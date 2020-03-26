﻿#ifndef LON_WIDGET
#define LON_WIDGET

#include "titlebar.h"
#include <memory>
#include <QSizeGrip>
#include <QGraphicsDropShadowEffect>
class WidgetPrivate;
class QLayout;

namespace lon {
/// 统一样式的widget订制.
/// 其实也只是一个简单的封装.
/// 如果某些地方不符合需要, 可以自定义窗口,
/// 但是务必使用lon::TitleBar以保持统一风格.
// 因为不是很确定bottom的界面具体情况, 如果是需要在默认的情况下绑定信号与槽的话
// 需要使用bottomBar()函数获得bottomBar的指针
/// <summary>
/// 统一样式的Widget.
/// 不允许自己定义layout(因为会破环titlebar),
/// 只允许对centerWidget和botttomWidget进行操作(包括替换).
///	</summary>


class Widget : public QWidget {
    Q_OBJECT
private:
    friend class WidgetPrivate;
    std::unique_ptr<WidgetPrivate> data_;

private:
    // 禁用setlayout, 只允许操作centerWidget和botttomWidget.
    virtual void setLayout(QLayout*) {}

    void initLayout() const;

    void initBottomBar() const;

    void initConnect() const;

    void initWidgets() const;

    void updateBackground() {
        update();
    }
protected:
    void resizeEvent(QResizeEvent* event) override {
        return QWidget::resizeEvent(event);
    }

    void paintEvent(QPaintEvent* event) override;

public:
    explicit Widget(QWidget* parent = nullptr, TitleBar::Buttons status = TitleBar::ALL);

    explicit Widget(QWidget* center_widget, QWidget* bottom_bar, QWidget* parent = nullptr);

    virtual ~Widget();

    /// <summary> 返回中间栏的widget指针. </summary>
    QWidget* centerWidget() const;

    /// <summary> 设置自定义的bottombar. </summary>
    /// 注意: 重新设置bottomBar会导致默认生成的按钮的信号与槽的失效.
    /// 此类会获取次widget的所有权.
    virtual bool setBottomBar(QWidget* widget);

    /// <summary> 设置自定义的centerwidget. </summary>
    /// 此类会获得widget的所有权.
    virtual bool setCenterWidget(QWidget* widget);

    /// <summary> 返回底部栏的widget指针. </summary>
    QWidget* bottomBar() const;

    virtual void setTitle(const QString& title);

    virtual void setTitleIcon(const QIcon& icon);

    // this class will take pixmap's ownship
    virtual void setTitleBackground(QPixmap* pixmap);

    virtual void enableSizeGrip();

    virtual bool sizeGripEnabled();

    // this class will take pixmap's ownship
    virtual void setBackground(QPixmap* pixmap);

    /// <summary>
    /// 设置最小化按钮按下后的执行函数
    /// </summary>
    /// <param name="val"> 执行函数, std::function<void> </param>
    virtual void setMinFunc(std::function<void(void)>&& val);

    /// <summary>
    /// 设置最大化按钮按下后的执行函数
    /// </summary>
    /// <param name="val"> 执行函数, std::function<void> </param>
    virtual void setMaxFunc(std::function<void(void)>&& val);

    /// <summary>
    /// 关闭按钮按下后的执行函数
    /// </summary>
    /// <param name="val"> 执行函数, std::function<void> </param>
    virtual void setCloseFunc(std::function<void(void)>&& val);

signals:
    void okButtonClicked();
    void cancelButtonClicked();
    void minimizeButtonClicked();
    void maximizeButtonClicked();
    void closeButtonClicked();
    void sizeChanged(QResizeEvent* event);
private slots:
    void onOkButtonClicked() {
        emit okButtonClicked();
    }

    void onCancelButtonClicked() {
        emit cancelButtonClicked();
    }
};



class ShadowWindow : public QWidget {
Q_OBJECT
public:
    explicit ShadowWindow(QWidget* contentWidget, QWidget* parent = nullptr)
        : QWidget(parent) {
        setWindowFlags(Qt::FramelessWindowHint);     // 去掉边框
        setAttribute(Qt::WA_TranslucentBackground);  // 背景透明

        // 添加阴影
        QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(contentWidget);
        shadowEffect->setColor(Qt::lightGray);
        shadowEffect->setBlurRadius(6);  // 阴影的大小
        shadowEffect->setOffset(0, 0);
        contentWidget->setGraphicsEffect(shadowEffect);

        // 添加到窗口中
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(contentWidget);
        layout->setContentsMargins(4, 4, 4, 4);  // 注意和阴影大小的协调
        setLayout(layout);
        connect(contentWidget,
                SIGNAL(sizeChanged(QResizeEvent*)),
                this,
                SLOT(sizeChanged(QResizeEvent*)));
    }

public slots:
    void sizeChanged(QResizeEvent* event) {
        this->resize(event->size().width() + 8, event->size().height() + 8);
    }
};
}  // namespace lon

#endif