#include "widget.h"
#include "WidgetPrivate.hpp"
#include <exception>
#include <QtGui/qpixmap.h>

using std::unique_ptr;
void Widget::initLayout() const {
    data_->initLayout();
}

void Widget::initBottomBar() const  {
    data_->initBottomBar();
}

void Widget::initConnect() const {
    data_->initConnect();
}

void Widget::initWidgets() const {
    data_->initWidgets();
}

void Widget::paintEvent(QPaintEvent* event) {
    data_->paintEvent(event);
    return QWidget::paintEvent(event);
}

Widget::Widget(QWidget* parent, TitleBar::Buttons status)
    : QWidget(parent)
{
    data_ = std::make_unique<WidgetPrivate>(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    data_->title_bar_ = new TitleBar(this, status);
    data_->center_widget_ = std::make_unique<QWidget>();
    data_->bottom_bar_ = std::make_unique<QWidget>();
    data_->size_girp_enabled = false;

    initWidgets();
    initBottomBar();
    initLayout();
    initConnect();
}

Widget::Widget(QWidget* center_widget, QWidget* bottom_bar, QWidget* parent)
    : QWidget(parent) {
    if(center_widget || bottom_bar) {
        // RAII don't worry about memory leak.
        throw std::logic_error{"pointer cannot be null!"};
    }
    data_ = std::make_unique<WidgetPrivate>(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);

    data_->title_bar_ = new TitleBar(this);

    data_->center_widget_.reset(center_widget);
    data_->bottom_bar_.reset(bottom_bar);

    initWidgets();
    initLayout();
    initConnect();
}

Widget::~Widget() = default;

QWidget* Widget::centerWidget() const {
    return data_->center_widget_.get();
}

bool Widget::setBottomBar(QWidget* widget) {
    return data_->setBottomBar(widget);
}

bool Widget::setCenterWidget(QWidget* widget) {
    return data_->setCenterWidget(widget);
}

QWidget* Widget::bottomBar() const {
    return data_->bottom_bar_.get();
}

void Widget::setTitle(const QString& title) {
    data_->setTitle(title);
}

void Widget::setTitleIcon(const QIcon& icon) {
    data_->setTitleIcon(icon);
}

void Widget::setTitleBackground(QPixmap* pixmap) {
    data_->setBackground(pixmap);
}

void Widget::enabelSizeGrip() {
    data_->enabelSizeGrip();
}

bool Widget::sizeGripEnabled() {
    return data_->size_girp_enabled;
}

void Widget::setBackground(QPixmap* pixmap) {
    data_->setBackground(pixmap);
}

void Widget::setMinFunc(std::function<void()>&& val) {
    data_->setMinFunc(val);
}

void Widget::setMaxFunc(std::function<void()>&& val) {
    data_->setMaxFunc(val);
}

void Widget::setCloseFunc(std::function<void()>&& val) {
    data_->setCloseFunc(val);
}
