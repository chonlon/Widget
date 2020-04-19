#ifndef LON_BUTTON
#define LON_BUTTON

#include <QPushButton>
#include <QtGui>
#include <memory>

namespace lon {
/// <summary>
/// PushButton的一个封装, 提供简单的设置PushButton三态的方法, 并且可以设置缩放因子以满足不同
/// 大小要求.
/// </summary>
/// 注意: 默认的不是flat的,(因为如果图标设置失败, 而按钮已经时flat的会很尴尬)
/// 所以添加icon后还是会有边框和背景, 如果不想要, 使用button->setFlat(true)即可.
class Button : public QPushButton {
Q_OBJECT
private:
    std::shared_ptr<QIcon> normal_icon_;
    std::shared_ptr<QIcon> focus_icon_;
    std::shared_ptr<QIcon> pressed_icon_;

    double scaling_factor_;

protected:
    /// <summary>
    /// 鼠标进入按钮事件, 改变图标为focus.
    /// 设置失败只在调试时提示, 不影响程序运行.
    /// </summary>
    void enterEvent(QEvent* event) override {
        Q_UNUSED(event)

        if (this->isEnabled() && focus_icon_) {
            this->setIcon(*focus_icon_);
        } else {
            qDebug() << "button is not enabled or icon is not exits";
        }
    }

    /// <summary>
    /// 鼠标进入按钮事件, 改变图标为normal.
    /// 设置失败只在调试时提示, 不影响程序运行.
    /// </summary>
    void leaveEvent(QEvent* event) override {
        Q_UNUSED(event)

        if (this->isEnabled() && normal_icon_) {
            this->setIcon(*normal_icon_);
        } else {
            qDebug() << "button is not enabled or icon is not exits";
        }
    }

    /// <summary>
    /// 鼠标按下按钮事件, 改变图标为pressed.
    /// 设置失败只在调试时提示, 不影响程序运行.
    /// </summary>
    void mousePressEvent(QMouseEvent* event) override {
        if (this->isEnabled() && pressed_icon_) {
            this->setIcon(*pressed_icon_);
        } else {
            qDebug() << "button is not enabled or icon is not exits";
        }
        QPushButton::mousePressEvent(event);
    }

    /// <summary>
    /// 鼠标松开按钮事件, 改变图标为focus.
    /// 设置失败只在调试时提示, 不影响程序运行.
    /// </summary>
    void mouseReleaseEvent(QMouseEvent* event) override {
        if (this->isEnabled() && focus_icon_) {
            this->setIcon(*focus_icon_);
        } else {
            qDebug() << "button is not enabled or icon is not exits";
        }
        QPushButton::mouseReleaseEvent(event);
    }

    virtual void setIcon(const QIcon& icon) {
        QPushButton::setIcon(icon);
        this->setIconSize(QSize(this->width() * scaling_factor_, this->height() * scaling_factor_));
    }


    void resizeEvent(QResizeEvent* event) override {
        QPushButton::resizeEvent(event);
        this->setIconSize(QSize(this->width() * scaling_factor_, this->height() * scaling_factor_));
    }

public:
    /// <summary>
    /// 设置默认按钮图标.
    /// 前面注释的部分是用于查看当前icon的图片是否放置于正确路径
    /// 如果发现设置图标失败, 可以试试取消注释, 查看当前路径是什么
    /// 以及是否存在icon文件
    /// </summary>
    /// <param name: parent> 用于设置当前Button的parent </param>
    Button(QWidget* parent = nullptr)
        : QPushButton(parent),
          scaling_factor_(0.8),
          normal_icon_{std::make_shared<QIcon>("normal.png")},
          focus_icon_{std::make_shared<QIcon>("focus.png")},
          pressed_icon_{std::make_shared<QIcon>("pressed.png")} {
        this->setIcon(*normal_icon_);
    }


    /// <summary>
    /// 以自定义的图标设置按钮,
    /// 使用智能指针管理icon内存.
    /// </summary>
    Button(std::shared_ptr<QIcon> normal_icon,
           std::shared_ptr<QIcon> focus_icon,
           std::shared_ptr<QIcon> pressed_icon,
           QWidget* parent = nullptr)
        : QPushButton(parent),
          scaling_factor_(0.8) {
        normal_icon_ = std::move(normal_icon);
        focus_icon_ = std::move(focus_icon);
        pressed_icon_ = std::move(pressed_icon);
        this->setIcon(*normal_icon_);
    }

    /// <summary>
    /// 设置button中的图标缩放比例
    /// </summary>
    /// <param name="factor">缩放比例, 范围 0 - 1</param>
    void setScalingFactor(double factor) {
        scaling_factor_ = factor;
        this->setIconSize(QSize(this->width() * scaling_factor_, this->height() * scaling_factor_));
    }

    /// <summary> 设置normal图标, 以智能指针管理内存 </summary>
    virtual void setNormal(std::shared_ptr<QIcon> normal) {
        normal_icon_ = std::move(normal);

        this->setIcon(*normal_icon_);
    }

    /// <summary> 设置focus图标, 以智能指针管理内存 </summary>
    virtual void setFocus(std::shared_ptr<QIcon> focus) {
        focus_icon_ = std::move(focus);
    }

    /// <summary> 设置pressed图标, 以智能指针管理内存 </summary>
    virtual void setPressed(std::shared_ptr<QIcon> pressed) {
        pressed_icon_ = std::move(pressed);
    }

    virtual ~Button() {
        normal_icon_ = nullptr;
        focus_icon_ = nullptr;
        pressed_icon_ = nullptr;
    }
};
} // namespace lon
#endif
