#ifndef LON_TITLEBAR
#define LON_TITLEBAR

#include "button.h"
#include <QWidget>
#include <functional>
#include <memory>

#pragma execution_character_set("utf-8")

namespace lon {
class TitleBarPrivate;
class TitleBar : public QWidget {
Q_OBJECT
public:
    // 标题栏的按钮状态
    // 二进制最后一位为1表示close开
    // 倒数第二位为1表示max开
    // 倒数第三位为1表示min开
    enum class Buttons { CLOSE = 1, CLOSE_MAX = 3, CLOSE_MIN = 5, ALL = 7 };

    /// <summary> parent不能为空. </summary>
    /// <param name: button> 用于选择最大化以及最小化按钮是否添加. </param>
    explicit TitleBar(QWidget* parent, Buttons button = Buttons::ALL);

    /// <summary> 以传入参数设置title</summary>
    virtual void setTitle(const QString& title);

    /// <summary> 以传入的icon设置TitleBar的icon </summary>
    virtual void setTitleIcon(const QIcon& icon);

    /// <summary> 以传入的icon设置TitleBar的背景</summary>
    virtual void setBackground(std::unique_ptr<QPixmap> pixmap);

    //todo 设置接口使用万能引用.

    /// <summary>
    /// 设置最小化按钮按下后的执行函数
    /// </summary>
    /// <param name="val"> 执行函数, std::function<void> </param>
    void setMinFunc(std::function<void(void)>&& val);

    /// <summary>
    /// 设置最大化按钮按下后的执行函数
    /// </summary>
    /// <param name="val"> 执行函数, std::function<void> </param>
    void setMaxFunc(std::function<void(void)>&& val);

    /// <summary>
    /// 关闭按钮按下后的执行函数
    /// </summary>
    /// <param name="val"> 执行函数, std::function<void> </param>
    void setCloseFunc(std::function<void(void)>&& val);

    virtual ~TitleBar();
protected:
    /// 双击标题栏进行界面的最大化/还原
    void mouseDoubleClickEvent(QMouseEvent* event) override;

    // 按住titlebar会进行窗口的拖放
    // 事实上是使用下面三个函数(press, move, release)计算按下时移动距离
    // 在press的时候进行计算
    // 并在release的时候结束计算
    void mousePressEvent(QMouseEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void mouseReleaseEvent(QMouseEvent* event) override;

    void resizeEvent(QResizeEvent* event) override;

    void paintEvent(QPaintEvent* event) override;

    /// 设置默认界面标题与图标
    bool eventFilter(QObject* obj, QEvent* event) override;

signals:
    void minimizeButtonClicked();
    void maximizeButtonClicked();
    void closeButtonClicked();
private slots:
    void onButtonClicked();
private:
    void updateBackground() {
        update();
    }

    friend class TitleBarPrivate;
    std::unique_ptr<TitleBarPrivate> data_;
};

} // namespace lon

#endif
