#ifndef PORTENTITY_H
#define PORTENTITY_H

#include <QObject>
#include <QTcpSocket>

class portEntity: public QObject
{
    Q_OBJECT
public:
    portEntity(QObject *parent = nullptr);
    //method
    void setEntity(QString, int, int, int);
    void setStop(bool);

private slots:
    //working method fot thread
    void scanEntity();

signals:
    void portOpen(int);
    void portNotOpen(int);
    void scanComplete();
    void disableUI();
    void enableUI();
    void currentPort(int);
    void changeProgressBar(int);
    //void doneWorking();
    //void err();

private:
    QTcpSocket *entity;
    QString enty;
    int port1;
    int port2;
    int interval;
    bool stop = false;
};

#endif // PORTENTITY_H
