#include "BookManager.h"
#include "ui_BookManager.h"
#include <QtSql/QSqlError>
#include <QtSql>
#include <QDebug>

#define PATH_TO_DB "C:/Users/gueye/Documents/Master1/Semestre 1/POO-C++/Projets Qt/Gestion-Bibliotheque-Scolaire/Database/gestion_bibliotheque.db"

Livres::Livres(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Livres)
{
    ui->setupUi(this);
    myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName(PATH_TO_DB);
    QFileInfo checkFile(PATH_TO_DB);

    if(checkFile.isFile())
    {
        if(myDB.open())
        {
            qDebug("Base ouverte");
        }
    }else{
        qDebug("Base non ouverte");
    }
}

bool Livres::createLivre(const QString& titre, const QString& auteur, const QString& genre, const QString& dateAjout)
{

    QSqlQuery query(myDB);
    query.prepare("INSERT INTO Livres (Titre, Auteur,Genre, Date_ajout) VALUES ('"+titre+"', '"+auteur+"','"+genre+"','"+dateAjout+"')");
    query.bindValue(":Titre", titre);
    query.bindValue(":Auteur", auteur);
    query.bindValue(":Genre", genre);
    query.bindValue(":Date_ajout", dateAjout);

    qDebug() << "Query prepared:" << query.lastQuery();
    // qDebug() << "Bound values: login =" << login << ", password =" << password;

    if (!query.exec()) {
        qDebug() << "Error creating user:" << query.lastError().text();
        return false;
    }else
    {
        ui->labelInfo->setText("Livre Ajoute");
    }

    return true;
}

bool Livres::updateLivre(int id, const QString& titre, const QString& auteur, const QString& genre, const QString& dateAjout)
{
    QString _id = QString::number(id);
    qDebug() << "Attributs:" << id << titre << auteur <<genre <<dateAjout;
    QSqlQuery query(myDB);
    query.prepare("UPDATE Livres SET Titre = '"+titre+"', Auteur = '"+auteur+"', Genre = '"+genre+"', Date_ajout = '"+dateAjout+"' WHERE id = '"+_id+"'");

    // query.prepare("UPDATE Livres SET Titre = :Titre, Auteur = :Auteur, Genre = :Genre, Date_ajout = :Date_ajout WHERE id = :id");
    // query.bindValue(":Titre", titre);
    // query.bindValue(":Auteur", auteur);
    // query.bindValue(":Genre", genre);
    // query.bindValue(":Date_ajout", dateAjout);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error updating user:" << query.lastError().text();
        return false;
    }else
    {
        ui->labelInfo->setText("Livre modifie");
    }
    qDebug() << "Query prepared:" << query.lastQuery();

    return true;
}

bool Livres::deleteLivre(const int& id)
{
    QSqlQuery query(myDB);
    query.prepare("DELETE FROM Livres WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error deleting user:" << query.lastError().text();
        return false;
    }else
    {
        ui->labelInfo->setText("Livre supprime");
    }

    return true;
}

Livres::~Livres()
{
    if (myDB.isOpen()) {
        myDB.close();
    }
    delete ui;
}

void Livres::on_btnAjouter_clicked()
{
    titre = ui->labelTitre->text();
    auteur=ui->labelAuteur->text();
    genre= ui->labelGenre->text();
    dateAjout=ui->labelDate->text();
    createLivre(titre, auteur, genre, dateAjout);
    qDebug("Base ouverte");
}


void Livres::on_btnModifier_clicked()
{

    titre = ui->labelTitre->text();
    auteur=ui->labelAuteur->text();
    genre= ui->labelGenre->text();
    dateAjout=ui->labelDate->text();
    updateLivre(idLivre,titre, auteur, genre, dateAjout);
}

QSqlQueryModel* Livres::getAllUsers()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    QSqlQuery query(myDB);

    if (!query.exec("SELECT * FROM Livres")) {
        qDebug() << "Error getting all users:" << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(query);
    return model;
}

QSqlQueryModel* Livres::getUser(const QString& type, const QString& recherche)
{
    QSqlQueryModel* model = new QSqlQueryModel;
    QSqlQuery query(myDB);
    query.prepare("SELECT * FROM Livres WHERE "+type+" = '"+recherche+"'");
    // qDebug() << "Query prepared:" << query.lastQuery();
    if (!query.exec()) {
        qDebug() << "Error getting user:" << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(query);
    return model;
}

void Livres::on_btnSupprimer_clicked()
{
    // qDebug() << "Error id:" << livreId;
    deleteLivre(idLivre);
}


void Livres::on_btnCharger_clicked()
{
    ui->tableLivre->setModel(getAllUsers());
}


void Livres::on_btnRechercher_clicked()
{
    QString recherche = ui->labelRechercher->text();
    QString type = ui->comboBox->currentText();
    qDebug() << "Recherche :" << recherche;
    qDebug() << "type :" << type;
    ui->tableLivre->setModel(getUser(type,recherche));
}


void Livres::on_tableLivre_activated(const QModelIndex &index)
{
    QString val = ui->tableLivre->model()->data(index).toString();
    QSqlQuery query(myDB);
    query.prepare("SELECT * FROM Livres WHERE ID='"+val+"' or Titre='"+val+"' or Auteur='"+val+"'or Genre='"+val+"'or Date_ajout ='"+val+"'");
    // qDebug() << "Query prepared:" << query.lastQuery();
    if (!query.exec()) {
        qDebug() << "Error getting user:" << query.lastError().text();

    }else
    {
        while(query.next())
        {
            ui->labelTitre->setText(query.value(1).toString());
            ui->labelAuteur->setText(query.value(2).toString());
            ui->labelGenre->setText(query.value(3).toString());
            QDate Date = QDate::fromString(query.value(4).toString(),"MM/dd/yyyy");
            // qDebug() << "Error de date:" << Date;
            ui->labelDate->setDate(Date);

            idLivre = query.value(0).toInt();
        }
    }
}

