#include "Toast.h"
#include "AnonymousHeader/Base.h"
#include <QPropertyAnimation>
#include <QPainter>
#include <QLabel>
#include <QHBoxLayout>
#include <gsl/gsl>

constexpr int FixedHeight = 35;
constexpr int SpacingWidth = 15;

auto getTextSize(gsl::not_null<QLabel*> label) {
    QFontMetrics font_metrics(label->font());
    auto rect = font_metrics.boundingRect(label->text());
    return QSize{rect.width(), rect.height()};
}


lon::Toast::Toast(const QString& msg, QWidget* parent)
    : QWidget(parent) {
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    main_layout_ = new QHBoxLayout{this};
    label_ = new QLabel{msg, this};
    label_->setWordWrap(false);

    Expects(label_);
    setFixedSize(getTextSize(label_) + SpacingWidth);

    main_layout_->addWidget(label_);
    main_layout_->setContentsMargins(5, 0, 0, 0);


    connect(&timer_, &QTimer::timeout, this, &lon::Toast::updateRender);
    timer_.setInterval(2000);
    timer_.start();
}


void lon::Toast::popUp() {
    auto point = [this]()
    {
        QPoint rect_center;
        if (parent_ == nullptr) {
            rect_center = getDesktopGeometry().center();
        } else {
            rect_center = parent_->geometry().center();
        }
        return QPoint{rect_center.x() - (width() / 2), rect_center.y() - (height() / 2)};
    }();

    popUp(point);
}

void lon::Toast::popUp(const QPoint& point) {
    move(point);

    raise();
    show();

    auto animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void lon::Toast::setFont(const QFont font) {
    Expects(label_);
    label_->setFont(font);
    setFixedSize(getTextSize(label_) + SpacingWidth);
}

void lon::Toast::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 175));
    painter.drawRoundRect(rect(), 6, 6);
}

void lon::Toast::updateRender() {
    timer_.stop();
    auto animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    connect(animation, &QPropertyAnimation::finished, this, &Toast::close);
}

void lon::popUpOneToast(const QString& msg, QWidget* parent) {
    auto toast = new Toast{msg, parent};
    toast->setAttribute(Qt::WA_QuitOnClose);
    toast->setAttribute(Qt::WA_DeleteOnClose);

    toast->popUp();
}

void lon::popUpOneToast(const QString& msg, const QPoint& point) {
    auto toast = new Toast{msg};
    toast->setAttribute(Qt::WA_QuitOnClose);
    toast->setAttribute(Qt::WA_DeleteOnClose);

    toast->popUp(point);
}
