#pragma once
#include <QDialog>

namespace lon {
class DialogPrivate;
class Dialog : public QDialog {
public:
    explicit Dialog(QWidget* parent = nullptr);

    ~Dialog() override;
private:
    friend class DialogPrivate;
    std::unique_ptr<DialogPrivate> data_;
};

}
