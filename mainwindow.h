#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QElapsedTimer>
#include <QString>
#include "queue.h"
#include <QFileDialog>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTime time;
    QTimer timer;
    QElapsedTimer m_timer;
    Queue Queue0;
public slots:

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void updateTime();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void showChanges();
    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();
};

#endif // MAINWINDOW_H
