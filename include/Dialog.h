#pragma once
#include <QDialog>
#include <gsl/gsl>

namespace lon {
class DialogPrivate;
class Dialog : public QDialog {
public:
    enum ButtonType { None = 0, Ok = 1, Cancel = 1 << 1 };
    explicit Dialog(QWidget* parent = nullptr, int types = ButtonType::None);

    ~Dialog() override;

    void setCenterWidget(gsl::not_null<QWidget*> widget) const;
private:
    friend class DialogPrivate;
    std::unique_ptr<DialogPrivate> data_;
};
}
