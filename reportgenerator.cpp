#include "reportgenerator.h"
#include "ui_reportgenerator.h"
#include <QtSql/QSqlError>
#include <QtSql>
#include <QDebug>

#define PATH_TO_DB "C:/Users/gueye/Documents/Master1/Semestre 1/POO-C++/Projets Qt/Gestion-Bibliotheque-Scolaire/Database/gestion_bibliotheque.db"


ReportGenerator::ReportGenerator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReportGenerator)
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




void ReportGenerator::getAllEmprunts()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    QSqlQuery query(myDB);

    if (!query.exec("SELECT ID_Membre, ID_Livre, Date_emprunt, Date_retour_prevue, Date_retour_reelle FROM Emprunts")) {
    // if (!query.exec("SELECT ID_Membre, ID_Livre, Date_emprunt, Date_retour_prevue, Date_retour_reelle FROM Emprunts WHERE Date_retour_reelle IS NULL OR Date_retour_reelle = ''")) {
        qDebug() << "Error getting all users:" << query.lastError().text();
        delete model;
    }
    qDebug() << "Query prepared:" << query.lastQuery();
    model->setQuery(query);
    ui->tableMembre->setModel(model);
}

QSqlQueryModel* ReportGenerator::filtre(const QString& type, const QString& recherche)
{
    QSqlQueryModel* model = new QSqlQueryModel;
    QSqlQuery query(myDB);
    query.prepare("SELECT Membres.Nom, Titre, Date_emprunt, Date_retour_prevue, Date_retour_reelle"
                    " FROM Emprunts join Livres on Emprunts.ID_Livre = Livres.ID join Membres ON Emprunts.ID_Membre = Membres.ID  WHERE "+type+" = '"+recherche+"'");


    qDebug() << "Query prepared:" << query.lastQuery();
    if (!query.exec()) {
        qDebug() << "Error getting user:" << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(query);
    return model;
}

void ReportGenerator::getAllLivres()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    QSqlQuery query(myDB);

    if (!query.exec("SELECT * FROM Livres")) {
        qDebug() << "Error getting all Livres:" << query.lastError().text();
        delete model;
    }

    model->setQuery(query);
    ui->tableLivre->setModel(model);
}

void ReportGenerator::on_btnCharger_clicked()
{
    getAllEmprunts();
}



ReportGenerator::~ReportGenerator()
{
    if (myDB.isOpen()) {
        myDB.close();
    }
    delete ui;
}

void ReportGenerator::on_btnRechercher_clicked()
{
    QString recherche = ui->labelRechercher->text();
    QString type = ui->comboBox->currentText();
    qDebug() << "Recherche :" << recherche;
    qDebug() << "type :" << type;
    ui->tableMembre->setModel(filtre(type,recherche));
}


void ReportGenerator::on_btnChargerLivre_clicked()
{
    getAllLivres();
}

