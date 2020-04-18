#include "Window.h"
#include "WindowPrivate.hpp"
#include <exception>
#include <QtGui/qpixmap.h>

using lon::Window;
using std::unique_ptr;

void Window::initLayout() const
{
	data_->initLayout();
}

void Window::initConnect() const
{
	data_->initConnect();
}

void Window::initWidgets() const
{
	data_->initWidgets();
}

void Window::paintEvent(QPaintEvent* event)
{
	data_->paintEvent(event);
	return QWidget::paintEvent(event);
}

Window::Window(QWidget* parent, TitleBar::Buttons status)
	: QWidget(parent)
{
	data_ = std::make_unique<WindowPrivate>(this);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
	data_->title_bar_ = std::make_unique<TitleBar>(this, status);

	initWidgets();
	initLayout();
	initConnect();
}

Window::Window(QWidget* center_widget, QWidget* parent, TitleBar::Buttons status)
	: Window(parent, status)
{
	if (center_widget)
	{
		// RAII don't worry about memory leak.
		throw std::logic_error{"pointer cannot be null!"};
	}

	data_->center_widget_.reset(center_widget);
}

Window::~Window() = default;

QWidget* Window::centerWidget() const
{
	return data_->center_widget_.get();
}


bool Window::setCenterWidget(QWidget* widget)
{
	return data_->setCenterWidget(widget);
}


void Window::setTitle(const QString& title)
{
	data_->setTitle(title);
}

void Window::setTitleIcon(const QIcon& icon)
{
	data_->setTitleIcon(icon);
}

void Window::setTitleBackground(QPixmap* pixmap)
{
	data_->setTitleBackground(pixmap);
}

void Window::enableSizeGrip()
{
	data_->enableSizeGrip();
}

bool Window::sizeGripEnabled()
{
	return data_->size_girp_enabled;
}

void Window::setBackground(unique_ptr<QPixmap> pixmap)
{
	data_->setBackground(std::move(pixmap));
}

void Window::setMinFunc(std::function<void()>&& val)
{
	data_->setMinFunc(std::forward<std::function<void()>>(val));
}

void Window::setMaxFunc(std::function<void()>&& val)
{
	data_->setMaxFunc(std::forward<std::function<void()>>(val));
}

void Window::setCloseFunc(std::function<void()>&& val)
{
	data_->setCloseFunc(std::forward<std::function<void()>>(val));
}
