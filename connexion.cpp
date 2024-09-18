#include "connexion.h"
#include "ui_connexion.h"

#define PATH_TO_DB "C:/Users/gueye/Documents/Master1/Semestre 1/POO-C++/Projets Qt/Gestion-Bibliotheque-Scolaire/Database/gestion_bibliotheque.db"

Connexion::Connexion(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Connexion)
    // , mw(nullptr)

{
    // QString dbPath = getDatabasePath();

    ui->setupUi(this);
    myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName(PATH_TO_DB);
    QFileInfo checkFile(PATH_TO_DB);

    if(checkFile.isFile())
    {
        if(myDB.open())
        {
            ui->lblResult->setText("[+]Connected to Database File :)");
        }
    }else{
        ui->lblResult->setText("[!]Database File does not exist :(");
    }
    connect(ui->txtUser, &QLineEdit::returnPressed, this, &Connexion::on_btnLogin_clicked);
    connect(ui->txtPass, &QLineEdit::returnPressed, this, &Connexion::on_btnLogin_clicked);
}

Connexion::~Connexion()
{
    delete ui;
    myDB.close();
}

void Connexion::on_btnClear_clicked()
{
    ui->txtPass->setText("");
    ui->txtUser->setText("");
}

QString Connexion::getDatabasePath() {
    QDir dir(QDir::currentPath());
    QString path = dir.filePath("Database/gestion_bibliotheque.db");
    qDebug() << "Database path:" << path;
    return path;
}

void Connexion::on_btnLogin_clicked()
{
    QString Username, Password;
    Username = ui->txtUser->text();
    Password = ui->txtPass->text();

    if(!myDB.isOpen())
    {
        qDebug("No connection to db :(");
        return;
    }

    QSqlQuery qry;
    if(qry.exec("select Username, Password, Role from Utilisateurs where Username=\'" + Username + "\' and Password=\'" + Password+ "\'"))

    {
        if(qry.next())
        {
            ui->lblResult->setText("[+]Valid Username and password");
            // QString msg = "Nom_utilisateur = " + qry.value(0).toString()+ "\n" +
            //               "Mot_de_passe = " + qry.value(1).toString()+ "\n" +
            //               "Role = " + qry.value(2).toString();
            // QMessageBox::warning(this, "Login was successful", msg);
            mw = std::make_unique<MainWindow>();
            mw->show();
            this->hide();

        }else{
            ui->lblResult->setText("[-]Wrong Username or password");
        }
    }
}

void Connexion::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        on_btnLogin_clicked();
    } else {
        QDialog::keyPressEvent(event);
    }
}

void Connexion::on_btnCancel_clicked()
{

}

