#include "ShadowWindow.h"

lon::ShadowWindow::ShadowWindow(QWidget* parent, TitleBar::Buttons buttons)
    : QWidget(parent),
      window_(std::make_unique<Window>(nullptr, buttons)) {
    setWindowFlags(Qt::FramelessWindowHint); // 去掉边框
    setAttribute(Qt::WA_TranslucentBackground);  // 背景透明

    // 添加阴影
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(window_.get());
    shadowEffect->setColor(Qt::red);
    shadowEffect->setBlurRadius(6); // 阴影的大小
    shadowEffect->setOffset(0, 0);
    window_->setStyleSheet("background-color:lightgray");
    window_->titleBar().setStyleSheet("background-color:lightgray");
    window_->setGraphicsEffect(shadowEffect);
    window_->setWindowFlags(Qt::Widget);
    
    // 添加到窗口中
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(window_.get());
    layout->setMargin(8);
    setLayout(layout);

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
