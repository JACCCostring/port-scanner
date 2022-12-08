#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QThread>
#include "portentity.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void notifyOpenPort(int);
    void notifyNotOpenPort(int);
    void errorfromBackEnd();
    void notifyScanComplete();
    void notifyDisableUI();
    void notifyEnableUI();
    void changeBar(int);
    void currentPort(int);
    //buttons slots
    void on_actionScann_triggered();
    void on_pushButton_clicked();

    void on_actionStop_Scan_triggered();

private:
    Ui::MainWindow *ui;
    portEntity *scanner;
    QThread *m_thread;
};
#endif // MAINWINDOW_H
