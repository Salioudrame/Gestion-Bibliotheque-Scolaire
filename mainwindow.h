#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QDebug>
#include <QtSql>
#include <QFileInfo>
#include <QMessageBox>
#include <QKeyEvent>
#include "BookManager.h"
#include "membermanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_btnLivres_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<Livres> livres = nullptr;
    std::unique_ptr<MemberManager> membermanager = nullptr;
};

#endif // MAINWINDOW_H
