#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_btnLivres_clicked()
{
    livres = std::make_unique<Livres>();
    livres->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    membermanager = std::make_unique<MemberManager>();
    membermanager->show();
}

