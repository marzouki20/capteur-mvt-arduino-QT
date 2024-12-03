#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer


}

MainWindow::~MainWindow()
{
    delete ui;
}



//-------------------------------------------------------------------------------------------------------------------------------**
void MainWindow::update_label() {
    QByteArray data = A.getserial()->readAll();

    if (!data.isEmpty()) {
        QString jei_ml_arduino = QString::fromUtf8(data).trimmed();
ui->label->setText(jei_ml_arduino);
       }


}


