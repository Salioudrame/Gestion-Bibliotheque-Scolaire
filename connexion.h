#ifndef CONNEXION_H
#define CONNEXION_H

#include <QDialog>
#include <QDebug>
#include <QtSql>
#include <QFileInfo>
#include <QMessageBox>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class Connexion;
}
QT_END_NAMESPACE

class Connexion : public QDialog
{
    Q_OBJECT

public:
    Connexion(QWidget *parent = nullptr);
    ~Connexion();
    QString getDatabasePath();

private slots:
    void on_btnClear_clicked();

    void on_btnLogin_clicked();

private:
    Ui::Connexion *ui;
    QSqlDatabase myDB;


protected:
    void keyPressEvent(QKeyEvent *event) override;
};
#endif // CONNEXION_H
