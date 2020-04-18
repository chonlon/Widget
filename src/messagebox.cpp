#include "messagebox.h"

using namespace lon;
MessageBox::MessageBox(const QString& title, const QString& message, QWidget* parent)
    : Widget(parent) {
    setTitle(title);

    text_label_p_ = new QLabel(this);
    text_label_p_->setText(message);

    center_layout_p_ = new QHBoxLayout(this);
    center_layout_p_->addStretch();
    center_layout_p_->addWidget(text_label_p_);
    center_layout_p_->addStretch();

    centerWidget()->setLayout(center_layout_p_);

    this->setWindowFlag(Qt::Dialog);
    //this->setCloseFunc([this]() { this->close(); });
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->show();
}
