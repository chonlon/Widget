#include "ShadowWindow.h"

lon::ShadowWindow::ShadowWindow(QWidget* parent, TitleBar::Buttons buttons)
    : QWidget(parent),
      window_(std::make_unique<Window>(this, buttons)),
      content_widget_(std::make_unique<QWidget>(this)),
      content_layout_(std::make_unique<QVBoxLayout>(content_widget_.get())),
      main_layout_(std::make_unique<QVBoxLayout>(this)) {
    setWindowFlags(Qt::FramelessWindowHint);    // 去掉边框
    setAttribute(Qt::WA_TranslucentBackground); // 背景透明

    // 添加阴影
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(window_.get());
    shadowEffect->setColor(Qt::red);
    shadowEffect->setBlurRadius(20); // 阴影的大小
    shadowEffect->setOffset(0, 0);
    
    content_widget_->setGraphicsEffect(shadowEffect);
    window_->setWindowFlags(Qt::Widget);

    // 添加到窗口中
    content_layout_->addWidget(window_.get());
    content_layout_->setMargin(0);
    main_layout_->addWidget(content_widget_.get());
    main_layout_->setMargin(20);
    {
        // connects
        connect(window_.get(),
                &lon::Window::maximizeButtonClicked,
                this,
                &lon::ShadowWindow::maximizeButtonClicked);
        connect(window_.get(),
                &lon::Window::minimizeButtonClicked,
                this,
                &lon::ShadowWindow::minimizeButtonClicked);
        connect(window_.get(),
                &lon::Window::closeButtonClicked,
                this,
                &lon::ShadowWindow::closeButtonClicked);
    }

}

void lon::ShadowWindow::setStyleSheet(const QString& style) {
    return content_widget_->setStyleSheet(style);
}


