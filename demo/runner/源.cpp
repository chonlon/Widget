#include <QApplication>
#include <iostream>
#include <QLabel>
#include "messagebox.h"
#include "Window.h"
#include "Dialog.h"
#include "ShadowWindow.h"
#include "Toast.h"


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
        s_button.setText("ShadowWindow");
        s_button.setNormal(std::make_shared<QIcon>("C:\\Users\\lon\\Downloads\\Button.png"));
        s_button.setFocus(std::make_shared<QIcon>("C:\\Users\\lon\\Downloads\\Button1.png"));
        s_button.setPressed(std::make_shared<QIcon>("C:\\Users\\lon\\Downloads\\Button2.png"));
        d_button.setText("Dialog");
        d_button.setStyleSheet(
            "QPushButton{background-color:rgba(255,178,0,100%);\
             color: white;   border-radius: 10px;  border: 2px groove gray; border-style: outset;}"
            // 按键本色
            "QPushButton:hover{background-color:white; color: black;}" // 鼠标停放时的色彩
            "QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }");
        m_button.setText("MessageBox");
        m_button.setStyleSheet("/*按钮普通态*/"
            "QPushButton"
            "{"
            "    /*字体为微软雅黑*/"
            "    font-family:Microsoft Yahei;"
            "    /*字体大小为20点*/"
            "    font-size:20pt;"
            "    /*字体颜色为白色*/    "
            "    color:white;"
            "    /*背景颜色*/  "
            "    background-color:rgb(14 , 150 , 254);"
            "    /*边框圆角半径为8像素*/ "
            "    border-radius:8px;"
            "}"
            ""
            "/*按钮停留态*/"
            "QPushButton:hover"
            "{"
            "    /*背景颜色*/  "
            "    background-color:rgb(44 , 137 , 255);"
            "}"
            ""
            "/*按钮按下态*/"
            "QPushButton:pressed"
            "{"
            "    /*背景颜色*/  "
            "    background-color:rgb(14 , 135 , 228);"
            "    /*左内边距为3像素，让按下时字向右移动3像素*/  "
            "    padding-left:3px;"
            "    /*上内边距为3像素，让按下时字向下移动3像素*/  "
            "    padding-top:3px;"
            "}");
        w_button.setNormal(std::make_shared<QIcon>(":/icon/Resources/button.png"));
        n_button.setText("normal shadow");
        n_button.setStyleSheet("QPushButton{border-image: url(:/icon/Resources/button.png);}");
        //n_button.setStyleSheet("QPushButton:hover{border-image: url(C:\\Users\\lon\\Downloads\\Button1.png)}");
        //n_button.setStyleSheet("QPushButton:pressed{border-image: url(C:\\Users\\lon\\Downloads\\Button2.png)}");

        QLabel* w1{new QLabel{"test test"}};
        promoted_window = promoteToWindow(w1);
        QMessageBox* w2 = new QMessageBox;
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
        connect(&promote_window_button,
                &QPushButton::clicked,
                [this]()
                {
                    promoted_window->show();
                });
        connect(&promote_shadow_window_button,
                &QPushButton::clicked,
                [this, w2]()
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
    DisplayWidget* w;
    try {
        w = new DisplayWidget{};
    } catch (std::bad_alloc& e) {
        std::cout << "out of memory usage";
        w = nullptr;
    }
    if (w) {
        w->resize(600, 400);
        w->show();
    }
    popUpOneToast("hello worldssssssssssssssssssssssssssssssssssssss");

    app.exec();
}
