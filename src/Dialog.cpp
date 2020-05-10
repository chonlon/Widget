#include "Dialog.h"
#include "DialogPrivate.hpp"

lon::Dialog::Dialog(QWidget* parent, int types) : QDialog(parent)
{
    data_ = std::make_unique<DialogPrivate>(this, types);
}

lon::Dialog::~Dialog() = default;

void lon::Dialog::setCenterWidget(gsl::not_null<QWidget*> widget) const {
    data_->setCenterWidget(widget);
}

