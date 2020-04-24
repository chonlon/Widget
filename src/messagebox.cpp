#include "messagebox.h"
#include <QLabel>

using namespace lon;
MessageBox::MessageBox(const QString& title, const QString& message, QWidget* parent)
    : Window(parent) {
    setTitle(title);

    text_label_p_ = new QLabel(this);
    text_label_p_->setText(message);

    center_layout_p_ = new QHBoxLayout(this);
    center_layout_p_->addStretch();
    center_layout_p_->addWidget(text_label_p_);
    center_layout_p_->addStretch();

    centerWidget().setLayout(center_layout_p_);

    this->setWindowFlag(Qt::Dialog);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->show();
}
