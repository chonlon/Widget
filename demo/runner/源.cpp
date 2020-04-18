#include "widget.h"
#include <QApplication>
#include "messagebox.h"

using namespace  lon;

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    Q_INIT_RESOURCE(lon_widget);
    Widget widget;
    widget.enableSizeGrip();
    widget.show();

    lon::MessageBox messagebox{"Ok", "hello"};
    messagebox.show();
    app.exec();
}
