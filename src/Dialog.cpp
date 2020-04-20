#include "Dialog.h"
#include "DialogPrivate.hpp"

lon::Dialog::Dialog(QWidget* parent) : QDialog(parent)
{
    data_ = std::make_unique<DialogPrivate>();
    data_->inner_window = std::make_unique<lon::Window>(this, TitleBar::Buttons::CLOSE_MIN);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    this->resize(400, 300);
    data_->inner_window->setGeometry(0, 0, 400, 300);
}

lon::Dialog::~Dialog() = default;
