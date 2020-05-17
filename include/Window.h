#ifndef LON_WIDGET
#define LON_WIDGET

#include "TitleBar.h"
#include <memory>
#include <QSizeGrip>
#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout>
#include <gsl/pointers>
class WindowPrivate;
class QLayout;

namespace lon {
// 其实也只是一个简单的封装.
// 如果某些地方不符合需要, 可以自定义窗口,
// 但是务必使用lon::TitleBar以保持统一风格.

/// <summary>
/// 统一样式的Widget.
/// 不允许自己定义layout(因为会破环titlebar)
/// </summary>


class Window : public QWidget {
Q_OBJECT
private:
    friend class WindowPrivate;
    std::unique_ptr<WindowPrivate> data_{nullptr};

private:
    // 禁用setlayout, 只允许操作centerWidget.
    virtual void setLayout(QLayout*) {
    }

    void initLayout() const;

    void initConnect() const;

    void initWidgets() const;

    void updateBackground() {
        update();
    }

protected:
    void resizeEvent(QResizeEvent* event) override {
        return QWidget::resizeEvent(event);
    }

    void paintEvent(QPaintEvent* event) override;

public:
    explicit Window(QWidget* parent = nullptr, TitleBar::Buttons status = TitleBar::Buttons::ALL);

    explicit Window(gsl::not_null<gsl::owner<QWidget*>> center_widget,
                    QWidget* parent = nullptr,
                    TitleBar::Buttons status = TitleBar::Buttons::ALL);

    ~Window() override;

    QWidget& centerWidget() const;
    TitleBar& titleBar() const;

    /// <summary> 设置自定义的centerwidget. </summary>
    bool Window::setCenterWidget(gsl::not_null<gsl::owner<QWidget*>> widget);

    virtual void setTitle(const QString& title);

    virtual void setTitleIcon(const QIcon& icon);

    // this class will take pixmap's ownship
    virtual void setTitleBackground(std::unique_ptr<QPixmap> pixmap);

    virtual void setSizeGripEnable(bool enable = true);

    virtual bool sizeGripEnabled();

    // this class will take pixmap's ownship
    virtual void setBackground(std::unique_ptr<QPixmap> pixmap);

    /// <summary>
    /// 设置最小化按钮按下后的执行函数
    /// </summary>
    /// <param name="val"> 执行函数, std::function<void> </param>
    virtual void setMinFunc(std::function<void(void)>&& val);

    /// <summary>
    /// 设置最大化按钮按下后的执行函数
    /// </summary>
    /// <param name="val"> 执行函数, std::function<void> </param>
    virtual void setMaxFunc(std::function<void(void)>&& val);

    /// <summary>
    /// 关闭按钮按下后的执行函数
    /// </summary>
    /// <param name="val"> 执行函数, std::function<void> </param>
    virtual void setCloseFunc(std::function<void(void)>&& val);

signals:
    void minimizeButtonClicked();
    void maximizeButtonClicked();
    void closeButtonClicked();
    void sizeChanged(QResizeEvent* event);
};

/**
 * \brief 将一个非空widget提升为Window, 对于很多已存在的widget或者dialog, 直接使用此函数提升为统一风格的无边框Window.
 * \param widget 非空, 并且获取指针所有权.
 * \param status 显示的按钮.
 */
inline std::unique_ptr<Window> promoteToWindow(gsl::not_null<gsl::owner<QWidget*>> widget,
                                               TitleBar::Buttons status = TitleBar::Buttons::ALL) {
    return std::make_unique<Window>(widget, nullptr, status);
}
} // namespace lon

#endif
