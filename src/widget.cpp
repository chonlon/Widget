#include "widget.h"
#include "WidgetPrivate.hpp"
#include <exception>
#include <QtGui/qpixmap.h>

using std::unique_ptr;

void Widget::initLayout() const
{
	data_->initLayout();
}

void Widget::initConnect() const
{
	data_->initConnect();
}

void Widget::initWidgets() const
{
	data_->initWidgets();
}

void Widget::paintEvent(QPaintEvent* event)
{
	data_->paintEvent(event);
	return QWidget::paintEvent(event);
}

Widget::Widget(QWidget* parent, TitleBar::Buttons status)
	: QWidget(parent)
{
	data_ = std::make_unique<WidgetPrivate>(this);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
	data_->title_bar_ = std::make_unique<TitleBar>(this, status);
	data_->center_widget_ = std::make_unique<QWidget>();
	data_->size_girp_enabled = false;

	initWidgets();
	initLayout();
	initConnect();
}

Widget::Widget(QWidget* center_widget, QWidget* parent)
	: QWidget(parent)
{
	if (center_widget)
	{
		// RAII don't worry about memory leak.
		throw std::logic_error{"pointer cannot be null!"};
	}
	data_ = std::make_unique<WidgetPrivate>(this);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);

	data_->title_bar_ = std::make_unique<TitleBar>(this);

	data_->center_widget_.reset(center_widget);

	initWidgets();
	initLayout();
	initConnect();
}

Widget::~Widget() = default;

QWidget* Widget::centerWidget() const
{
	return data_->center_widget_.get();
}


bool Widget::setCenterWidget(QWidget* widget)
{
	return data_->setCenterWidget(widget);
}


void Widget::setTitle(const QString& title)
{
	data_->setTitle(title);
}

void Widget::setTitleIcon(const QIcon& icon)
{
	data_->setTitleIcon(icon);
}

void Widget::setTitleBackground(QPixmap* pixmap)
{
	data_->setTitleBackground(pixmap);
}

void Widget::enableSizeGrip()
{
	data_->enableSizeGrip();
}

bool Widget::sizeGripEnabled()
{
	return data_->size_girp_enabled;
}

void Widget::setBackground(unique_ptr<QPixmap> pixmap)
{
	data_->setBackground(std::move(pixmap));
}

void Widget::setMinFunc(std::function<void()>&& val)
{
	data_->setMinFunc(std::forward<std::function<void()>>(val));
}

void Widget::setMaxFunc(std::function<void()>&& val)
{
	data_->setMaxFunc(std::forward<std::function<void()>>(val));
}

void Widget::setCloseFunc(std::function<void()>&& val)
{
	data_->setCloseFunc(std::forward<std::function<void()>>(val));
}
