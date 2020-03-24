#pragma once
#include "button.hpp"
#include "titlebar.hpp"
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QSizeGrip>
#include <QVBoxLayout>
#include <QtWidgets>
#include <widget.hpp>

class WidgetPrivate : QObject {
    Q_OBJECT
private:
    Widget* parent_;
public:
    WidgetPrivate(Widget* parent) : parent_{parent} {}


    TitleBar* title_bar_{nullptr};

    QSizeGrip* size_grip_{nullptr};

    Button* ok_button_{nullptr};
    Button* cancel_button_{nullptr};

    QGridLayout* p_layout_{nullptr};

    bool size_girp_enabled{nullptr};

    QPixmap* pixmap_{nullptr};
    QWidget* center_widget_{nullptr};
    QWidget* bottom_bar_{nullptr};

    void initLayout() {
        p_layout_ = new QGridLayout(this);
        p_layout_->setSpacing(0);
        p_layout_->addWidget(title_bar_, 0, 0, 1, 2);
        p_layout_->addWidget(center_widget_, 1, 0, 1, 2);
        p_layout_->addWidget(bottom_bar_, 2, 0, 1, 1);
        p_layout_->setContentsMargins(0, 0, 0, 0);
    }

    void initBottomBar() {
        bottom_bar_->setFixedHeight(50);
        bottom_bar_->setWindowFlags(Qt::SubWindow);

        QHBoxLayout* bottom_layout = new QHBoxLayout(bottom_bar_);

        ok_button_ = new Button(bottom_bar_);
        cancel_button_ = new Button(bottom_bar_);


        // 这里由于pushbutton不能使text在icon下面显示.
        // 所以只好使用样式表了
        // 或者这里得给ok_button换一个类型: QToolButton了.
        ok_button_->setStyleSheet(
            "QPushButton{border-image: url(:/icon/Resources/button.png);} "
            "QPus0hButton:hover{border-image: url(:/icon/Resources/button.png);} "
            "QPushButton:pressed{border-image: url(:/icon/Resources/button.png);} ");
        ok_button_->setText(u8"确认");
        ok_button_->setFixedSize(90, 30);
        ok_button_->setFlat(true);

        cancel_button_->setStyleSheet(
            "QPushButton{border-image: url(:/icon/Resources/button.png);} "
            "QPus0hButton:hover{border-image: url(:/icon/Resources/button.png);} "
            "QPushButton:pressed{border-image: url(:/icon/Resources/button.png);} ");

        cancel_button_->setText(u8"取消");
        cancel_button_->setFixedSize(90, 30);
        cancel_button_->setFlat(true);

        bottom_layout->addStretch();
        bottom_layout->addWidget(ok_button_);
        bottom_layout->addStretch();
        bottom_layout->addWidget(cancel_button_);
        bottom_layout->addStretch();

        bottom_bar_->setLayout(bottom_layout);
    }

    void initConnect() {
        // todo use new style connect.
        connect(ok_button_, SIGNAL(clicked()), this, SLOT(onOkButtonClicked()));
        connect(cancel_button_, SIGNAL(clicked()), this, SLOT(onCancelButtonClicked()));
        connect(title_bar_, SIGNAL(minimizeButtonClicked()), this, SIGNAL(minimizeButtonClicked()));
        connect(title_bar_, SIGNAL(maximizeButtonClicked()), this, SIGNAL(maximizeButtonClicked()));
        connect(title_bar_, SIGNAL(closeButtonClicked()), this, SIGNAL(closeButtonClicked()));
    }

    void initWidgets() {
        pixmap_ = nullptr;
        QPalette palette;
        palette.setBrush(parent_->backgroundRole(), QBrush(QColor(255, 255, 255, 30)));
        title_bar_->setPalette(palette);
    }

    void paintEvent(QPaintEvent *event) override {
        QPainter painter(parent_);
        if(pixmap_)
            painter.drawPixmap(QRect{0, 0, parent_->width(), parent_->height()}, *pixmap_);
        return QWidget::paintEvent(event);
    }
};