#ifndef LON_MESSAGEBOX
#define LON_MESSAGEBOX

#include "widget.h"

#include <QMessageBox>


namespace lon {
// todo 实现模态.
class MessageBox : public Widget {
    Q_OBJECT
private:
    QLabel* text_label_p_;
    QBoxLayout* center_layout_p_;

public:
    MessageBox(const QString& title, const QString& message, QWidget* parent = nullptr);


private slots:
    void onOkButtonClicked() {
        window()->close();
    }
    void onCancleButtonClicked() {
        window()->close();
    }
};

}  // namespace lon
#endif
