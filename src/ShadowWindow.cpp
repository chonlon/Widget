#include "ShadowWindow.h"


lon::ShadowBox::ShadowBox(gsl::not_null<gsl::owner<QWidget*>> content,
                          QColor color,
                          int shadow_width)
    : content_widget_(content) {
    main_layout_ = new QVBoxLayout{this};

    setWindowFlags(Qt::FramelessWindowHint); // 去掉边框
    setAttribute(Qt::WA_TranslucentBackground); // 背景透明

    {
        auto shadowEffect = [&color, this, shadow_width]()
        {
            const auto shadowEffect = new QGraphicsDropShadowEffect(content_widget_);
            shadowEffect->setColor(color);
            shadowEffect->setBlurRadius(shadow_width); // 阴影的大小
            shadowEffect->setOffset(0, 0);
            return shadowEffect;
        }();

        container_widget_ = [shadowEffect, this]()
        {
            auto container_widget = new QWidget{this};
            container_widget->setGraphicsEffect(
                gsl::owner<QGraphicsDropShadowEffect*>(shadowEffect));
            container_widget->setAttribute(Qt::WA_TranslucentBackground, false);
            container_widget->setObjectName("ShadowBox__container_widget_");
            content_layout_ = new QVBoxLayout{container_widget};
            return container_widget;
        }();
        this->setWidgetBackGround(Qt::blue);
        
        content_layout_->addWidget(gsl::owner<QWidget*>(content_widget_));
        content_layout_->setMargin(0);
    }

    main_layout_->addWidget(gsl::owner<QWidget*>(container_widget_));
    main_layout_->setSpacing(0);
    main_layout_->setMargin(shadow_width);
}

void lon::ShadowBox::setWidgetBackGround(const QColor& color) const {
    container_widget_->setStyleSheet(
        QString("QWidget#%4{"
            "background-color:rgb(%1, %2, %3);"
            "}")
        .arg(color.red())
        .arg(color.green())
        .arg(color.blue())
        .arg(container_widget_->objectName())
        );
}

lon::ShadowWindow::ShadowWindow(QWidget* parent,
                                QColor color,
                                int shadow_width,
                                TitleBar::Buttons buttons)   
{
    main_layout_ = new QVBoxLayout(this);
    main_layout_->setMargin(0);

    setWindowFlags(Qt::FramelessWindowHint);    // 去掉边框
    setAttribute(Qt::WA_TranslucentBackground); // 背景透明

    window_ = new Window{nullptr, buttons};
    

    shadow_box_ = new ShadowBox{gsl::owner<lon::Window*>(window_), color, shadow_width};
    main_layout_->addWidget(gsl::owner<ShadowWindow*>(shadow_box_));
}

void lon::ShadowWindow::setWidgetBackGround(const QColor& color) const {
    shadow_box_->setWidgetBackGround(color);
}
