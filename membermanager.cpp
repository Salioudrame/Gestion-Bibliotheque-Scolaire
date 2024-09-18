#include "membermanager.h"
#include "ui_membermanager.h"
#include <QtSql/QSqlError>
#include <QtSql>
#include <QDebug>

#define PATH_TO_DB "C:/Users/gueye/Documents/Master1/Semestre 1/POO-C++/Projets Qt/Gestion-Bibliotheque-Scolaire/Database/gestion_bibliotheque.db"

MemberManager::MemberManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MemberManager)
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


bool MemberManager::createMembre(const QString& nom, const QString& dateInscription)
{

    QSqlQuery query(myDB);
    query.prepare("INSERT INTO Membres (Nom, Date_inscription) VALUES ('"+nom+"', '"+dateInscription+"')");

    qDebug() << "Query prepared:" << query.lastQuery();
    if (!query.exec()) {
        qDebug() << "Error creating user:" << query.lastError().text();
        return false;
    }else
    {
        ui->labelInfo->setText("Membre Ajoutee");
    }

    return true;
}

bool MemberManager::updateMembre(int id, const QString& nom, const QString& dateInscription)
{
    QString _id = QString::number(id);
    qDebug() << "Attributs:" << nom << dateInscription;
    QSqlQuery query(myDB);
    query.prepare("UPDATE Membres SET Nom = '"+nom+"', Date_inscription = '"+dateInscription+"' WHERE id = '"+_id+"'");

    if (!query.exec()) {
        qDebug() << "Error updating user:" << query.lastError().text();
        return false;
    }else
    {
        ui->labelInfo->setText("Membre modifie");
    }
    qDebug() << "Query prepared:" << query.lastQuery();

    return true;
}

bool MemberManager::deleteMembre(const int& id)
{
    QSqlQuery query(myDB);
    query.prepare("DELETE FROM Membres WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error deleting user:" << query.lastError().text();
        return false;
    }else
    {
        ui->labelInfo->setText("Membre supprime");
    }

    return true;
}

void MemberManager::on_btnAjouter_clicked()
{
    nom= ui->labelNom->text();
    dateInscription=ui->labelDate->text();
    createMembre(nom, dateInscription);
    qDebug("Base ouverte");
}


void MemberManager::on_btnModifier_clicked()
{

    nom= ui->labelNom->text();
    dateInscription=ui->labelDate->text();
    updateMembre(idMembre,nom, dateInscription);
}

QSqlQueryModel* MemberManager::getAllMembres()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    QSqlQuery query(myDB);

    if (!query.exec("SELECT * FROM Membres")) {
        qDebug() << "Error getting all users:" << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(query);
    return model;
}

QSqlQueryModel* MemberManager::getMembre(const QString& type, const QString& recherche)
{
    QSqlQueryModel* model = new QSqlQueryModel;
    QSqlQuery query(myDB);
    query.prepare("SELECT * FROM Membres WHERE "+type+" = '"+recherche+"'");
    qDebug() << "Query prepared:" << query.lastQuery();
    if (!query.exec()) {
        qDebug() << "Error getting user:" << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(query);
    return model;
}

void MemberManager::on_btnSupprimer_clicked()
{
    // qDebug() << "Error id:" << livreId;
    deleteMembre(idMembre);
}


void MemberManager::on_btnCharger_clicked()
{
    ui->tableMembre->setModel(getAllMembres());
}


void MemberManager::on_btnRechercher_clicked()
{
    QString recherche = ui->labelRechercher->text();
    QString type = ui->comboBox->currentText();
    qDebug() << "Recherche :" << recherche;
    qDebug() << "type :" << type;
    ui->tableMembre->setModel(getMembre(type,recherche));
}


void MemberManager::on_tableMembre_activated(const QModelIndex &index)
{
    QString val = ui->tableMembre->model()->data(index).toString();
    QSqlQuery query(myDB);
    query.prepare("SELECT * FROM membres WHERE ID='"+val+"' or Nom='"+val+"' or Date_inscription='"+val+"'");
    // qDebug() << "Query prepared:" << query.lastQuery();
    if (!query.exec()) {
        qDebug() << "Error getting user:" << query.lastError().text();

    }else
    {
        while(query.next())
        {
            ui->labelNom->setText(query.value(1).toString());
            QDate Date = QDate::fromString(query.value(2).toString(),"MM/dd/yyyy");
            // qDebug() << "Error de date:" << Date;
            ui->labelDate->setDate(Date);

            idMembre = query.value(0).toInt();
        }
    }
}



MemberManager::~MemberManager()
{
    delete ui;
}
