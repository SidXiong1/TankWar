#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>
#include<QPainter>
#include<HelpWidget.h>
#include<MainWidget.h>
#include<GameRecord.h>
namespace Ui {
class StartWidget;
}

class StartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StartWidget(QWidget *parent = 0);
    ~StartWidget();
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *) override;


    MainWidget *mw;
    HelpWidget *hw;
    GameRecord *gw;
private:
    Ui::StartWidget *ui;
    QImage *backGround;
    int status = 0;
    QPainter paint;
 private slots:

};

#endif // STARTWIDGET_H
