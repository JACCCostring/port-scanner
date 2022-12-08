#include "portentity.h"

portEntity::portEntity(QObject *parent):QObject(parent)
{
    entity = new QTcpSocket(this);
}

void portEntity::setEntity(QString ent, int firstPort, int secondPort, int inter)
{
    enty = ent;
    port1 = firstPort;
    port2 = secondPort;
    interval = inter;
}

void portEntity::setStop(bool value)
{
    stop = value;
}
//worker method
void portEntity::scanEntity()
{
    emit disableUI(); // emit for UI disabling

    if(port1!=0 && port2!=0)
    {
    for(int port = port1; port<=port2; port++)
    {
        entity->connectToHost(enty, port);
        if(!entity->waitForConnected(interval))
        {
        //emit portNotOpen(port); //emit for not open ports
        }
        else{
            emit portOpen(port); //emit for open ports
            entity->disconnectFromHost();
        }
        emit currentPort(port); //emiting for current port
        emit changeProgressBar(port);//emit for progressbar
         if(stop){break;}
    }
   // emit doneWorking();
    emit scanComplete(); //emit for completed scan
    }
    else{
       // emit err();
    }
    emit enableUI(); //emit for UI enabling
}
