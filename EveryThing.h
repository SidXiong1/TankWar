#ifndef EVERYTHING_H
#define EVERYTHING_H

#include <QObject>
#include <QGraphicsItem>
#include<QPainter>
#include<QtMath>
enum TYPES{ TANK , BULLET , WALL, PROP};//枚举类型 tank,bullet,wall
#define PI  3.1415926
class EveryThing :public QObject ,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit EveryThing(QObject *parent = nullptr);

    virtual int getId()
    {
        return id;
    }
    TYPES wtype;//标记对象类型
    int id;//表记对象Id
    int angle;//标记对象角度
    QPixmap pix;//标记对象图标
signals:

public slots:
};

#endif // EVERYTHING_H
