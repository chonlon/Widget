#include <button.h>

lon::Button::Button(QWidget* parent)
    : QPushButton(parent),
      scaling_factor_(0.8) {
    setCurrentIcon(CurrentIconStatus::Normal);
    this->setFlat(true);
}

lon::Button::Button(std::shared_ptr<QIcon> normal_icon,
                    std::shared_ptr<QIcon> focus_icon,
                    std::shared_ptr<QIcon> pressed_icon,
                    QWidget* parent)
    : QPushButton(parent),
      scaling_factor_(0.8) {
    normal_icon_ = std::move(normal_icon);
    focus_icon_ = std::move(focus_icon);
    pressed_icon_ = std::move(pressed_icon);
    setCurrentIcon(CurrentIconStatus::Normal);
    this->setFlat(true);
}

void lon::Button::setScalingFactor(double factor) {
    scaling_factor_ = factor;
    this->setIconSize(QSize(this->width() * scaling_factor_, this->height() * scaling_factor_));
}

void lon::Button::setNormal(std::shared_ptr<QIcon> normal) {
    normal_icon_ = std::move(normal);

    setCurrentIcon(CurrentIconStatus::Normal);
}

void lon::Button::setFocus(std::shared_ptr<QIcon> focus) {
    focus_icon_ = std::move(focus);
}

void lon::Button::setPressed(std::shared_ptr<QIcon> pressed) {
    pressed_icon_ = std::move(pressed);
}

void lon::Button::enterEvent(QEvent* event) {
    if (this->isEnabled()) {
        setCurrentIcon(CurrentIconStatus::Focus);
    }
    return QPushButton::enterEvent(event);
}

void lon::Button::leaveEvent(QEvent* event) {
    if (this->isEnabled()) {
        setCurrentIcon(CurrentIconStatus::Normal);
    }
    return QPushButton::leaveEvent(event);
}

void lon::Button::mousePressEvent(QMouseEvent* event) {
    if (this->isEnabled()) {
        setCurrentIcon(CurrentIconStatus::Pressed);
    }
    QPushButton::mousePressEvent(event);
}

void lon::Button::mouseReleaseEvent(QMouseEvent* event) {
    if (this->isEnabled() && focus_icon_) {
        setCurrentIcon(CurrentIconStatus::Focus);
    }
    QPushButton::mouseReleaseEvent(event);
}

void lon::Button::paintEvent(QPaintEvent* event) {
    if (current_icon_) {
        drawCurrentIcon();
        event->accept();
    }
    QPushButton::paintEvent(event);
}

auto lon::Button::setCurrentIcon(CurrentIconStatus status) -> void {
    switch (status) {
        case CurrentIconStatus::Normal:
            current_icon_ = normal_icon_.get();
            break;
        case CurrentIconStatus::Focus:
            current_icon_ = focus_icon_.get();
            break;
        case CurrentIconStatus::Pressed:
            current_icon_ = pressed_icon_.get();
            break;
        default:
            exit(-1);
    }
    update();
}

auto lon::Button::drawCurrentIcon() -> void {
    if (current_icon_) {
        QPainter painter(this);
        auto w = static_cast<int>(this->size().width() * scaling_factor_);
        auto h = static_cast<int>(this->size().height() * scaling_factor_);
        auto w_offset = static_cast<int>((this->size().width() - w) / 2);
        auto h_offset = static_cast<int>((this->size().height() - h) / 2);
        painter.drawPixmap(QRect{w_offset, h_offset, w, h}, current_icon_->pixmap(w, h));
    }
}
