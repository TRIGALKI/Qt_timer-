#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    time = QTime(0,0);
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateTime()));
}

MainWindow::~MainWindow()
{
    delete ui;

}
void MainWindow::showChanges()
{
QString text;
Queue::Iterator iterator;
for(iterator=Queue0.begin(); iterator!=nullptr; iterator++)
{
    if ((*iterator)->whichClass()==true)
    {
        const CommandMove *p = static_cast<const CommandMove*>(*iterator);
        text=text +"\n<<MOVE ORDER ACEPTED >>"+"\nSpeed :" + QString::number(p->getSpeed()) + "\nTime :" + QString::number(p->getTime());
    }
    else
    {
        const CommandTurn *a = static_cast<const CommandTurn*>(*iterator);
        text=text +"\n<DIRECTON ORDER ACEPTED>"+"\nRad :" + QString::number(a->getRadius()) + "\nTimer :" + QString::number(a->getTime());
    }
}

ui->textBrowser->setText(text);
}
void MainWindow::updateTime()
{
    time=time.addMSecs(m_timer.restart());
    ui->lcdNumber->display(time.second());
}
void MainWindow::on_pushButton_clicked()
{
    m_timer.start();
    timer.start(100);
}

void MainWindow::on_pushButton_2_clicked()
{
    timer.stop();
}

void MainWindow::on_pushButton_3_clicked()
{
    float speed,time ;
    double speedDoub;
    speedDoub=ui->doubleSpinBox->value();
    speed=float(speedDoub);
    time=ui->lcdNumber->value();
    CommandMove objName(speed,time);
    Queue0.addNode(objName);
    showChanges();
    //btnRefresh();
}

void MainWindow::on_pushButton_4_clicked()
{
    float radius,time ;
    double radiusDoub;
    radiusDoub=ui->doubleSpinBox_2->value();
    radius=float(radiusDoub);
    time=ui->lcdNumber->value();
    CommandTurn objName(radius,time);
    Queue0.addNode(objName);
    showChanges();
    //btnRefresh();
}

void MainWindow::on_pushButton_6_clicked()
{
    QString Qfilestr=QFileDialog::getOpenFileName();;
    string filestr=Qfilestr.toStdString();
    Queue0.readFromFile(filestr);
    showChanges();
}


void MainWindow::on_pushButton_5_clicked()
{
    QString Qfilestr=QFileDialog::getOpenFileName();;
    string filestr=Qfilestr.toStdString();
    Queue0.writeInFile(filestr);
    showChanges();
}
