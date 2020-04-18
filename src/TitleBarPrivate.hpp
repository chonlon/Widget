#pragma once

#include "TitleBar.h"

using lon::Button;
using std::unique_ptr;

constexpr int32_t BUTTON_HEIGHT = 45;
constexpr int32_t BUTTON_WIDTH = 45;
constexpr int32_t TITLE_BAR_HEIGHT = 50;

namespace lon {

struct TitleBarPrivate : QObject {
Q_OBJECT
public:
    // todo: 使用 not_null 描述
    TitleBarPrivate(TitleBar* parent)
        : parent_(parent) {
        assert(parent && "the titlebar pointer cannot be empty");
    }

    // 点击最大化按钮以后需要更新一些控件
    void updateMaximize() {
        QWidget* pWindow = parent_->window();
        if (pWindow->isTopLevel()) {
            bool bMaximize = pWindow->isMaximized();
            if (bMaximize) {
                pmaximize_button_->setToolTip(tr("还原"));
                pmaximize_button_->setProperty("maximizeProperty", "restore");

                pmaximize_button_->setNormal(max_max_normal_);
                pmaximize_button_->setFocus(max_max_focus_);
                pmaximize_button_->setPressed(max_max_pressed_);
            } else {
                pmaximize_button_->setProperty("maximizeProperty", "maximize");
                pmaximize_button_->setToolTip(tr("最大化"));

                pmaximize_button_->setNormal(max_normal_normal_);
                pmaximize_button_->setFocus(max_normal_focus_);
                pmaximize_button_->setPressed(max_normal_pressed_);
            }
            // parent_->resize();
            pmaximize_button_->setStyle(QApplication::style());
        }
    }

    void initMaxIcons(uint32_t button) {
        const char maxn = 2;
        if ((button & maxn) != maxn)
            return;

        max_max_normal_.reset(new QIcon(":/icon/Resources/max_max_normal.png"));
        max_max_focus_.reset(new QIcon(":/icon/Resources/max_max_focus.png"));
        max_max_pressed_.reset(new QIcon(":/icon/Resources/max_max_pressed.png"));

        max_normal_normal_.reset(new QIcon(":/icon/Resources/max_normal_normal.png"));
        max_normal_focus_.reset(new QIcon(":/icon/Resources/max_normal_focus.png"));
        max_normal_pressed_.reset(new QIcon(":/icon/Resources/max_normal_pressed.png"));
    }

    void initWidgets(uint32_t button) {
        const char minn = 4;
        const char maxn = 2;

        //初始化最小化按钮
        if ((button & minn) == minn) {
            pminimize_button_ = new Button(new QIcon(":/icon/Resources/min_normal.png"),
                                           // normal
                                           new QIcon(":/icon/Resources/min_focus.png"),
                                           // focus
                                           new QIcon(":/icon/Resources/min_pressed.png"),
                                           // pressed
                                           parent_);
            pminimize_button_->setFlat(true);
            pminimize_button_->setStyleSheet("border:none");
            pminimize_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
            pminimize_button_->setObjectName("minimizeButton");
            pminimize_button_->setToolTip("最小化");
        }

        //初始化最大化按钮
        if ((button & maxn) == maxn) {
            pmaximize_button_ = new Button(parent_);

            pmaximize_button_->setNormal(max_normal_normal_);
            pmaximize_button_->setFocus(max_normal_focus_);
            pmaximize_button_->setPressed(max_normal_pressed_);
            pmaximize_button_->setFlat(true);
            pmaximize_button_->setStyleSheet("border:none");
            pmaximize_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
            pmaximize_button_->setObjectName("maximizeButton");
            pmaximize_button_->setToolTip("最大化");
        }
        // 初始化关闭按钮
        pclose_button_ = new Button(new QIcon(":/icon/Resources/close_normal.png"),
                                    // normal
                                    new QIcon(":/icon/Resources/close_focus.png"),
                                    // focus
                                    new QIcon(":/icon/Resources/close_pressed.png"),
                                    // pressedparent_
                                    parent_);
        pclose_button_->setFlat(true);
        pclose_button_->setStyleSheet("border:none");
        pclose_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
        pclose_button_->setObjectName("closeButton");
        pclose_button_->setToolTip("关闭窗口");

        // 初始化两个label
        icon_label_ = new QLabel(parent_);
        icon_label_->setFixedSize(30, 30);
        icon_label_->setScaledContents(true);

        title_label_ = new QLabel(parent_);
        title_label_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        title_label_->setObjectName("titleLable");
    }

    void initLayout(uint32_t button) {
        const char minn = 4;
        const char maxn = 2;
        title_bar_layout_ = new QHBoxLayout(parent_);
        title_bar_layout_->addWidget(icon_label_);
        title_bar_layout_->addSpacing(5);
        title_bar_layout_->addWidget(title_label_);
        title_bar_layout_->setSpacing(0);

        if ((button & minn) == minn)
            title_bar_layout_->addWidget(pminimize_button_);
        if ((button & maxn) == maxn)
            title_bar_layout_->addWidget(pmaximize_button_);
        title_bar_layout_->addWidget(pclose_button_);

        title_bar_layout_->setContentsMargins(5, 0, 0, 0);

        parent_->setLayout(title_bar_layout_);
    }

