#ifndef WALL_H
#define WALL_H

#include <QObject>
#include"EveryThing.h"
class Wall : public EveryThing
{
public:
    //构造函数，传入参数为墙方向，墙的位置坐标
    Wall(int id,int x,int y);
    //单独保存墙的方向
    int id;
    int getId(){return id;}
    //
    QRectF boundingRect()const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // WALL_H
