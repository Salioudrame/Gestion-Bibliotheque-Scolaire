#ifndef EMPRUNTMANAGER_H
#define EMPRUNTMANAGER_H

#include <QWidget>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlDatabase>
#include <QVariant>
#include <QFileInfo>
#include <QMessageBox>
#include <QKeyEvent>
namespace Ui {
class EmpruntManager;
}

class EmpruntManager : public QWidget
{
    Q_OBJECT

public:
    explicit EmpruntManager(QWidget *parent = nullptr);

    bool createEmprunt(const QString& idMembre, const QString& idLivre, const QString& dateEmprunt, const QString& dateRetourPrevue);
    bool updateEmprunt(int id, const QString& dateRetourPrevue);
    void getAllEmprunts();
    // QSqlQueryModel* getMembre(const QString& type, const QString& recherche);

    ~EmpruntManager();

private slots:

    void on_btnCharger_clicked();

    void on_tableEmprunt_activated(const QModelIndex &index);

    void on_btnEnregistrer_clicked();

    void on_btnEnregistrerRetour_clicked();

private:
    Ui::EmpruntManager *ui;
    QSqlDatabase myDB;
    QString idMembre, idLivre, dateEmprunt, dateRetourPrevue, dateRetourReelle;
    int idLivreRetour;
};

#endif // EMPRUNTMANAGER_H
