#include "Window.h"
#include "WindowPrivate.hpp"
#include <exception>
#include <QtGui/qpixmap.h>
#include <gsl/gsl>

using lon::Window;
using std::unique_ptr;

void Window::initLayout() const {
    data_->initLayout();
}

void Window::initConnect() const {
    data_->initConnect();
}

void Window::initWidgets() const {
    data_->initWidgets();
}

void Window::paintEvent(QPaintEvent* event) {
    data_->paintEvent(event);
    return QWidget::paintEvent(event);
}

Window::Window(QWidget* parent, TitleBar::Buttons status)
    : QWidget(parent),
      data_{std::make_unique<WindowPrivate>(this, status)} {
}

Window::Window(std::unique_ptr<QWidget> center_widget, QWidget* parent, TitleBar::Buttons status)
    : Window(parent, status) {
    Expects(center_widget != nullptr);

    setCenterWidget(std::move(center_widget));
}

Window::~Window() = default;

QWidget& Window::centerWidget() const {
    return data_->centerWidget();
}

TitleBar& Window::titleBar() const {
    return data_->titleBar();
}


bool Window::setCenterWidget(std::unique_ptr<QWidget> widget) {
    Expects(widget != nullptr);
    return data_->setCenterWidget(std::move(widget));
}


void Window::setTitle(const QString& title) {
    data_->setTitle(title);
}

void Window::setTitleIcon(const QIcon& icon) {
    data_->setTitleIcon(icon);
}

void Window::setTitleBackground(unique_ptr<QPixmap> pixmap) {
    Expects(pixmap != nullptr);
    data_->setTitleBackground(std::move(pixmap));
}

void Window::enableSizeGrip() {
    data_->enableSizeGrip();
}

bool Window::sizeGripEnabled() {
    return data_->size_grip_enabled;
}

void Window::setBackground(unique_ptr<QPixmap> pixmap) {
    Expects(pixmap != nullptr);
    data_->setBackground(std::move(pixmap));
}

void Window::setMinFunc(std::function<void()>&& val) {
    data_->setMinFunc(std::forward<std::function<void()>>(val));
}

void Window::setMaxFunc(std::function<void()>&& val) {
    data_->setMaxFunc(std::forward<std::function<void()>>(val));
}

void Window::setCloseFunc(std::function<void()>&& val) {
    data_->setCloseFunc(std::forward<std::function<void()>>(val));
}
