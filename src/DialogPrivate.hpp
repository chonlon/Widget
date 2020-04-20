#pragma once
#include "Dialog.h"
#include "Window.h"
#include <QLabel>

using lon::Window;
using lon::Button;
using std::unique_ptr;

namespace lon {
struct DialogPrivate {
    unique_ptr<Window> inner_window{nullptr};
    unique_ptr<QWidget> center_widget{nullptr};
    unique_ptr<QLabel> label{nullptr};
    unique_ptr<Button> ok_button{nullptr};
    unique_ptr<Button> cancel_button{nullptr};
    unique_ptr<QHBoxLayout> bottom_layout{nullptr};
    unique_ptr<QVBoxLayout> main_layout{nullptr};

    lon::Dialog* parent{nullptr};
};
}

