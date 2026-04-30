#include "inscription.h"
#include "ui_inscription.h"
#include <QFile>
#include <QInputDialog>
#include <QTextStream>
#include <QMessageBox>

Inscription::Inscription(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Inscription)
{
    ui->setupUi(this);
}

Inscription::~Inscription()
{
    delete ui;
}

void Inscription::on_actionS_inscrire_triggered()
{;
    ui->stackedWidget_3->setCurrentWidget(ui->page_5);
}

void Inscription::on_actionChercher_triggered()
{
        ui->stackedWidget_3->setCurrentWidget(ui->page_6);
        ui->lineEdit_2->clear();
        ui->list_2->clear();
        ui->lineEdit_2->setFocus();
}
void Inscription::on_actionLister_triggered()
{
    ui->stackedWidget_3->setCurrentWidget(ui->page);
        ui->listNoms->clear();

        QFile fichier("inscrits.txt");
        if(!fichier.exists())
        {
            ui->listNoms->addItem("Erreur : Le fichier n'existe pas encore.");
            return;
        }

        if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream flux(&fichier);
            while(!flux.atEnd())
            {
                QString ligne = flux.readLine();
                if(!ligne.isEmpty())
                {
                    ui->listNoms->addItem(ligne); // C'est ici que l'insertion se fait
                }
            }
            fichier.close();
        }
}

void Inscription::on_pushButton_clicked()
{
    QString nom = ui->lineEdit->text();
    QFile fichier("inscrits.txt");
    QStringList listeMembres;
    bool existe = false;
    if(nom.isEmpty())
    {
        return;
    }
    // On lit tout pour vérifier l'existence
    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream flux(&fichier);
        while(!flux.atEnd()) {
            QString ligne = flux.readLine().trimmed();
            if(ligne == nom)
            {
                existe = true;
            } else
            {
                listeMembres << ligne;
            }
        }
        fichier.close();
    }
    //  Si le nom existe
    if(existe)
    {
        QMessageBox::critical(this, "Erreur", "Le nom '" + nom + "' existe déjà");
        ui->lineEdit->clear();
        return;
    }

    if(fichier.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream flux(&fichier);
        flux << nom << "\n";
        fichier.close();

        ui->lineEdit->clear();
    }

}

void Inscription::on_actionSe_desabonner_triggered()
{
    ui->stackedWidget_3->setCurrentWidget(ui->page_2);
}


void Inscription::on_pushButton_5_clicked()
{
    QString nomASupprimer = ui->lineEdit_11->text().trimmed(); // Le champ de la page_10
    if(nomASupprimer.isEmpty()){
            return;
    }
        QFile fichier("inscrits.txt");
        QStringList listeMembres;
        bool existe = false;

        // 1. On lit tout pour vérifier l'existence
        if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream flux(&fichier);
            while(!flux.atEnd()) {
                QString ligne = flux.readLine().trimmed();
                if(ligne == nomASupprimer)
                {
                    existe = true;
                } else
                {
                    listeMembres << ligne;
                }
            }
            fichier.close();
        }

        // 2. Si le nom n'existe pas
        if(!existe)
        {
            QMessageBox::critical(this, "Erreur", "Le nom '" + nomASupprimer + "' est introuvable.");
            return;
        }

        // 3. Si il existe, on demande confirmation
        QMessageBox::StandardButton rep;
        rep = QMessageBox::question(this, "Confirmation", "Voulez-vous supprimer " + nomASupprimer + " ?",
             QMessageBox::Yes | QMessageBox::No);

        if(rep == QMessageBox::Yes)
        {
            if(fichier.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
            {
                QTextStream flux(&fichier);
                for(const QString &nom : listeMembres) flux << nom << "\n";
                fichier.close();
                QMessageBox::information(this, "Succès", "Désabonnement effectué.");
                ui->lineEdit_11->clear();
            }
        }
}


void Inscription::on_lineEdit_2_textChanged(const QString &arg1)
{
    ui->list_2->clear();

    QString motCle = arg1.trimmed().toLower();
    if(motCle.isEmpty()) return;

    QFile fichier("inscrits.txt");
    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream flux(&fichier);
        while(!flux.atEnd()) {
            QString nom = flux.readLine();
            // On vérifie si le nom contient le mot-clé
            if(nom.toLower().contains(motCle)) {
                ui->list_2->addItem(nom);
            }
        }
        fichier.close();
    }
}

