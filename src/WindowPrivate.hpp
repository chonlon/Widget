#pragma once
#include "button.h"
#include "TitleBar.h"
#include <QGraphicsDropShadowEffect>
#include <QSizeGrip>
#include <QtWidgets>
#include <Window.h>
#include <gsl/gsl>

using lon::Window;
using lon::TitleBar;
using lon::Button;
using std::unique_ptr;

class WindowPrivate : QObject {
Q_OBJECT
private:
    Window* parent_;
public:
    WindowPrivate(gsl::not_null<Window*> parent, TitleBar::Buttons status)
        : parent_{parent} {
        // todo move to init list
        title_bar_ = new TitleBar(parent_, status);
        center_widget_ = new QWidget(parent_);
        initWidgets();
        initLayout();
        initConnect();
    }


    void initLayout() {
        p_layout_ = new QGridLayout(parent_);
        p_layout_->setSpacing(0);
        p_layout_->addWidget(title_bar_, 0, 0, 1, 2);
        p_layout_->addWidget(center_widget_, 1, 0, 1, 2);
        p_layout_->setContentsMargins(0, 0, 0, 0);
    }


    void initConnect() const {
        connect(
            title_bar_,
            &TitleBar::minimizeButtonClicked,
            parent_,
            &Window::minimizeButtonClicked);
        connect(
            title_bar_,
            &TitleBar::maximizeButtonClicked,
            parent_,
            &Window::maximizeButtonClicked);
        connect(title_bar_,
                &TitleBar::closeButtonClicked,
                parent_,
                &Window::closeButtonClicked);
    }

    void initWidgets() const {
        parent_->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);        
    }

    void paintEvent(QPaintEvent* event) const {        
        if (pixmap_) {
            QPainter painter(parent_);
            painter.drawPixmap(QRect{0, 0, parent_->width(), parent_->height()}, *pixmap_);
            event->accept();
        }       
    }


    bool setCenterWidget(QWidget* widget) {
        if (!widget)
            return false;

        p_layout_->removeWidget(center_widget_);

        

        if (widget)
            p_layout_->addWidget(widget, 1, 0);
        delete center_widget_;
        center_widget_ = widget;
        return true;
    }

    void setTitle(const QString& title) const {
        title_bar_->setTitle(title);
    }

    void setTitleIcon(const QIcon& icon) const {
        title_bar_->setTitleIcon(icon);
    }

    void setTitleBackground(unique_ptr<QPixmap> pixmap) const {
        title_bar_->setBackground(std::move(pixmap));
    }

    void setSizeGripEnable(bool enable) {
        if(enable) {
           if(size_grip_) size_grip_->setVisible(true);
           else enableSizeGrip();
        } else {
           if(size_grip_) size_grip_->setVisible(false);
        }
        
    }

    void enableSizeGrip() {
        size_grip_enabled = true;
        size_grip_ = new QSizeGrip(parent_);
        size_grip_->setFixedSize(size_grip_->sizeHint());
        p_layout_->addWidget(size_grip_, 2, 1, Qt::AlignRight | Qt::AlignBottom);
    }

    void setBackground(unique_ptr<QPixmap> pixmap) {
        parent_->setAutoFillBackground(true);
        //判断图片是否为空
        if (!pixmap || pixmap->isNull()) {
            qDebug() << tr("illege arguments, your image is empty") << __FILE__ << "\n";
        }
        pixmap_ = std::move(pixmap);
        parent_->updateBackground();
    }

    TitleBar& titleBar() const {
        Ensures(title_bar_);
        return *title_bar_;
    }

    QWidget& centerWidget() const {
        return *center_widget_;
    }

    void setMinFunc(std::function<void()>&& val) const {
        title_bar_->setMinFunc(std::move(val));
    }

    void setMaxFunc(std::function<void()>&& val) const {
        title_bar_->setMaxFunc(std::move(val));
    }

    void setCloseFunc(std::function<void()>&& val) const {
        title_bar_->setCloseFunc(std::move(val));
    }

    TitleBar* title_bar_{nullptr};
    QSizeGrip* size_grip_{nullptr};

    QGridLayout* p_layout_{nullptr};

    bool size_grip_enabled{false};

    unique_ptr<QPixmap> pixmap_{nullptr};
    QWidget* center_widget_{nullptr};
};
