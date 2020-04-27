#include "ShadowWindow.h"

lon::ShadowWindow::ShadowWindow(QWidget* parent, TitleBar::Buttons buttons)
    : QWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint);    // 去掉边框
    setAttribute(Qt::WA_TranslucentBackground); // 背景透明

    window_ = new Window{};
    window_->setWindowFlags(Qt::Widget);
    content_layout_.addWidget(window_);
    content_layout_.setMargin(0);

    {
        auto shadowEffect = [this]()
        {
            const auto shadowEffect = new QGraphicsDropShadowEffect(window_);
            shadowEffect->setColor(Qt::red);
            shadowEffect->setBlurRadius(20); // 阴影的大小
            shadowEffect->setOffset(0, 0);
            return shadowEffect;
        }();
        content_widget_ = new QWidget{this};
        content_widget_->setGraphicsEffect(shadowEffect);
        content_widget_->setAttribute(Qt::WA_TranslucentBackground, false);
        content_widget_->setObjectName("content_widget");
        content_widget_->setLayout(&content_layout_);
    }

    main_layout_.addWidget(content_widget_);
    main_layout_.setMargin(20);

    {
        connect(window_,
                &lon::Window::maximizeButtonClicked,
                this,
                &lon::ShadowWindow::maximizeButtonClicked);
        connect(window_,
                &lon::Window::minimizeButtonClicked,
                this,
                &lon::ShadowWindow::minimizeButtonClicked);
        connect(window_,
                &lon::Window::closeButtonClicked,
                this,
                &lon::ShadowWindow::closeButtonClicked);
    }
}

void lon::ShadowWindow::setStyleSheet(const QString& style) {
    return content_widget_->setStyleSheet(style);
}
