#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H


#include <QWidget>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlDatabase>
#include <QVariant>
#include <QFileInfo>
#include <QMessageBox>
#include <QKeyEvent>
namespace Ui {
class ReportGenerator;
}

class ReportGenerator : public QWidget
{
    Q_OBJECT

public:
    explicit ReportGenerator(QWidget *parent = nullptr);

    void getAllEmprunts();
    void getAllLivres();
    QSqlQueryModel* filtre(const QString& type, const QString& recherche);

    ~ReportGenerator();

private slots:

    void on_btnCharger_clicked();

    void on_btnRechercher_clicked();

    void on_btnChargerLivre_clicked();

private:
    Ui::ReportGenerator *ui;
    QSqlDatabase myDB;
    QString idMembre, idLivre, dateEmprunt, dateRetourPrevue, dateRetourReelle;
    int idLivreRetour;
};
#endif // REPORTGENERATOR_H
