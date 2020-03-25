#include "widget.h"
#include <QApplication>

using namespace  lon;

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    Q_INIT_RESOURCE(lon_widget);
    Widget widget;
    widget.enabelSizeGrip();
    widget.show();
    app.exec();
}
