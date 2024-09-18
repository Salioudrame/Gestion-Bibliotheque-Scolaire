#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include <QWidget>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlDatabase>
#include <QVariant>
#include <QFileInfo>
#include <QMessageBox>
#include <QKeyEvent>
namespace Ui {
class Livres;
}

class Livres : public QWidget
{
    Q_OBJECT

public:
    explicit Livres(QWidget *parent = nullptr);
    // explicit Livres(QSqlDatabase& db, QWidget *parent = nullptr);

    bool createLivre(const QString& titre, const QString& auteur, const QString& genre, const QString& dateAjout);
    bool updateLivre(int id, const QString& titre, const QString& auteur, const QString& genre, const QString& dateAjout);
    bool deleteLivre(const int& id);
    QSqlQueryModel* getAllUsers();
    QSqlQueryModel* getUser(const QString& type, const QString& recherche);

    // bool updateUser(int id, const QString& login, const QString& password);
    // bool deleteUser(int id);
    // QSqlQueryModel* getUser(int id);
    // QSqlQueryModel* getAllUsers();
    // bool readBy(const QString& login, const QString& password);
    ~Livres();

private slots:
    void on_btnAjouter_clicked();

    void on_btnModifier_clicked();

    void on_btnSupprimer_clicked();

    void on_btnCharger_clicked();

    void on_btnRechercher_clicked();

    void on_tableLivre_activated(const QModelIndex &index);

private:
    Ui::Livres *ui;
    QSqlDatabase myDB;
    QString titre, auteur, genre, dateAjout;
    int idLivre;
};

#endif // BOOKMANAGER_H
