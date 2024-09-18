#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Bibliotheque");
    on_btnReport_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_btnLivres_clicked()
{
    Livres *membre = new Livres(this);
    QWidget *placeholderWidget = ui->uihere;

    if (placeholderWidget->layout() != nullptr) {
        QLayoutItem *item;
        while ((item = placeholderWidget->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    } else {
        QVBoxLayout *layout = new QVBoxLayout(placeholderWidget);
        placeholderWidget->setLayout(layout);
    }

    // Add the new widget to the layout
    placeholderWidget->layout()->addWidget(membre);
}

void MainWindow::on_pushButton_3_clicked()
{
    MemberManager *memberManager = new MemberManager(this);
    QWidget *placeholderWidget = ui->uihere;

    if (placeholderWidget->layout() != nullptr) {
        QLayoutItem *item;
        while ((item = placeholderWidget->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    } else {
        QVBoxLayout *layout = new QVBoxLayout(placeholderWidget);
        placeholderWidget->setLayout(layout);
    }

    placeholderWidget->layout()->addWidget(memberManager);
}

void MainWindow::on_btnEmprunts_clicked()
{
    EmpruntManager *emprunt = new EmpruntManager(this);
    QWidget *placeholderWidget = ui->uihere;

    if (placeholderWidget->layout() != nullptr) {
        QLayoutItem *item;
        while ((item = placeholderWidget->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    } else {
        QVBoxLayout *layout = new QVBoxLayout(placeholderWidget);
        placeholderWidget->setLayout(layout);
    }

    placeholderWidget->layout()->addWidget(emprunt);
}

void MainWindow::on_btnReport_clicked()
{
    ReportGenerator *report = new ReportGenerator(this);
    QWidget *placeholderWidget = ui->uihere;

    if (placeholderWidget->layout() != nullptr) {
        QLayoutItem *item;
        while ((item = placeholderWidget->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    } else {
        QVBoxLayout *layout = new QVBoxLayout(placeholderWidget);
        placeholderWidget->setLayout(layout);
    }

    placeholderWidget->layout()->addWidget(report);
}

