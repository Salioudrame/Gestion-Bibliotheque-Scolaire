#ifndef MEMBERMANAGER_H
#define MEMBERMANAGER_H

#include <QWidget>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlDatabase>
#include <QVariant>
#include <QFileInfo>
#include <QMessageBox>
#include <QKeyEvent>
namespace Ui {
class MemberManager;
}

class MemberManager : public QWidget
{
    Q_OBJECT

public:
    explicit MemberManager(QWidget *parent = nullptr);

    bool createMembre(const QString& nom, const QString& dateInscription);
    bool updateMembre(int id, const QString& nom, const QString& dateInscription);
    bool deleteMembre(const int& id);
    QSqlQueryModel* getAllMembres();
    QSqlQueryModel* getMembre(const QString& type, const QString& recherche);

    ~MemberManager();

private slots:
    void on_btnAjouter_clicked();

    void on_btnModifier_clicked();

    void on_btnSupprimer_clicked();

    void on_btnCharger_clicked();

    void on_btnRechercher_clicked();

    void on_tableMembre_activated(const QModelIndex &index);

private:
    Ui::MemberManager *ui;
    QSqlDatabase myDB;
    QString nom, dateInscription;
    int idMembre;
};

#endif // MEMBERMANAGER_H
