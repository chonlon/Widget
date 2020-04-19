#include <QApplication>
#include "messagebox.h"
#include "Window.h"

using namespace  lon;

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    Q_INIT_RESOURCE(lon_widget);
    Window widget;
    widget.enableSizeGrip();
    widget.setTitleBackground(std::make_unique<QPixmap>(":/icon/Resources/back.png"));
    widget.show();

    lon::MessageBox messagebox{"Ok", "hello"};
    messagebox.show();
    app.exec();
}
