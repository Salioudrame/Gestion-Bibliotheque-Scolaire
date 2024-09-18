#include "empruntmanager.h"
#include "ui_empruntmanager.h"
#include <QtSql/QSqlError>
#include <QtSql>
#include <QDebug>

#define PATH_TO_DB "C:/Users/gueye/Documents/Master1/Semestre 1/POO-C++/Projets Qt/Gestion-Bibliotheque-Scolaire/Database/gestion_bibliotheque.db"

EmpruntManager::EmpruntManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EmpruntManager)
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

bool EmpruntManager::createEmprunt(const QString& idMembre, const QString& idLivre, const QString& dateEmprunt, const QString& dateRetourPrevue)
{

    QSqlQuery query(myDB);
    query.prepare("INSERT INTO Emprunts (ID_Membre, ID_Livre, Date_Emprunt, Date_retour_prevue) VALUES ('"+idMembre+"', '"+idLivre+"',  '"+dateEmprunt+"',  '"+dateRetourPrevue+"')");

    qDebug() << "Query prepared:" << query.lastQuery();
    if (!query.exec()) {
        qDebug() << "Error creating user:" << query.lastError().text();
        return false;
    }else
    {
        ui->labelInfo->setText("Emprunt Ajoutee");
    }

    return true;
}

void EmpruntManager::getAllEmprunts()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    QSqlQuery query(myDB);

    // if (!query.exec("SELECT ID_Membre, ID_Livre, Date_emprunt, Date_retour_prevue, Date_retour_reelle FROM Emprunts")) {
    if (!query.exec("SELECT ID_Membre, ID_Livre, Date_emprunt, Date_retour_prevue, Date_retour_reelle FROM Emprunts WHERE Date_retour_reelle IS NULL OR Date_retour_reelle = ''")) {
        qDebug() << "Error getting all users:" << query.lastError().text();
        delete model;
    }
    qDebug() << "Query prepared:" << query.lastQuery();
    model->setQuery(query);
    ui->tableEmprunt->setModel(model);
    QSqlQueryModel* membreModel = new QSqlQueryModel;
    if (!query.exec("SELECT ID FROM Membres")) {
        qDebug() << "Error getting members:" << query.lastError().text();
        delete membreModel;
        return;
    }
    membreModel->setQuery(query);
    ui->comboBoxIDMembre->setModel(membreModel);

    QSqlQueryModel* livreModel = new QSqlQueryModel;
    if (!query.exec("SELECT ID FROM Livres")) {
        qDebug() << "Error getting books:" << query.lastError().text();
        delete livreModel;
        return;
    }
    livreModel->setQuery(query);
    ui->comboBoxIdLivre->setModel(livreModel);
}


EmpruntManager::~EmpruntManager()
{
    if (myDB.isOpen()) {
        myDB.close();
    }
    delete ui;
}

void EmpruntManager::on_btnCharger_clicked()
{
    getAllEmprunts();
}
void EmpruntManager::on_tableEmprunt_activated(const QModelIndex &index)
{
    QString val = ui->tableEmprunt->model()->data(index).toString();
    QSqlQuery query(myDB);
    query.prepare("SELECT * FROM Emprunts WHERE ID='"+val+"' or ID_Membre='"+val+"' or ID_Livre='"+val+"' or Date_emprunt='"+val+"' or Date_retour_prevue='"+val+"' or Date_retour_reelle='"+val+"'");
    if (!query.exec()) {
        qDebug() << "Error getting user:" << query.lastError().text();

    }else
    {
        while(query.next())
        {

            QDate Date = QDate::fromString(query.value(0).toString(),"MM/dd/yyyy");
            // qDebug() << "Error de date:" << Date;
            ui->lineDateRetourReelle->setDate(Date);

            idLivreRetour = query.value(0).toInt();
            qDebug() << "le id:" << idLivreRetour;

        }
    }
}

bool EmpruntManager::updateEmprunt(int id, const QString& dateRetourPrevue)
{
    QString _id = QString::number(id);
    QSqlQuery query(myDB);
    query.prepare("UPDATE Emprunts SET Date_retour_reelle = '"+dateRetourReelle+"' WHERE ID = "+_id+"");
    qDebug() << "Query prepared:" << query.lastQuery();
    if (!query.exec()) {
        qDebug() << "Error updating Emprunt:" << query.lastError().text();
        return false;
    }else
    {
        ui->labelInfo->setText("Date de retour ajoute modifie");
    }

    return true;
}
void EmpruntManager::on_btnEnregistrer_clicked()
{
    idMembre = ui->comboBoxIDMembre->currentText();
    idLivre=ui->comboBoxIdLivre->currentText();
    dateEmprunt= ui->lineDateEmprunt->text();
    dateRetourPrevue=ui->lineDateRetourPrevue->text();
    createEmprunt(idMembre, idLivre, dateEmprunt, dateRetourPrevue);
}


void EmpruntManager::on_btnEnregistrerRetour_clicked()
{
    dateRetourReelle= ui->lineDateRetourReelle->text();
    updateEmprunt(idLivreRetour, dateRetourReelle);
}

