#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();

private slots:
    //обработка сигналов сокета
    void socketConnected();
    void socketDisconnected();

    void socketReadyRead();

    void on_pB_connectToServer_clicked();

    void on_pB_sendData_clicked();

private:
    Ui::Client *ui;
    QTcpSocket *socket; //сокет
    bool connectToHost; //признак подключения

    void printMessage(QString message);
};
#endif // CLIENT_H
