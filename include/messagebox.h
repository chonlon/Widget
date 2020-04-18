#ifndef LON_MESSAGEBOX
#define LON_MESSAGEBOX

#include <QMessageBox>
#include "Window.h"


namespace lon {
// todo 实现模态.
class MessageBox : public Window {
    Q_OBJECT
private:
    QLabel* text_label_p_;
    QBoxLayout* center_layout_p_;

public:
    MessageBox(const QString& title, const QString& message, QWidget* parent = nullptr);
};

}  // namespace lon
#endif
