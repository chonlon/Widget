#include <QApplication>
#include "messagebox.h"
#include "Window.h"
#include "Dialog.h"
#include "ShadowWindow.h"

using namespace lon;

class DisplayWidget : public QWidget {
public:
    DisplayWidget() {
        // Q_INIT_RESOURCE(lon_widget);
        widget.enableSizeGrip();
        widget.setTitleBackground(std::make_unique<QPixmap>(":/icon/Resources/back.png"));


        shadow.setTitleBackground(std::make_unique<QPixmap>(":/icon/Resources/back.png"));

        shadow.setBackground(std::make_unique<QPixmap>(
            "D:\\1_code\\1_Cpp\\3_1_mine\\temp\\tomatoclock\\bin\\res\\gui\\Res\\Img\\background.png"));
        shadow.enableSizeGrip();
        normal_shadow.setWidgetBackGround(Qt::red);
        
        normal_shadow.enableSizeGrip();

        w_button.setText("Widget");
        w_button.setFlat(true);
        s_button.setText("ShadowWindow");
        d_button.setText("Dialog");
        m_button.setText("MessageBox");
        w_button.setNormal(std::make_shared<QIcon>(":/icon/Resources/button.png"));
        n_button.setText("normal shadow");


        connect(&w_button,
                &QPushButton::clicked,
                [this]()
                {
                    widget.show();
                });
        connect(&s_button,
                &QPushButton::clicked,
                [this]()
                {
                    shadow.show();
                });
        connect(&d_button,
                &QPushButton::clicked,
                [this]()
                {
                    dialog.exec();
                });
        connect(&m_button,
                &QPushButton::clicked,
                [this]()
                {
                    //new lon::MessageBox{"hello", "world"};
                });
        connect(&n_button,
                &QPushButton::clicked,
                [this]()
                {
                    normal_shadow.show();
                });

        layout.setSpacing(0);
        layout.addWidget(&w_button);
        layout.addWidget(&d_button);
        layout.addWidget(&s_button);
        layout.addWidget(&m_button);
        layout.addWidget(&n_button);
        this->setLayout(&layout);
    }

private:
    Window widget;
    Dialog dialog;
    ShadowWindow shadow;
    ShadowWindow normal_shadow{nullptr, Qt::green};

    QVBoxLayout layout;
    Button w_button;
    Button d_button;
    Button s_button;
    Button m_button;
    Button n_button;
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    Q_INIT_RESOURCE(lon_widget);

    DisplayWidget w;
    w.resize(600, 400);
    w.show();

    auto shadow_box_ = new ShadowBox{gsl::owner<lon::Window*>(new lon::Window)};
    shadow_box_->setWidgetBackGround(Qt::green);
    shadow_box_->resize(400, 400);
    shadow_box_->show();

    ShadowBox s{new QWidget};
    s.setWidgetBackGround(Qt::red);
    s.resize(400, 400);
    s.show();

    app.exec();
}
