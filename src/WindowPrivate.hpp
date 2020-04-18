#pragma once
#include "button.h"
#include "TitleBar.h"
#include <QGraphicsDropShadowEffect>
#include <QSizeGrip>
#include <QtWidgets>
#include <Window.h>

using lon::Window;
using lon::TitleBar;
using lon::Button;
using std::unique_ptr;

class WindowPrivate : QObject {
Q_OBJECT
private:
    Window* parent_;
public:
    WindowPrivate(Window* parent)
        : parent_{parent} {
    }

    unique_ptr<TitleBar> title_bar_{nullptr};
    unique_ptr<QSizeGrip> size_grip_{nullptr};

    QGridLayout* p_layout_{nullptr};

    bool size_girp_enabled{false};

    unique_ptr<QPixmap> pixmap_{nullptr};
    unique_ptr<QWidget> center_widget_{std::make_unique<QWidget>()};

    void initLayout() {
        p_layout_ = new QGridLayout(parent_);
        p_layout_->setSpacing(0);
        p_layout_->addWidget(title_bar_.get(), 0, 0, 1, 2);
        p_layout_->addWidget(center_widget_.get(), 1, 0, 1, 2);
        p_layout_->setContentsMargins(0, 0, 0, 0);
    }


    void initConnect() const {
        connect(
            title_bar_.get(),
            &TitleBar::minimizeButtonClicked,
            parent_,
            &Window::minimizeButtonClicked);
        connect(
            title_bar_.get(),
            &TitleBar::maximizeButtonClicked,
            parent_,
            &Window::maximizeButtonClicked);
        connect(title_bar_.get(), &TitleBar::closeButtonClicked, parent_, &Window::closeButtonClicked);
    }

    void initWidgets() {
        pixmap_ = nullptr;
        QPalette palette;
        palette.setBrush(parent_->backgroundRole(), QBrush(QColor(255, 255, 255, 30)));
        title_bar_->setPalette(palette);
    }

    void paintEvent(QPaintEvent* event) const {
        QPainter painter(parent_);
        if (pixmap_)
            painter.drawPixmap(QRect{0, 0, parent_->width(), parent_->height()}, *pixmap_);
    }


    bool setCenterWidget(std::unique_ptr<QWidget> widget) {
        if (!widget)
            return false;

        p_layout_->removeWidget(center_widget_.get());

        center_widget_ = std::move(widget);

        if (center_widget_)
            p_layout_->addWidget(center_widget_.get(), 1, 0);
        return true;
    }

    void setTitle(const QString& title) const {
        title_bar_->setTitle(title);
    }

    void setTitleIcon(const QIcon& icon) const {
        title_bar_->setTitleIcon(icon);
    }

    void setTitleBackground(unique_ptr<QPixmap> pixmap) const {
        title_bar_->setBackground(pixmap.release());
    }


    void enableSizeGrip() {
        size_girp_enabled = true;
        size_grip_ = std::make_unique<QSizeGrip>(parent_);
        size_grip_->setFixedSize(size_grip_->sizeHint());
        p_layout_->addWidget(size_grip_.get(), 2, 1, Qt::AlignRight | Qt::AlignBottom);
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

    void setMinFunc(std::function<void()>&& val) const {
        title_bar_->setMinFunc(val);
    }

    void setMaxFunc(std::function<void()>&& val) const {
        title_bar_->setMaxFunc(val);
    }

    void setCloseFunc(std::function<void()>&& val) const {
        title_bar_->setCloseFunc(val);
    }
};
