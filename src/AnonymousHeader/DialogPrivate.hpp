#pragma once
#include "Dialog.h"
#include <ShadowWindow.h>
#include <QLabel>
#include <gsl/gsl>

using std::unique_ptr;

namespace lon {
class DialogPrivate {
public:
    ShadowWindow* inner_window{nullptr};
    Button* ok_button{nullptr};
    Button* cancel_button{nullptr};

    QWidget* center_widget{nullptr};
    QLabel* content_label{nullptr};
    QHBoxLayout* bottom_layout{nullptr};
    QVBoxLayout* main_layout{nullptr};

    QVBoxLayout* layout{nullptr};

    DialogPrivate(gsl::not_null<Dialog*> parent, int types) {
        parent_ = parent;
        layout = new QVBoxLayout{parent_};
        inner_window = new lon::ShadowWindow(parent_, Qt::lightGray, Qt::lightGray,  20,TitleBar::Buttons::CLOSE_MIN);
        layout->addWidget(inner_window);
        center_widget = new QWidget{inner_window};

        initButtons(types);
        auto content_widget = new QWidget();
        main_layout = new QVBoxLayout{content_widget};
        main_layout->addWidget(center_widget, 1);
        main_layout->addLayout(bottom_layout, 0);
        main_layout->setSpacing(0);
        inner_window->setCenterWidget(content_widget);

        parent_->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
        parent_->resize(400, 300);
        inner_window->setGeometry(0, 0, 400, 300);
        QObject::connect(inner_window, &ShadowWindow::closeButtonClicked, [this]()
        {
            parent_->reject();
        });
        parent_->setAttribute(Qt::WA_TranslucentBackground);
    }

    auto setCenterWidget(QWidget* widget) -> void {
        main_layout->replaceWidget(center_widget, widget);
        delete center_widget;
        center_widget = widget;
    }
private:
    void initButtons(int types) {
        bottom_layout = new QHBoxLayout{};
        if(types | Dialog::Ok) {
            ok_button = new Button{center_widget};
            ok_button->setText(u8"确认");
            bottom_layout->addWidget(ok_button);
            QObject::connect(ok_button, &QPushButton::clicked, [this]()
            {
                parent_->accept();
            });
        }

        if(types | Dialog::Cancel) {
            bottom_layout->addSpacerItem(new QSpacerItem{10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum});
            cancel_button = new Button{center_widget};
            cancel_button->setText(u8"取消");
            bottom_layout->addWidget(cancel_button);
            QObject::connect(cancel_button, &QPushButton::clicked, [this]()
            {
                parent_->reject();
            });
        }
    }
    lon::Dialog* parent_{nullptr};
};
}
