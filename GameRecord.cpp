#include "GameRecord.h"
#include "ui_GameRecord.h"
#include<QFile>
#include<QApplication>
#include<QDebug>
GameRecord::GameRecord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameRecord)
{
    ui->setupUi(this);
        QString path = QApplication::applicationDirPath();
        path += "/GameRecord.txt";
        QFile file(path);
        file.open(QIODevice::ReadOnly);
        QByteArray array = file.readAll();
        ui->textEdit->setText(array);
        file.close();
        qDebug()<<"打印系统日志于"<<path;
}

GameRecord::~GameRecord()
{
    delete ui;
}
