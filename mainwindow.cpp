#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //code here
    //creating Objs
    scanner = new portEntity();
    m_thread = new QThread(this);
    //operating Objs
    scanner->moveToThread(m_thread);
    //connecting thread
    connect(m_thread, SIGNAL(started()), scanner, SLOT(scanEntity()));
    //connecting UIs
    connect(scanner, SIGNAL(portOpen(int)), this, SLOT(notifyOpenPort(int)));
    //connect(scanner, SIGNAL(portNotOpen(int)), this, SLOT(notifyNotOpenPort(int)));
    connect(scanner, SIGNAL(scanComplete()), this, SLOT(notifyScanComplete()));
    connect(scanner, SIGNAL(disableUI()), this, SLOT(notifyDisableUI()));
    connect(scanner, SIGNAL(enableUI()), this, SLOT(notifyEnableUI()));
    connect(scanner, SIGNAL(changeProgressBar(int)), this, SLOT(changeBar(int)));
    connect(scanner, SIGNAL(currentPort(int)), this, SLOT(currentPort(int)));
    //connect(scanner, SIGNAL(err()), this, SLOT(errorfromBackEnd()));
    //setting UI things
    setContextMenuPolicy(Qt::ActionsContextMenu);
    addActions({ui->actionScann, ui->actionStop_Scan});
    ui->plainLog->setReadOnly(true);
    ui->spinInterval->setValue(300);
    ui->spinPortFrom->setValue(0);
    ui->spinPortTo->setValue(0);
    ui->progressBar->setValue(0);
    ui->actionStop_Scan->setEnabled(false);
    ui->spinCurrent->setReadOnly(true);
    setWindowTitle("::::Port Scanner::::");
    ui->lineHost->setText("127.0.0.1");
}

MainWindow::~MainWindow()
{
    delete ui;
     m_thread->deleteLater();
}

void MainWindow::notifyOpenPort(int port)
{
    ui->plainLog->appendPlainText("");
    ui->plainLog->appendPlainText("");
    ui->plainLog->appendPlainText("--> Opened: "+QString::number(port));
}

void MainWindow::notifyNotOpenPort(int port)
{
    //ui->plainLog->appendPlainText("Closed: "+QString::number(port));
    (void) port;
}

void MainWindow::errorfromBackEnd()
{
    //QMessageBox::information(this, "Error", "Ports or Host missing!");
   // return;
}

void MainWindow::notifyScanComplete()
{
    QString port1 = ui->spinPortFrom->text();
    QString port2 = ui->spinPortTo->text();

    ui->plainLog->appendPlainText("");
    ui->plainLog->appendPlainText("");
    ui->plainLog->appendPlainText("::::Scan Complete::::");
    ui->plainLog->appendPlainText("From: " + port1 + " To: " + port2);
    ui->spinPortFrom->setValue(0);
    ui->spinPortTo->setValue(0);
    //quitting thread
    m_thread->quit();
}

void MainWindow::notifyDisableUI()
{
    ui->lineHost->setEnabled(false);
    ui->spinInterval->setEnabled(false);
    ui->spinPortFrom->setEnabled(false);
    ui->spinPortTo->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->actionScann->setEnabled(false);
    ui->actionStop_Scan->setEnabled(true);
}

void MainWindow::notifyEnableUI()
{
    ui->lineHost->setEnabled(true);
    ui->spinInterval->setEnabled(true);
    ui->spinPortFrom->setEnabled(true);
    ui->spinPortTo->setEnabled(true);
    ui->pushButton->setEnabled(true);
    ui->actionScann->setEnabled(true);
    ui->actionStop_Scan->setEnabled(false);
}

void MainWindow::on_actionScann_triggered()
{
    if(ui->spinPortFrom->value()==0 && ui->spinPortTo->value()==0){
        ui->plainLog->clear();
        ui->progressBar->setValue(0);
        QMessageBox::information(this, "Error", "Ports or Host missing!");
    return;
    }

    ui->plainLog->clear();
    ui->plainLog->appendPlainText("Scanning...");
    ui->progressBar->setValue(0);
    //setting values to entity
    scanner->setStop(false);
    scanner->setEntity(ui->lineHost->text(), ui->spinPortFrom->value(), ui->spinPortTo->value(),
                       ui->spinInterval->value());
    //starting thread
    if(ui->spinPortFrom->value()!=0 && ui->spinPortTo->value()!=0)
    m_thread->start();
}


void MainWindow::on_pushButton_clicked()
{
    if(ui->spinPortFrom->value()==0 && ui->spinPortTo->value()==0){
        ui->plainLog->clear();
        ui->progressBar->setValue(0);
        QMessageBox::information(this, "Error", "Ports or Host missing!");
    return;
    }

    ui->plainLog->clear();
    ui->progressBar->setValue(0);
    ui->plainLog->appendPlainText("Scanning...");
     //setting values to entity
    scanner->setStop(false);
    scanner->setEntity(ui->lineHost->text(), ui->spinPortFrom->value(), ui->spinPortTo->value(),
                       ui->spinInterval->value());
    //starting thread
    if(ui->spinPortFrom->value()!=0 && ui->spinPortTo->value()!=0)
    m_thread->start();
}

void MainWindow::changeBar(int val){
    ui->progressBar->setValue(val);
     ui->progressBar->setRange(0, ui->spinPortTo->value());
    ui->labelProgress->setText(QString::number(val)+tr(" / %1").arg(ui->spinPortTo->value()));
}

void MainWindow::currentPort(int pt)
{
    ui->spinCurrent->setValue(pt);
}

void MainWindow::on_actionStop_Scan_triggered()
{
    scanner->setStop(true);
}

