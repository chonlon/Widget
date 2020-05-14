#pragma once

#include <QtWidgets/QWidget>
#include <QTimer>

class QLabel;
class QHBoxLayout;

namespace lon {
class Toast : public QWidget
{
Q_OBJECT
public:

     /**
     * \brief toast窗口, 默认情况下, 窗口将会在parent的中心位置弹出.
     * \param msg 显示消息.
     * \param parent Toast父窗口. 为空将会在屏幕正中心弹出Toast.
     */
    Toast(const QString& msg, QWidget* parent = nullptr);


    /**
     * \brief popUp Toast at default position.
     */
    void popUp();
    /**
     * \brief popUp Toast at specific position point.
     * \param point position.
     */
    void popUp(const QPoint& point);

    void setFont(const QFont font);
protected:
    void paintEvent(QPaintEvent* event) override;
private:
    void updateRender();

    QTimer timer_;
    QLabel* label_{nullptr};
    QHBoxLayout* main_layout_;
    QWidget* parent_{nullptr};
};


/**
 * \brief popUp Toast at default position.
 * \param msg 显示信息
 * \param parent Toast父窗口. 为空将会在屏幕正中心弹出Toast. 否则, 窗口将会在parent的中心位置弹出.
 */
void popUpOneToast(const QString& msg, QWidget* parent = nullptr);
/**
 * \brief 在指定位置弹出Toast
 * \param msg 显示信息
 * \param point 位置
 */
void popUpOneToast(const QString& msg, const QPoint& point);

}
