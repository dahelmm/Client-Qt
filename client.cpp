#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);





}

Client::~Client()
{
    delete ui;
}


void Client::socketConnected()
{
    qDebug()<<"Подключено к серверу.";
    printMessage("Подключено к серверу");
    QString name = ui->lE_name->text();
    socket->write(name.toUtf8()+" подключился к чату");
    ui->pB_connectToServer->setText("Отключиться");
    connectToHost=true;
}

void Client::socketDisconnected()
{
    qDebug() << "Отключено от сервера.";
    printMessage("Отключено от сервера");
    ui->pB_connectToServer->setText("Подключиться");
    connectToHost = false;
}

void Client::socketReadyRead()
{
    ui->tE_info->append(socket->readAll());
}

void Client::on_pB_connectToServer_clicked()
{
    if(!connectToHost)
    {
        socket = new QTcpSocket();

        connect(socket,SIGNAL(connected()),this,SLOT(socketConnected()));
        connect(socket,SIGNAL(disconnected()),this,SLOT(socketDisconnected()));
        connect(socket,SIGNAL(readyRead()),this,SLOT(socketReadyRead()));

        socket->connectToHost("127.0.0.1",8001);
    }
    else
    {
        QString name = ui->lE_name->text();
        socket->write(name.toUtf8()+"уже находится в чате");
        socket->disconnectFromHost();
    }
}

void Client::on_pB_sendData_clicked()
{
    QString name= ui->lE_name->text();
    QString message = ui->lE_sendData->text();
    socket->write(name.toUtf8()+":"+message.toUtf8());
    ui->lE_sendData->clear();
}

void Client::printMessage(QString message)
{
    ui->tE_info->append(message);
}
