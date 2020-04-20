#pragma once
#include "Window.h"

namespace lon {

class ShadowWindow : public QWidget {
Q_OBJECT
public:
    explicit ShadowWindow(QWidget* parent = nullptr,
                          TitleBar::Buttons buttons = TitleBar::Buttons::ALL);

    /// <summary> 返回中间栏的widget指针. </summary>
    QWidget* centerWidget() const { return window_->centerWidget(); }

    /// <summary> 设置自定义的centerwidget. </summary>
    virtual bool setCenterWidget(std::unique_ptr<QWidget> widget) {
        return window_->setCenterWidget(std::move(widget));
    }

    virtual void setTitle(const QString& title) { window_->setTitle(title); }

    virtual void setTitleIcon(const QIcon& icon) { window_->setTitleIcon(icon); }

    // this class will take pixmap's ownship
    virtual void setTitleBackground(std::unique_ptr<QPixmap> pixmap) {
        window_->setTitleBackground(std::move(pixmap));
    }

    virtual void enableSizeGrip() { window_->enableSizeGrip(); }

    virtual bool sizeGripEnabled() { return window_->sizeGripEnabled(); }

    // this class will take pixmap's ownship
    virtual void setBackground(std::unique_ptr<QPixmap> pixmap) {
        window_->setBackground(std::move(pixmap));
    }

    /// <summary>
    /// 设置最小化按钮按下后的执行函数
    /// </summary>
    /// <param name="val"> 执行函数, std::function<void> </param>
    virtual void setMinFunc(std::function<void(void)>&& val) {
        window_->setMinFunc(std::move(val));
    }

    /// <summary>
    /// 设置最大化按钮按下后的执行函数
    /// </summary>
    /// <param name="val"> 执行函数, std::function<void> </param>
    virtual void setMaxFunc(std::function<void(void)>&& val) {
        window_->setMaxFunc(std::move(val));
    }

    /// <summary>
    /// 关闭按钮按下后的执行函数
    /// </summary>
    /// <param name="val"> 执行函数, std::function<void> </param>
    virtual void setCloseFunc(std::function<void(void)>&& val) {
        window_->setCloseFunc(std::move(val));
    }

signals:
    void minimizeButtonClicked();
    void maximizeButtonClicked();
    void closeButtonClicked();


private:
    std::unique_ptr<Window> window_{nullptr};
};

}
