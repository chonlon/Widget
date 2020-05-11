﻿#include <QApplication>
#include <iostream>
#include <QLabel>
#include "messagebox.h"
#include "Window.h"
#include "Dialog.h"
#include "ShadowWindow.h"



using namespace lon;

class DisplayWidget : public QWidget {
public:
    DisplayWidget() {
        // Q_INIT_RESOURCE(lon_widget);
        widget.setSizeGripEnable();
        widget.setTitleBackground(std::make_unique<QPixmap>(":/icon/Resources/back.png"));


        shadow.setTitleBackground(std::make_unique<QPixmap>(":/icon/Resources/back.png"));

        shadow.setBackground(std::make_unique<QPixmap>(
            "D:\\1_code\\1_Cpp\\3_1_mine\\temp\\tomatoclock\\bin\\res\\gui\\Res\\Img\\background.png"));
        shadow.setSizeGripEnable();
        normal_shadow.setWidgetBackGround(Qt::red);
        
        normal_shadow.setSizeGripEnable();

        w_button.setText("Window");
        w_button.setFlat(true);
        s_button.setText("ShadowWindow");
        d_button.setText("Dialog");
        m_button.setText("MessageBox");
        w_button.setNormal(std::make_shared<QIcon>(":/icon/Resources/button.png"));
        n_button.setText("normal shadow");
        QLabel *w1{new QLabel{"test test"}};
        promoted_window = promoteToWindow(w1);
        QMessageBox *w2 = new QMessageBox;
        w2->setWindowTitle("11");
        w2->setText("22");
        promoted_shadow_window = promoteToShadowWindow(w2);
        promoted_shadow_window->resize(400, 300);
        promote_window_button.setText(u8"提升窗口");
        promote_shadow_window_button.setText(u8"提升阴影窗口");

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
        connect(&promote_window_button, &QPushButton::clicked, [this]()
        {
            promoted_window->show();
        });
        connect(&promote_shadow_window_button, &QPushButton::clicked, [this, w2]()
        {
            w2->exec();
            promoted_shadow_window->show();
        });

        layout.setSpacing(0);
        layout.addWidget(&w_button);
        layout.addWidget(&d_button);
        layout.addWidget(&s_button);
        layout.addWidget(&m_button);
        layout.addWidget(&n_button);
        layout.addWidget(&promote_window_button);
        layout.addWidget(&promote_shadow_window_button);

        this->setLayout(&layout);
    }

private:
    Window widget;
    Dialog dialog{nullptr, Dialog::Ok | Dialog::Cancel};
    ShadowWindow shadow;
    ShadowWindow normal_shadow{nullptr, Qt::green, Qt::red};
    std::unique_ptr<Window> promoted_window;
    std::unique_ptr<ShadowWindow> promoted_shadow_window;

    QVBoxLayout layout;
    Button w_button;
    Button d_button;
    Button s_button;
    Button m_button;
    Button n_button;
    Button promote_window_button;
    Button promote_shadow_window_button;
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    Q_INIT_RESOURCE(lon_widget);
    DisplayWidget *w;
    try {
        w = new DisplayWidget{};
    } catch (std::bad_alloc& e) {
        std::cout << "out of memory usage";
        w = nullptr;
    }
    if(w) {
        w->resize(600, 400);
        w->show();
    }
    

    app.exec();
}
