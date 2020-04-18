#include "TitleBar.h"
#include "TitleBarPrivate.hpp"

void lon::TitleBar::mouseDoubleClickEvent(QMouseEvent* event) {
    Q_UNUSED(event);
    emit data_->pmaximize_button_->clicked();
}

void lon::TitleBar::mousePressEvent(QMouseEvent* event) {
    data_->mousePressEvent(event);
    return QWidget::mousePressEvent(event);
}

void lon::TitleBar::mouseMoveEvent(QMouseEvent* event) {
    data_->mouseMoveEvent(event);
    return QWidget::mouseMoveEvent(event);
}

void lon::TitleBar::mouseReleaseEvent(QMouseEvent* event) {
    data_->mouseReleaseEvent(event);
    return QWidget::mouseReleaseEvent(event);
}

void lon::TitleBar::resizeEvent(QResizeEvent* event) {
    data_->resizeEvent(event);
    return QWidget::resizeEvent(event);
}

bool lon::TitleBar::eventFilter(QObject* obj, QEvent* event) {
    if (!data_->eventFilter(obj, event)) {
        return QWidget::eventFilter(obj, event);
    }
}

lon::TitleBar::TitleBar(QWidget* parent, Buttons button)
    : QWidget(parent),
      data_{std::make_unique<lon::TitleBarPrivate>(this)} {
    data_->initTitleBar(button);
}

void lon::TitleBar::setTitle(const QString& title) {
    data_->setTitle(title);
}

void lon::TitleBar::setTitleIcon(const QIcon& icon) {
    data_->setTitleIcon(icon);
}

void lon::TitleBar::setBackground(QPixmap* pixmap) {

}

void lon::TitleBar::setMinFunc(std::function<void()> val) {
    data_->min_func_ = val;
}

void lon::TitleBar::setMaxFunc(std::function<void()> val) {
    data_->max_func_ = val;
}

void lon::TitleBar::setCloseFunc(std::function<void()> val) {
    data_->close_func_ = val;
}

void lon::TitleBar::onButtonClicked() {
    QPushButton* pButton = qobject_cast<QPushButton*>(sender());
    data_->onButtonClicked(pButton);
}

inline lon::TitleBar::~TitleBar() = default;
