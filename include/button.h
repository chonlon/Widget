#ifndef LON_BUTTON
#define LON_BUTTON

#include <QPushButton>
#include <QtGui>
#include <memory>

namespace lon {
/// <summary>
/// flat button, 提供设置三态图标设置方法, 方便管理对应的图标.
/// </summary>
class Button : public QPushButton {
    Q_OBJECT

public:
    /// <summary>
    /// 设置默认按钮图标.
    /// 前面注释的部分是用于查看当前icon的图片是否放置于正确路径
    /// 如果发现设置图标失败, 可以试试取消注释, 查看当前路径是什么
    /// 以及是否存在icon文件
    /// </summary>
    /// <param name: parent> 用于设置当前Button的parent </param>
    explicit Button(QWidget* parent = nullptr);


    /// <summary>
    /// 以自定义的图标设置按钮,
    /// 使用智能指针管理icon内存.
    /// </summary>
    explicit Button(std::shared_ptr<QIcon> normal_icon,
                    std::shared_ptr<QIcon> focus_icon,
                    std::shared_ptr<QIcon> pressed_icon,
                    QWidget* parent = nullptr);

    /// <summary>
    /// 设置button中的图标缩放比例
    /// </summary>
    /// <param name="factor">缩放比例, 范围 0 - 1 </param>
    auto setScalingFactor(double factor) -> void;

    /// <summary> 设置normal图标, 以智能指针管理内存 </summary>
    virtual auto setNormal(std::shared_ptr<QIcon> normal) -> void;

    /// <summary> 设置focus图标, 以智能指针管理内存 </summary>
    virtual auto setFocus(std::shared_ptr<QIcon> focus) -> void;

    /// <summary> 设置pressed图标, 以智能指针管理内存 </summary>
    virtual auto setPressed(std::shared_ptr<QIcon> pressed) -> void;

protected:
    /// <summary>
    /// 鼠标进入按钮事件, 改变图标为focus.
    /// </summary>
    void enterEvent(QEvent* event) override;

    /// <summary>
    /// 鼠标进入按钮事件, 改变图标为normal.
    /// </summary>
    void leaveEvent(QEvent* event) override;

    /// <summary>
    /// 鼠标按下按钮事件, 改变图标为pressed.
    /// </summary>
    void mousePressEvent(QMouseEvent* event) override;

    /// <summary>
    /// 鼠标松开按钮事件, 改变图标为focus.
    /// </summary>
    void mouseReleaseEvent(QMouseEvent* event) override;


    void paintEvent(QPaintEvent* event) override;

private:
    QIcon* current_icon_{nullptr};

    std::shared_ptr<QIcon> normal_icon_;
    std::shared_ptr<QIcon> focus_icon_;
    std::shared_ptr<QIcon> pressed_icon_;

    double scaling_factor_;
    QPoint draw_text_position_{0, 0};

    enum class CurrentIconStatus { Normal, Focus, Pressed };

    auto setCurrentIcon(CurrentIconStatus status) -> void;

    auto drawCurrentIcon() -> void;
};
}  // namespace lon
#endif