    void initConnection(uint32_t button) {
        const char minn = 4;
        const char maxn = 2;

        if ((button & minn) == minn)
            connect(pminimize_button_, SIGNAL(clicked(bool)), parent_, SLOT(onButtonClicked()));
        if ((button & maxn) == maxn)
            connect(pmaximize_button_, SIGNAL(clicked(bool)), parent_, SLOT(onButtonClicked()));
        connect(pclose_button_, SIGNAL(clicked(bool)), parent_, SLOT(onButtonClicked()));
    }

    void mousePressEvent(QMouseEvent* event) {
        if (parent_->window()->isMaximized())
            return;

        is_pressed_ = true;
        move_start_position_ = event->globalPos();

    }

    void mouseMoveEvent(QMouseEvent* event) {
        if (!is_pressed_)
            return;

        QPoint move_point = event->globalPos() - move_start_position_;
        QPoint widget_pos = parent_->window()->pos();

        move_start_position_ = event->globalPos();
        parent_->window()->move(widget_pos.x() + move_point.x(), widget_pos.y() + move_point.y());
    }

    void mouseReleaseEvent(QMouseEvent* event) {
        is_pressed_ = false;

    }

    bool eventFilter(QObject* obj, QEvent* event) {
        switch (event->type()) {
            case QEvent::WindowTitleChange: {
                QWidget* pWidget = qobject_cast<QWidget*>(obj);
                if (pWidget) {
                    title_label_->setText(pWidget->windowTitle());
                    return true;
                }
                return false;
            }
            case QEvent::WindowIconChange: {
                QWidget* pWidget = qobject_cast<QWidget*>(obj);
                if (pWidget) {
                    QIcon icon = pWidget->windowIcon();
                    icon_label_->setPixmap(icon.pixmap(icon_label_->size()));
                    return true;
                }
                return false;
            }
            case QEvent::WindowStateChange:
            case QEvent::Resize:
                this->updateMaximize();
                return true;
            default:
                return false;
        }
    }

    void initTitleBar(TitleBar::Buttons button) {
        is_pressed_ = false;
        pixmap_ = nullptr;

        parent_->resize(parent_->width(), TITLE_BAR_HEIGHT);
        parent_->setFixedHeight(TITLE_BAR_HEIGHT);
        auto _button = static_cast<uint32_t>(button);
        initMaxIcons(_button);
        initWidgets(_button);
        initLayout(_button);
        initConnection(_button);

        min_func_ =
            [this]()
            {
                if (parent_->window()->isTopLevel())
                    parent_->window()->showMinimized();
            };
        max_func_ =
            [this]()
            {
                if (parent_->window()->isTopLevel())
                    parent_->window()->isMaximized()
                        ? parent_->window()->showNormal()
                        : parent_->window()->showMaximized();
                this->updateMaximize();
            };
        close_func_ =
            [this]()
            {
                if (parent_->window()->isTopLevel())
                    parent_->window()->close();
            };
    }

    void setTitleIcon(const QIcon& icon) {
        icon_label_->setPixmap(icon.pixmap(icon_label_->size()));
    }

    void setBackground(QPixmap* pixmap) {
        parent_->setAutoFillBackground(true);
        //判断图片是否为空
        if (pixmap->isNull()) {
            qDebug() << tr("illege arguments") << endl;
            return;
        }
        //设置窗口的背景
        QPalette palette = parent_->palette();
        palette.setBrush(
            parent_->backgroundRole(),
            QBrush(pixmap->scaled(parent_->size(),
                                  Qt::IgnoreAspectRatio,
                                  Qt::SmoothTransformation)));
        parent_->setPalette(palette);
        pixmap_ = pixmap;
    }

    void resizeEvent(QResizeEvent* event) {
        if (pixmap_ == nullptr)
            return;
        if (pixmap_->isNull())
            return;
        this->setBackground(pixmap_);
    }

    void setTitle(const QString& title) {
        title_label_->setText(title);
    }

    void onButtonClicked(QPushButton* pButton) {
        if (pButton == pminimize_button_) {
            emit parent_->minimizeButtonClicked();
            min_func_();
        } else if (pButton == pmaximize_button_) {
            emit parent_->maximizeButtonClicked();
            max_func_();
        } else if (pButton == pclose_button_) {
            emit parent_->closeButtonClicked();
            close_func_();
        }
    }

    QLabel* icon_label_;
    QLabel* title_label_;

    Button* pminimize_button_;
    Button* pmaximize_button_;
    Button* pclose_button_;

    std::shared_ptr<QIcon> max_max_normal_;
    std::shared_ptr<QIcon> max_max_focus_;
    std::shared_ptr<QIcon> max_max_pressed_;

    std::shared_ptr<QIcon> max_normal_normal_;
    std::shared_ptr<QIcon> max_normal_focus_;
    std::shared_ptr<QIcon> max_normal_pressed_;

    QPixmap* pixmap_;

    QHBoxLayout* title_bar_layout_;

    bool is_pressed_;
    QPoint move_start_position_;

    // actions titlebar will exec when specific button clicked.
    std::function<void(void)> min_func_;
    std::function<void(void)> max_func_;
    std::function<void(void)> close_func_;

    lon::TitleBar* parent_;
};

}
