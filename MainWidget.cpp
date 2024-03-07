#include "MainWidget.h"
#include<QApplication>
#include<QDebug>

int MainWidget::propNum=0;
Tank *play1,*play2;
Map *mymap;
int OVER = 0;
MainWidget::MainWidget()
{

    score1=0;
    score2=0;
    startTimer(100);
    pix1.load(":/pic/Tank1(1)(1).png");
    pix2.load(":/pic/Tank2(1)(1).png");
    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sound/TankBomb.wav"));
    lcd = new QLCDNumber(this);
      lcd1=new QLCDNumber(this);
      //���þ���ܿؼ�QLCDNumber����ʾ��λ��
      lcd->setDigitCount(3);
      lcd1->setDigitCount(3);
      //������ʾ��ģʽΪʮ����
      lcd->setMode(QLCDNumber::Dec);
      lcd1->setMode(QLCDNumber::Dec);
      //������ʾ��ʽ
      lcd->setSegmentStyle(QLCDNumber::Flat);
      lcd1->setSegmentStyle(QLCDNumber::Flat);
      lcd->setGeometry(1000,300,200,100);
      lcd1->setGeometry(1000,500,200,100);
      lcd->display(score1);
      lcd1->display(score2);

}
MainWidget::~MainWidget()
{
//    qDebug()<<"������������";
    QString path = QApplication::applicationDirPath();
    path+="/GameRecord.txt";
    qDebug()<<path;
    QFile file(path);
    if(file.open(QIODevice::WriteOnly)){
        file.write((char*)(score1));
        file.write("sssss");
        file.close();
        qDebug()<<"�ļ���д��:"<<path;
    }
}
void MainWidget::Display()
{
    lcd->display(score1);
    lcd1->display(score2);

    auto *scene = new QGraphicsScene(this);
    scene->setSceneRect(QRectF(0,0,this->width(),this->height()));
    //����scenne���Ͻǵ�Ϊ���ڵ����Ͻǣ����߶ȺͿ�����ó�view�Ŀ��
    this->setStyleSheet("padding: 0px; border: 0px;");//�����߿�
    mymap=new Map;
    for(int i =0;i<8;i++)
    {
        Wall * w =new Wall(2,50-16,(i+1)*100-16);
        mymap->wall.push_back(w);
        scene->addItem(w);
        Wall * w2 =new Wall(1,(i+1)*100-16,50-16);
        mymap->wall.push_back(w2);
        scene->addItem(w2);
    }
    for(int i =0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(mymap->cell[i][j].right==true)
            {
//                if(j==7||(i!=j&&rand()%15))
                {
                Wall * w =new Wall(2,50+(j+1)*100-16,100+i*100-16);
                mymap->wall.push_back(w);
                scene->addItem(w);
                }
            }
            if(mymap->cell[i][j].down==true)
            {
//                if(i==7||(i!=7&&rand()%15))
                {
                Wall * w =new Wall(1,100+j*100-16,50+(i+1)*100-16);
                mymap->wall.push_back(w);
                scene->addItem(w);
                }
            }
        }
    }
    play1=new Tank(1,(rand()%8*100+80),(rand()%8*100+80),rand()%4);                                   //�½�����̹�˶���
    play2=new Tank(2,(rand()%8*100+80),(rand()%8*100+80),rand()%4);
    scene->addItem(play1);                                     //���item��������
    play1->setPos(play1->posx,play1->posy);                                   //�������ԭ���ڴ������м�
    scene->addItem(play2);
    play2->setPos(play2->posx,play2->posy);
    QGraphicsPixmapItem *tank1=new QGraphicsPixmapItem(pix1);
    tank1->setPos(900,310);
    QGraphicsPixmapItem *tank2=new QGraphicsPixmapItem(pix2);
    tank2->setPos(900,510);
    scene->addItem(tank1);
    scene->addItem(tank2);
    this->setScene(scene);
    this->show();
    PropTime = new QTimer(this);
    PropTime->start(6000);
    connect(PropTime,&QTimer::timeout,[=](){
        if(propNum<3)
        {
        int PropChoose = rand()%2;
        if(PropChoose==0)
        {
            BombProp * x= new BombProp((rand()%8*100+80),(rand()%8*100+80));
            scene->addItem(x);

        }
        else
        {
            Gartin * x= new Gartin((rand()%8*100+80),(rand()%8*100+80));
            scene->addItem(x);
        }
        propNum++;
        }
    });

}

void MainWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
        case (Qt::Key_Up):
            play1->UP = true;
            break;
        case (Qt::Key_Down):
            play1->DOWN = true;
            break;
        case (Qt::Key_Left):
            play1->LEFT = true;
            break;
        case (Qt::Key_Right):
            play1->RIGHT = true;
            break;
        case (Qt::Key_Slash):
            play1->FIRE = true;
            break;
        case (Qt::Key_W):
            play2->UP = true;
            break;
        case (Qt::Key_S):
            play2->DOWN = true;
            break;
        case (Qt::Key_A):
            play2->LEFT = true;
            break;
        case (Qt::Key_D):
            play2->RIGHT = true;
            break;
        case (Qt::Key_G):
            play2->FIRE = true;
            break;
        default:
            break;
}
}
void MainWidget::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key()){
        case (Qt::Key_Up):
            play1->UP = false;
            break;
        case (Qt::Key_Down):
            play1->DOWN = false;
            break;
        case (Qt::Key_Left):
            play1->LEFT = false;
            break;
        case (Qt::Key_Right):
            play1->RIGHT = false;
            break;
        case (Qt::Key_Slash):
            play1->FIRE = false;
            break;
        case (Qt::Key_W):
            play2->UP = false;
            break;
        case (Qt::Key_S):
            play2->DOWN = false;
            break;
        case (Qt::Key_A):
            play2->LEFT = false;
            break;
        case (Qt::Key_D):
            play2->RIGHT = false;
            break;
        case (Qt::Key_G):
            play2->FIRE = false;
            break;
        default:
            break;
    }
}
void MainWidget::timerEvent(QTimerEvent *) {

    if (OVER){
        music->play();
        Bullet::bullet1Num=0;
        Bullet::bullet2Num=0;
        BigBullet::bullet1Num=0;
        BigBullet::bullet2Num=0;
        SmallBullet::bullet1Num=0;
        SmallBullet::bullet2Num=0;
        propNum=0;
        delete PropTime;
        if (OVER == 1){
            score1++;
            QMessageBox::about(nullptr, "Result", "Gamer-1 win");
        }else{
            score2++;
            QMessageBox::about(nullptr, "Result", "Gamer-2 win");
        }
        list =  items();
                foreach(QGraphicsItem * i , list){
                    delete i;
                }
        delete mymap;
        scene()->clear();
        OVER = 0;
        Display();

    }
}

