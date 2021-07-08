//==============================================================================
// Name        : EcranPrincipal.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Source file of the EcranPrincipal class
//==============================================================================

#include "EcranPrincipal.h"
#include "ui_EcranPrincipal.h"
#include "FenetreDocumentation.h"
#include "FenetreGraphique.h"
#include "FenetreParametresAffichage.h"
#include "FenetreParametresConversion.h"
#include "FenetreParametresExport.h"
#include "FenetreParametresRecherche.h"
#include "Image.h"
#include "Parametres.h"
#include "ParametresAffichage.h"
#include "ParametresConversion.h"
#include "ParametresExport.h"
#include "ParametresFichiers.h"
#include "ParametresGraphique.h"
#include "ParametresRecherche.h"
#include "Point.h"
#include "Repere.h"
#include <cmath>
#include <QDialog>
#include <QDoubleValidator>
#include <QFileDialog>
#include <QGraphicsView>
#include <QImage>
#include <QIntValidator>
#include <QList>
#include <QMessageBox>
#include <QModelIndexList>
#include <QPoint>
#include <QString>
#include <QTableWidgetItem>

EcranPrincipal::EcranPrincipal(QWidget* parent) :
        QMainWindow(parent), ui(new Ui::EcranPrincipal), pushButtonActif(nullptr)
{
    this->ui->setupUi(this);
    this->connect(this->ui->vueGraphiqueEtude, SIGNAL(mousePressEventSignal(const QPointF)), this,
            SLOT(mousePressEventSlot(const QPointF)));
    this->connect(this->ui->vueGraphiqueEtude, SIGNAL(mouseMoveEventSignal(const QPointF)), this,
            SLOT(mouseMoveEventSlot(const QPointF)));
    this->initialiserElementsGraphiques();
    this->effacerElementsGraphiques();
}

EcranPrincipal::~EcranPrincipal()
{
    delete this->ui;
}

void EcranPrincipal::initialiserElementsGraphiques()
{
    this->ui->radioButtonNoirEtBlanc->setChecked(true);

    const QIntValidator* nombreEntier = new QIntValidator(this);
    this->ui->lineEditPointX0XPixel->setValidator(nombreEntier);
    this->ui->lineEditPointX0YPixel->setValidator(nombreEntier);
    this->ui->lineEditPointX1XPixel->setValidator(nombreEntier);
    this->ui->lineEditPointX1YPixel->setValidator(nombreEntier);
    this->ui->lineEditPointY0XPixel->setValidator(nombreEntier);
    this->ui->lineEditPointY0YPixel->setValidator(nombreEntier);
    this->ui->lineEditPointY1XPixel->setValidator(nombreEntier);
    this->ui->lineEditPointY1YPixel->setValidator(nombreEntier);
    this->ui->lineEditPointDepartXPixel->setValidator(nombreEntier);
    this->ui->lineEditPointDepartYPixel->setValidator(nombreEntier);
    this->ui->lineEditPointArriveeXPixel->setValidator(nombreEntier);
    this->ui->lineEditPointArriveeYPixel->setValidator(nombreEntier);
    this->ui->lineEditPointManuelXPixel->setValidator(nombreEntier);
    this->ui->lineEditPointManuelYPixel->setValidator(nombreEntier);

    const QDoubleValidator* nombreReel = new QDoubleValidator(this);
    this->ui->lineEditPointX0Valeur->setValidator(nombreReel);
    this->ui->lineEditPointX1Valeur->setValidator(nombreReel);
    this->ui->lineEditPointY0Valeur->setValidator(nombreReel);
    this->ui->lineEditPointY1Valeur->setValidator(nombreReel);
    this->ui->lineEditPointDepartXReel->setValidator(nombreReel);
    this->ui->lineEditPointDepartYReel->setValidator(nombreReel);
    this->ui->lineEditPointArriveeXReel->setValidator(nombreReel);
    this->ui->lineEditPointArriveeYReel->setValidator(nombreReel);
    this->ui->lineEditPointManuelXReel->setValidator(nombreReel);
    this->ui->lineEditPointManuelYReel->setValidator(nombreReel);

#ifndef ENABLE_QWT
    this->ui->pushButtonGraphique->setEnabled(false);
#endif
}

void EcranPrincipal::effacerElementsGraphiques()
{
    this->ui->radioButtonNoirEtBlanc->setChecked(true);

    this->ui->lineEditPointX0XPixel->clear();
    this->ui->lineEditPointX0YPixel->clear();
    this->ui->lineEditPointX0Valeur->clear();
    this->ui->lineEditPointX1XPixel->clear();
    this->ui->lineEditPointX1YPixel->clear();
    this->ui->lineEditPointX1Valeur->clear();
    this->ui->lineEditPointY0XPixel->clear();
    this->ui->lineEditPointY0YPixel->clear();
    this->ui->lineEditPointY0Valeur->clear();
    this->ui->lineEditPointY1XPixel->clear();
    this->ui->lineEditPointY1YPixel->clear();
    this->ui->lineEditPointY1Valeur->clear();

    this->ui->lineEditPointDepartXPixel->clear();
    this->ui->lineEditPointDepartYPixel->clear();
    this->ui->lineEditPointDepartXReel->clear();
    this->ui->lineEditPointDepartYReel->clear();
    this->ui->lineEditPointArriveeXPixel->clear();
    this->ui->lineEditPointArriveeYPixel->clear();
    this->ui->lineEditPointArriveeXReel->clear();
    this->ui->lineEditPointArriveeYReel->clear();
    this->ui->lineEditPointManuelXPixel->clear();
    this->ui->lineEditPointManuelYPixel->clear();
    this->ui->lineEditPointManuelXReel->clear();
    this->ui->lineEditPointManuelYReel->clear();

    this->ui->tableWidgetListePoints->clearContents();
    this->ui->tableWidgetListePoints->setRowCount(0);
    this->ui->tableWidgetListePoints->resizeColumnsToContents();

    this->ui->statusBar->clearMessage();

    this->activerBouton(nullptr);

    this->repositionnerVueGraphiqueEtude();
    this->effacerVueGraphiqueEtude();
}

void EcranPrincipal::actualiserElementsGraphiques()
{
    const Repere& repere = this->etude.getRepere();
    const Parametres& parametres = this->etude.getParametres();
    const ParametresConversion& parametresConversion = parametres.getParametresConversion();
    const int& methodeConversion = parametresConversion.getMethodeConversion();

    if ((methodeConversion == ParametresConversion::BRUTE)
            || (methodeConversion == ParametresConversion::NOIR_ET_BLANC))
    {
        this->ui->radioButtonNoirEtBlanc->setChecked(true);
    }
    else if (methodeConversion == ParametresConversion::NIVEAUX_DE_GRIS)
    {
        this->ui->radioButtonNiveauxDeGris->setChecked(true);
    }
    else if (methodeConversion == ParametresConversion::TEINTES_SATUREES)
    {
        this->ui->radioButtonTeintesSaturees->setChecked(true);
    }

    this->ui->lineEditPointX0XPixel->setText(QString::number(repere.getPointX0().getPointPixelX()));
    this->ui->lineEditPointX0YPixel->setText(QString::number(repere.getPointX0().getPointPixelY()));
    this->ui->lineEditPointX0Valeur->setText(QString::number(repere.getPointX0().getPointReelX()));
    this->ui->lineEditPointX1XPixel->setText(QString::number(repere.getPointX1().getPointPixelX()));
    this->ui->lineEditPointX1YPixel->setText(QString::number(repere.getPointX1().getPointPixelY()));
    this->ui->lineEditPointX1Valeur->setText(QString::number(repere.getPointX1().getPointReelX()));
    this->ui->lineEditPointY0XPixel->setText(QString::number(repere.getPointY0().getPointPixelX()));
    this->ui->lineEditPointY0YPixel->setText(QString::number(repere.getPointY0().getPointPixelY()));
    this->ui->lineEditPointY0Valeur->setText(QString::number(repere.getPointY0().getPointReelY()));
    this->ui->lineEditPointY1XPixel->setText(QString::number(repere.getPointY1().getPointPixelX()));
    this->ui->lineEditPointY1YPixel->setText(QString::number(repere.getPointY1().getPointPixelY()));
    this->ui->lineEditPointY1Valeur->setText(QString::number(repere.getPointY1().getPointReelY()));

    this->actualiserCoordonneesPoints();

    this->etude.restaurerImage();
    this->etude.convertirImage();
    this->dessinerVueGraphiqueEtude();
}

void EcranPrincipal::creerNouvelleEtude()
{
    const QString cheminFichierImageSource = QFileDialog::getOpenFileName(this,
            QString::fromUtf8("Sélection d'un fichier image"),
            this->etude.getParametres().getParametresFichiers().getCheminFichierImageSource(),
            QString::fromUtf8("Fichier image (*.bmp *.jpg *.jpeg *.png)"));
    if (cheminFichierImageSource.isEmpty())
        return;

    this->effacerElementsGraphiques();

    this->etude.clear();
    this->actualiserEtudeReference();

    Image image;
    image.setImageSource(QImage(cheminFichierImageSource));
    image.restaurerImage();
    this->etude.setImage(image);
    Parametres parametres;
    ParametresFichiers parametresFichiers = parametres.getParametresFichiers();
    parametresFichiers.setCheminFichierImageSource(cheminFichierImageSource);
    parametres.setParametresFichiers(parametresFichiers);
    this->etude.setParametres(parametres);

    this->dessinerVueGraphiqueEtude();
}

void EcranPrincipal::chargerEtudeExistante()
{
    const QString cheminFichierEtude = QFileDialog::getOpenFileName(this,
            QString::fromUtf8("Sélection d'un fichier étude"),
            this->etude.getParametres().getParametresFichiers().getCheminFichierEtude(),
            QString::fromUtf8("Fichier étude (*.ndc)"));
    if (cheminFichierEtude.isEmpty())
        return;

    this->effacerElementsGraphiques();

    this->etude.chargerEtude(cheminFichierEtude);
    this->actualiserEtudeReference();

    this->actualiserElementsGraphiques();
}

void EcranPrincipal::sauverEtudeCourante()
{
    const QString cheminFichierEtude = QFileDialog::getSaveFileName(this,
            QString::fromUtf8("Sélection d'un fichier étude"),
            this->etude.getParametres().getParametresFichiers().getCheminFichierEtude(),
            QString::fromUtf8("Fichier étude (*.ndc)"));
    if (cheminFichierEtude.isEmpty())
        return;

    this->etude.sauverEtude(cheminFichierEtude);
    this->actualiserEtudeReference();
}

void EcranPrincipal::exporterListeDePointsCourante()
{
    const QString cheminFichierExport = QFileDialog::getSaveFileName(this,
            QString::fromUtf8("Sélection d'un fichier export"),
            this->etude.getParametres().getParametresFichiers().getCheminFichierExport(),
            QString::fromUtf8("Fichier export (*.csv)"));
    if (cheminFichierExport.isEmpty())
        return;

    this->etude.exporterListeDePoints(cheminFichierExport);
}

void EcranPrincipal::exporterImageConvertieCourante()
{
    const QString cheminFichierImageConvertie = QFileDialog::getSaveFileName(this,
            QString::fromUtf8("Sélection d'un fichier image"),
            this->etude.getParametres().getParametresFichiers().getCheminFichierImageConvertie(),
            QString::fromUtf8("Fichier image Windows Bitmap (*.bmp);;"
                    "Fichier image JPEG (*.jpg *.jpeg);;"
                    "Fichier image PNG (*.png)"));
    if (cheminFichierImageConvertie.isEmpty())
        return;

    this->etude.exporterImageConvertie(cheminFichierImageConvertie);
}

void EcranPrincipal::chargerParametresExistants()
{
    const QString cheminFichierParametres = QFileDialog::getOpenFileName(this,
            QString::fromUtf8("Sélection d'un fichier paramètres"),
            this->etude.getParametres().getParametresFichiers().getCheminFichierParametres(),
            QString::fromUtf8("Fichier paramètres (*.prm)"));
    if (cheminFichierParametres.isEmpty())
        return;

    this->etude.chargerParametres(cheminFichierParametres);

    this->dessinerVueGraphiqueEtude();
}

void EcranPrincipal::sauverParametresCourants()
{
    const QString cheminFichierParametres = QFileDialog::getSaveFileName(this,
            QString::fromUtf8("Sélection d'un fichier paramètres"),
            this->etude.getParametres().getParametresFichiers().getCheminFichierParametres(),
            QString::fromUtf8("Fichier paramètres (*.prm)"));
    if (cheminFichierParametres.isEmpty())
        return;

    this->etude.sauverParametres(cheminFichierParametres);
}

void EcranPrincipal::verifierEtatSauvegardeEtude()
{
    if (this->etude.equals(this->etudeReference))
        return;

    QMessageBox* fenetreMessage = new QMessageBox(QMessageBox::Warning,
            QString::fromUtf8("Sauvegarde de l'étude courante"),
            QString::fromUtf8("Souhaitez-vous sauver l'étude courante ?"),
            QMessageBox::Yes | QMessageBox::No, this);
    fenetreMessage->setButtonText(QMessageBox::Yes, "Oui");
    fenetreMessage->setButtonText(QMessageBox::No, "Non");
    if (fenetreMessage->exec() == QMessageBox::No)
        return;

    this->sauverEtudeCourante();
}

void EcranPrincipal::actualiserEtudeReference()
{
    this->etudeReference = this->etude;
}

void EcranPrincipal::actualiserCoordonneesPoints()
{
    this->actualiserCoordonneesPointDepart();
    this->actualiserCoordonneesPointArrivee();
    this->actualiserCoordonneesPointManuel();
    this->actualiserCoordonneesListeDePoints();
}

void EcranPrincipal::actualiserCoordonneesPointDepart()
{
    if (this->ui->lineEditPointDepartXPixel->text().isEmpty()
            || this->ui->lineEditPointDepartYPixel->text().isEmpty())
    {
        this->ui->lineEditPointDepartXReel->clear();
        this->ui->lineEditPointDepartYReel->clear();
        return;
    }

    const Parametres& parametres = this->etude.getParametres();
    const ParametresAffichage& parametresAffichage = parametres.getParametresAffichage();
    const char formatNotationNombresCaractere =
            parametresAffichage.getFormatNotationNombresCaractere();
    const int& nombreChiffresSignificatifs = parametresAffichage.getNombreChiffresSignificatifs();

    const int pointPixelX = this->ui->lineEditPointDepartXPixel->text().toInt();
    const int pointPixelY = this->ui->lineEditPointDepartYPixel->text().toInt();
    double pointReelX = 0.0;
    double pointReelY = 0.0;
    this->etude.getRepere().pixelVersReel(pointPixelX, pointPixelY, pointReelX, pointReelY);
    this->ui->lineEditPointDepartXReel->setText(
            QString::number(pointReelX, formatNotationNombresCaractere,
                    nombreChiffresSignificatifs));
    this->ui->lineEditPointDepartYReel->setText(
            QString::number(pointReelY, formatNotationNombresCaractere,
                    nombreChiffresSignificatifs));
}

void EcranPrincipal::actualiserCoordonneesPointArrivee()
{
    if (this->ui->lineEditPointArriveeXPixel->text().isEmpty()
            || this->ui->lineEditPointArriveeYPixel->text().isEmpty())
    {
        this->ui->lineEditPointArriveeXReel->clear();
        this->ui->lineEditPointArriveeYReel->clear();
        return;
    }

    const Parametres& parametres = this->etude.getParametres();
    const ParametresAffichage& parametresAffichage = parametres.getParametresAffichage();
    const char formatNotationNombresCaractere =
            parametresAffichage.getFormatNotationNombresCaractere();
    const int& nombreChiffresSignificatifs = parametresAffichage.getNombreChiffresSignificatifs();

    const int pointPixelX = this->ui->lineEditPointArriveeXPixel->text().toInt();
    const int pointPixelY = this->ui->lineEditPointArriveeYPixel->text().toInt();
    double pointReelX = 0.0;
    double pointReelY = 0.0;
    this->etude.getRepere().pixelVersReel(pointPixelX, pointPixelY, pointReelX, pointReelY);
    this->ui->lineEditPointArriveeXReel->setText(
            QString::number(pointReelX, formatNotationNombresCaractere,
                    nombreChiffresSignificatifs));
    this->ui->lineEditPointArriveeYReel->setText(
            QString::number(pointReelY, formatNotationNombresCaractere,
                    nombreChiffresSignificatifs));
}

void EcranPrincipal::actualiserCoordonneesPointManuel()
{
    if (this->ui->lineEditPointManuelXPixel->text().isEmpty()
            || this->ui->lineEditPointManuelYPixel->text().isEmpty())
    {
        this->ui->lineEditPointManuelXReel->clear();
        this->ui->lineEditPointManuelYReel->clear();
        return;
    }

    const Parametres& parametres = this->etude.getParametres();
    const ParametresAffichage& parametresAffichage = parametres.getParametresAffichage();
    const char formatNotationNombresCaractere =
            parametresAffichage.getFormatNotationNombresCaractere();
    const int& nombreChiffresSignificatifs = parametresAffichage.getNombreChiffresSignificatifs();

    const int pointPixelX = this->ui->lineEditPointManuelXPixel->text().toInt();
    const int pointPixelY = this->ui->lineEditPointManuelYPixel->text().toInt();
    double pointReelX = 0.0;
    double pointReelY = 0.0;
    this->etude.getRepere().pixelVersReel(pointPixelX, pointPixelY, pointReelX, pointReelY);
    this->ui->lineEditPointManuelXReel->setText(
            QString::number(pointReelX, formatNotationNombresCaractere,
                    nombreChiffresSignificatifs));
    this->ui->lineEditPointManuelYReel->setText(
            QString::number(pointReelY, formatNotationNombresCaractere,
                    nombreChiffresSignificatifs));
}

void EcranPrincipal::actualiserCoordonneesListeDePoints()
{
    // TODO Déplacement de l'actualisation des éléments de la liste de points

    const Parametres& parametres = this->etude.getParametres();
    const ParametresAffichage& parametresAffichage = parametres.getParametresAffichage();
    const char formatNotationNombresCaractere =
            parametresAffichage.getFormatNotationNombresCaractere();
    const int& nombreChiffresSignificatifs = parametresAffichage.getNombreChiffresSignificatifs();

    QList<Point> listeDePoints = this->etude.getListeDePoints();
    const int nombreDePoints = listeDePoints.count();
    for (int itPoint = 0; itPoint < nombreDePoints; itPoint++)
    {
        Point point = listeDePoints.at(itPoint);
        this->etude.getRepere().pixelVersReel(point);
        listeDePoints.replace(itPoint, point);
    }
    this->etude.setListeDePoints(listeDePoints);

    this->ui->tableWidgetListePoints->clearContents();
    this->ui->tableWidgetListePoints->setRowCount(nombreDePoints);
    for (int itPoint = 0; itPoint < nombreDePoints; itPoint++)
    {
        const Point& point = listeDePoints.at(itPoint);
        QTableWidgetItem* itemPointPixelX = new QTableWidgetItem(
                QString::number(point.getPointPixelX()));
        QTableWidgetItem* itemPointPixelY = new QTableWidgetItem(
                QString::number(point.getPointPixelY()));
        QTableWidgetItem* itemPointReelX = new QTableWidgetItem(
                QString::number(point.getPointReelX(), formatNotationNombresCaractere,
                        nombreChiffresSignificatifs));
        QTableWidgetItem* itemPointReelY = new QTableWidgetItem(
                QString::number(point.getPointReelY(), formatNotationNombresCaractere,
                        nombreChiffresSignificatifs));
        QTableWidgetItem* itemTypePoint = new QTableWidgetItem(point.getTypePointTexte());
        this->ui->tableWidgetListePoints->setItem(itPoint, 0, itemPointPixelX);
        this->ui->tableWidgetListePoints->setItem(itPoint, 1, itemPointPixelY);
        this->ui->tableWidgetListePoints->setItem(itPoint, 2, itemPointReelX);
        this->ui->tableWidgetListePoints->setItem(itPoint, 3, itemPointReelY);
        this->ui->tableWidgetListePoints->setItem(itPoint, 4, itemTypePoint);
    }
    this->ui->tableWidgetListePoints->resizeColumnsToContents();
}

void EcranPrincipal::repositionnerVueGraphiqueEtude()
{
    this->ui->vueGraphiqueEtude->repositionner();
}

void EcranPrincipal::effacerVueGraphiqueEtude()
{
    this->ui->vueGraphiqueEtude->effacer();
}

void EcranPrincipal::dessinerVueGraphiqueEtude()
{
    this->ui->vueGraphiqueEtude->dessiner(this->etude);
}

void EcranPrincipal::activerBouton(const QPushButton* pushButton)
{
    if (!pushButton || !pushButton->isChecked())
    {
        this->ui->vueGraphiqueEtude->setDragMode(QGraphicsView::ScrollHandDrag);
        this->ui->pushButtonPointX0->setChecked(false);
        this->ui->pushButtonPointY0->setChecked(false);
        this->ui->pushButtonPointX1->setChecked(false);
        this->ui->pushButtonPointY1->setChecked(false);
        this->ui->pushButtonPointDepart->setChecked(false);
        this->ui->pushButtonPointArrivee->setChecked(false);
        this->ui->pushButtonPointManuel->setChecked(false);
        this->pushButtonActif = nullptr;
    }
    else
    {
        this->ui->vueGraphiqueEtude->setDragMode(QGraphicsView::NoDrag);
        if (this->pushButtonActif && this->pushButtonActif != pushButton)
        {
            this->pushButtonActif->setChecked(false);
        }
        this->pushButtonActif = const_cast<QPushButton*>(pushButton);
    }
}

void EcranPrincipal::actualiserPoint(const QPointF& pointVueGraphique)
{
    if (this->pushButtonActif == this->ui->pushButtonPointX0
            || this->pushButtonActif == this->ui->pushButtonPointX1
            || this->pushButtonActif == this->ui->pushButtonPointY0
            || this->pushButtonActif == this->ui->pushButtonPointY1)
    {
        this->actualiserPointRepere(pointVueGraphique);
    }
    else if (this->pushButtonActif == this->ui->pushButtonPointDepart
            || this->pushButtonActif == this->ui->pushButtonPointArrivee
            || this->pushButtonActif == this->ui->pushButtonPointManuel)
    {
        this->actualiserPointCourbe(pointVueGraphique);
    }
}

void EcranPrincipal::actualiserPointRepere(const QPointF& pointVueGraphique)
{
    const int ppx = static_cast<int>(floor(pointVueGraphique.x()));
    const int ppy = static_cast<int>(floor(pointVueGraphique.y()));
    Repere repere = this->etude.getRepere();

    const QString ppxTexte = QString::number(ppx);
    const QString ppyTexte = QString::number(ppy);

    if (this->pushButtonActif == this->ui->pushButtonPointX0)
    {
        Point pointX0 = repere.getPointX0();
        pointX0.setPointPixelX(ppx);
        pointX0.setPointPixelY(ppy);
        repere.setPointX0(pointX0);
        this->etude.setRepere(repere);
        this->ui->lineEditPointX0XPixel->setText(ppxTexte);
        this->ui->lineEditPointX0YPixel->setText(ppyTexte);
        this->actualiserCoordonneesPoints();
        this->dessinerVueGraphiqueEtude();
        this->ui->lineEditPointX0Valeur->setFocus();
    }
    else if (this->pushButtonActif == this->ui->pushButtonPointX1)
    {
        Point pointX1 = repere.getPointX1();
        pointX1.setPointPixelX(ppx);
        pointX1.setPointPixelY(ppy);
        repere.setPointX1(pointX1);
        this->etude.setRepere(repere);
        this->ui->lineEditPointX1XPixel->setText(ppxTexte);
        this->ui->lineEditPointX1YPixel->setText(ppyTexte);
        this->actualiserCoordonneesPoints();
        this->dessinerVueGraphiqueEtude();
        this->ui->lineEditPointX1Valeur->setFocus();
    }
    else if (this->pushButtonActif == this->ui->pushButtonPointY0)
    {
        Point pointY0 = repere.getPointY0();
        pointY0.setPointPixelX(ppx);
        pointY0.setPointPixelY(ppy);
        repere.setPointY0(pointY0);
        this->etude.setRepere(repere);
        this->ui->lineEditPointY0XPixel->setText(ppxTexte);
        this->ui->lineEditPointY0YPixel->setText(ppyTexte);
        this->actualiserCoordonneesPoints();
        this->dessinerVueGraphiqueEtude();
        this->ui->lineEditPointY0Valeur->setFocus();
    }
    else if (this->pushButtonActif == this->ui->pushButtonPointY1)
    {
        Point pointY1 = repere.getPointY1();
        pointY1.setPointPixelX(ppx);
        pointY1.setPointPixelY(ppy);
        repere.setPointY1(pointY1);
        this->etude.setRepere(repere);
        this->ui->lineEditPointY1XPixel->setText(ppxTexte);
        this->ui->lineEditPointY1YPixel->setText(ppyTexte);
        this->actualiserCoordonneesPoints();
        this->dessinerVueGraphiqueEtude();
        this->ui->lineEditPointY1Valeur->setFocus();
    }
}

void EcranPrincipal::actualiserPointCourbe(const QPointF& pointVueGraphique)
{
    const Parametres& parametres = this->etude.getParametres();
    const ParametresAffichage& parametresAffichage = parametres.getParametresAffichage();
    const char formatNotationNombresCaractere =
            parametresAffichage.getFormatNotationNombresCaractere();
    const int& nombreChiffresSignificatifs = parametresAffichage.getNombreChiffresSignificatifs();

    const int ppx = static_cast<int>(floor(pointVueGraphique.x()));
    const int ppy = static_cast<int>(floor(pointVueGraphique.y()));
    double prx = 0.0;
    double pry = 0.0;
    this->etude.getRepere().pixelVersReel(ppx, ppy, prx, pry);

    const QString ppxTexte = QString::number(ppx);
    const QString ppyTexte = QString::number(ppy);
    const QString prxTexte = QString::number(prx, formatNotationNombresCaractere,
            nombreChiffresSignificatifs);
    const QString pryTexte = QString::number(pry, formatNotationNombresCaractere,
            nombreChiffresSignificatifs);

    if (this->pushButtonActif == this->ui->pushButtonPointDepart)
    {
        this->ui->lineEditPointDepartXPixel->setText(ppxTexte);
        this->ui->lineEditPointDepartYPixel->setText(ppyTexte);
        this->ui->lineEditPointDepartXReel->setText(prxTexte);
        this->ui->lineEditPointDepartYReel->setText(pryTexte);
    }
    else if (this->pushButtonActif == this->ui->pushButtonPointArrivee)
    {
        this->ui->lineEditPointArriveeXPixel->setText(ppxTexte);
        this->ui->lineEditPointArriveeYPixel->setText(ppyTexte);
        this->ui->lineEditPointArriveeXReel->setText(prxTexte);
        this->ui->lineEditPointArriveeYReel->setText(pryTexte);
    }
    else if (this->pushButtonActif == this->ui->pushButtonPointManuel)
    {
        this->ui->lineEditPointManuelXPixel->setText(ppxTexte);
        this->ui->lineEditPointManuelYPixel->setText(ppyTexte);
        this->ui->lineEditPointManuelXReel->setText(prxTexte);
        this->ui->lineEditPointManuelYReel->setText(pryTexte);
    }
}

void EcranPrincipal::actualiserBarreStatut(const QPointF& pointVueGraphique)
{
    const Parametres& parametres = this->etude.getParametres();
    const ParametresAffichage& parametresAffichage = parametres.getParametresAffichage();
    const char formatNotationNombresCaractere =
            parametresAffichage.getFormatNotationNombresCaractere();
    const int& nombreChiffresSignificatifs = parametresAffichage.getNombreChiffresSignificatifs();

    const int ppx = static_cast<int>(floor(pointVueGraphique.x()));
    const int ppy = static_cast<int>(floor(pointVueGraphique.y()));
    double prx = 0.0;
    double pry = 0.0;
    this->etude.getRepere().pixelVersReel(ppx, ppy, prx, pry);

    const QString ppxTexte = QString::number(ppx);
    const QString ppyTexte = QString::number(ppy);
    const QString prxTexte = QString::number(prx, formatNotationNombresCaractere,
            nombreChiffresSignificatifs);
    const QString pryTexte = QString::number(pry, formatNotationNombresCaractere,
            nombreChiffresSignificatifs);
    const QString statusBarTexte = QString::fromUtf8("Pixel=(%1:%2) - Réel=(%3:%4)").arg(ppxTexte,
            ppyTexte, prxTexte, pryTexte);

    this->ui->statusBar->showMessage(statusBarTexte);
}

void EcranPrincipal::on_actionCreerEtude_triggered()
{
    this->verifierEtatSauvegardeEtude();
    this->creerNouvelleEtude();
}

void EcranPrincipal::on_actionChargerEtude_triggered()
{
    this->verifierEtatSauvegardeEtude();
    this->chargerEtudeExistante();
}

void EcranPrincipal::on_actionSauverEtude_triggered()
{
    this->sauverEtudeCourante();
}

void EcranPrincipal::on_actionExporterListePoints_triggered()
{
    this->exporterListeDePointsCourante();
}

void EcranPrincipal::on_actionExporterImage_triggered()
{
    this->exporterImageConvertieCourante();
}

void EcranPrincipal::on_actionQuitter_triggered()
{
    this->verifierEtatSauvegardeEtude();
    this->close();
}

void EcranPrincipal::on_actionParametresAffichage_triggered()
{
    Parametres parametres = this->etude.getParametres();
    ParametresAffichage parametresAffichage = parametres.getParametresAffichage();
    FenetreParametresAffichage* fenetreParametresAffichage = new FenetreParametresAffichage(this);
    fenetreParametresAffichage->setParametresAffichage(parametresAffichage);
    fenetreParametresAffichage->actualiserElementsGraphiques();
    if (fenetreParametresAffichage->exec() == QDialog::Rejected)
        return;
    parametresAffichage = fenetreParametresAffichage->getParametresAffichage();
    parametres.setParametresAffichage(parametresAffichage);
    this->etude.setParametres(parametres);

    this->actualiserCoordonneesPoints();
    this->dessinerVueGraphiqueEtude();
}

void EcranPrincipal::on_actionParametresConversion_triggered()
{
    Parametres parametres = this->etude.getParametres();
    ParametresConversion parametresConversion = parametres.getParametresConversion();
    FenetreParametresConversion* fenetreParametresConversion = new FenetreParametresConversion(
            this);
    fenetreParametresConversion->setParametresConversion(parametresConversion);
    fenetreParametresConversion->actualiserElementsGraphiques();
    if (fenetreParametresConversion->exec() == QDialog::Rejected)
        return;
    parametresConversion = fenetreParametresConversion->getParametresConversion();
    parametres.setParametresConversion(parametresConversion);
    this->etude.setParametres(parametres);
}

void EcranPrincipal::on_actionParametresRecherche_triggered()
{
    Parametres parametres = this->etude.getParametres();
    ParametresRecherche parametresRecherche = parametres.getParametresRecherche();
    FenetreParametresRecherche* fenetreParametresRecherche = new FenetreParametresRecherche(this);
    fenetreParametresRecherche->setParametresRecherche(parametresRecherche);
    fenetreParametresRecherche->actualiserElementsGraphiques();
    if (fenetreParametresRecherche->exec() == QDialog::Rejected)
        return;
    parametresRecherche = fenetreParametresRecherche->getParametresRecherche();
    parametres.setParametresRecherche(parametresRecherche);
    this->etude.setParametres(parametres);
}

void EcranPrincipal::on_actionParametresExport_triggered()
{
    Parametres parametres = this->etude.getParametres();
    ParametresExport parametresExport = parametres.getParametresExport();
    FenetreParametresExport* fenetreParametresExport = new FenetreParametresExport(this);
    fenetreParametresExport->setParametresExport(parametresExport);
    fenetreParametresExport->actualiserElementsGraphiques();
    if (fenetreParametresExport->exec() == QDialog::Rejected)
        return;
    parametresExport = fenetreParametresExport->getParametresExport();
    parametres.setParametresExport(parametresExport);
    this->etude.setParametres(parametres);
}

void EcranPrincipal::on_actionChargerParametres_triggered()
{
    this->chargerParametresExistants();
}

void EcranPrincipal::on_actionSauverParametres_triggered()
{
    this->sauverParametresCourants();
}

void EcranPrincipal::on_actionDocumentation_triggered()
{
    FenetreDocumentation* fenetreDocumentation = new FenetreDocumentation(this);
    fenetreDocumentation->exec();
}

void EcranPrincipal::on_actionAbout_triggered()
{
    QMessageBox* fenetreMessage = new QMessageBox(QMessageBox::Information,
            QString::fromUtf8("NumerisationDeCourbes"),
            QString::fromUtf8("NumerisationDeCourbes - Version 1.2.0 (03/10/2020).\n"
                    "Réalisée par Alexis Foerster (alexis.foerster@gmail.com)."), QMessageBox::Ok,
            this);
    fenetreMessage->exec();
}

void EcranPrincipal::on_pushButtonConvertir_clicked()
{
    int methodeConversion = ParametresConversion::BRUTE;
    if (this->ui->radioButtonNoirEtBlanc->isChecked())
    {
        methodeConversion = ParametresConversion::NOIR_ET_BLANC;
    }
    else if (this->ui->radioButtonNiveauxDeGris->isChecked())
    {
        methodeConversion = ParametresConversion::NIVEAUX_DE_GRIS;
    }
    else if (this->ui->radioButtonTeintesSaturees->isChecked())
    {
        methodeConversion = ParametresConversion::TEINTES_SATUREES;
    }
    Parametres parametres = this->etude.getParametres();
    ParametresConversion parametresConversion = parametres.getParametresConversion();
    parametresConversion.setMethodeConversion(methodeConversion);
    parametres.setParametresConversion(parametresConversion);
    this->etude.setParametres(parametres);

    this->etude.convertirImage();

    this->dessinerVueGraphiqueEtude();
}

void EcranPrincipal::on_pushButtonRestaurer_clicked()
{
    const int methodeConversion = ParametresConversion::BRUTE;
    Parametres parametres = this->etude.getParametres();
    ParametresConversion parametresConversion = parametres.getParametresConversion();
    parametresConversion.setMethodeConversion(methodeConversion);
    parametres.setParametresConversion(parametresConversion);
    this->etude.setParametres(parametres);

    this->etude.restaurerImage();

    this->dessinerVueGraphiqueEtude();
}

void EcranPrincipal::on_lineEditPointX0XPixel_textChanged()
{
    Repere repere = this->etude.getRepere();
    Point pointX0 = repere.getPointX0();
    pointX0.setPointPixelX(this->ui->lineEditPointX0XPixel->text().toInt());
    repere.setPointX0(pointX0);
    this->etude.setRepere(repere);

    this->actualiserCoordonneesPoints();
    this->dessinerVueGraphiqueEtude();
}

void EcranPrincipal::on_lineEditPointX0YPixel_textChanged()
{
    Repere repere = this->etude.getRepere();
    Point pointX0 = repere.getPointX0();
    pointX0.setPointPixelY(this->ui->lineEditPointX0YPixel->text().toInt());
    repere.setPointX0(pointX0);
    this->etude.setRepere(repere);

    this->actualiserCoordonneesPoints();
    this->dessinerVueGraphiqueEtude();
}

void EcranPrincipal::on_lineEditPointX0Valeur_textChanged()
{
    Repere repere = this->etude.getRepere();
    Point pointX0 = repere.getPointX0();
    pointX0.setPointReelX(this->ui->lineEditPointX0Valeur->text().toDouble());
    repere.setPointX0(pointX0);
    this->etude.setRepere(repere);

    this->actualiserCoordonneesPoints();
    this->dessinerVueGraphiqueEtude();
}

void EcranPrincipal::on_lineEditPointX1XPixel_textChanged()
{
    Repere repere = this->etude.getRepere();
    Point pointX1 = repere.getPointX1();
    pointX1.setPointPixelX(this->ui->lineEditPointX1XPixel->text().toInt());
    repere.setPointX1(pointX1);
    this->etude.setRepere(repere);

    this->actualiserCoordonneesPoints();
    this->dessinerVueGraphiqueEtude();
}

void EcranPrincipal::on_lineEditPointX1YPixel_textChanged()
{
    Repere repere = this->etude.getRepere();
    Point pointX1 = repere.getPointX1();
    pointX1.setPointPixelY(this->ui->lineEditPointX1YPixel->text().toInt());
    repere.setPointX1(pointX1);
    this->etude.setRepere(repere);

    this->actualiserCoordonneesPoints();
    this->dessinerVueGraphiqueEtude();
}

void EcranPrincipal::on_lineEditPointX1Valeur_textChanged()
{
    Repere repere = this->etude.getRepere();
    Point pointX1 = repere.getPointX1();
    pointX1.setPointReelX(this->ui->lineEditPointX1Valeur->text().toDouble());
    repere.setPointX1(pointX1);
    this->etude.setRepere(repere);

    this->actualiserCoordonneesPoints();
    this->dessinerVueGraphiqueEtude();
}

void EcranPrincipal::on_lineEditPointY0XPixel_textChanged()
{
    Repere repere = this->etude.getRepere();
    Point pointY0 = repere.getPointY0();
    pointY0.setPointPixelX(this->ui->lineEditPointY0XPixel->text().toInt());
    repere.setPointY0(pointY0);
    this->etude.setRepere(repere);

    this->actualiserCoordonneesPoints();
    this->dessinerVueGraphiqueEtude();
}

void EcranPrincipal::on_lineEditPointY0YPixel_textChanged()
{
    Repere repere = this->etude.getRepere();
    Point pointY0 = repere.getPointY0();
    pointY0.setPointPixelY(this->ui->lineEditPointY0YPixel->text().toInt());
    repere.setPointY0(pointY0);
    this->etude.setRepere(repere);

    this->actualiserCoordonneesPoints();
    this->dessinerVueGraphiqueEtude();
}

void EcranPrincipal::on_lineEditPointY0Valeur_textChanged()
{
    Repere repere = this->etude.getRepere();
    Point pointY0 = repere.getPointY0();
    pointY0.setPointReelY(this->ui->lineEditPointY0Valeur->text().toDouble());
    repere.setPointY0(pointY0);
    this->etude.setRepere(repere);

    this->actualiserCoordonneesPoints();
    this->dessinerVueGraphiqueEtude();
}

void EcranPrincipal::on_lineEditPointY1XPixel_textChanged()
{
    Repere repere = this->etude.getRepere();
    Point pointY1 = repere.getPointY1();
    pointY1.setPointPixelX(this->ui->lineEditPointY1XPixel->text().toInt());
    repere.setPointY1(pointY1);
    this->etude.setRepere(repere);

    this->actualiserCoordonneesPoints();
    this->dessinerVueGraphiqueEtude();
}

void EcranPrincipal::on_lineEditPointY1YPixel_textChanged()
{
    Repere repere = this->etude.getRepere();
    Point pointY1 = repere.getPointY1();
    pointY1.setPointPixelY(this->ui->lineEditPointY1YPixel->text().toInt());
    repere.setPointY1(pointY1);
    this->etude.setRepere(repere);

    this->actualiserCoordonneesPoints();
    this->dessinerVueGraphiqueEtude();
}

void EcranPrincipal::on_lineEditPointY1Valeur_textChanged()
{
    Repere repere = this->etude.getRepere();
    Point pointY1 = repere.getPointY1();
    pointY1.setPointReelY(this->ui->lineEditPointY1Valeur->text().toDouble());
    repere.setPointY1(pointY1);
    this->etude.setRepere(repere);

    this->actualiserCoordonneesPoints();
    this->dessinerVueGraphiqueEtude();
}

void EcranPrincipal::on_pushButtonPointX0_clicked()
{
    this->activerBouton(this->ui->pushButtonPointX0);
}

void EcranPrincipal::on_pushButtonPointX1_clicked()
{
    this->activerBouton(this->ui->pushButtonPointX1);
}

void EcranPrincipal::on_pushButtonPointY0_clicked()
{
    this->activerBouton(this->ui->pushButtonPointY0);
}

void EcranPrincipal::on_pushButtonPointY1_clicked()
{
    this->activerBouton(this->ui->pushButtonPointY1);
}

void EcranPrincipal::on_lineEditPointDepartXPixel_textChanged()
{
    this->actualiserCoordonneesPointDepart();
}

void EcranPrincipal::on_lineEditPointDepartYPixel_textChanged()
{
    this->actualiserCoordonneesPointDepart();
}

void EcranPrincipal::on_lineEditPointArriveeXPixel_textChanged()
{
    this->actualiserCoordonneesPointArrivee();
}

void EcranPrincipal::on_lineEditPointArriveeYPixel_textChanged()
{
    this->actualiserCoordonneesPointArrivee();
}

void EcranPrincipal::on_lineEditPointManuelXPixel_textChanged()
{
    this->actualiserCoordonneesPointManuel();
}

void EcranPrincipal::on_lineEditPointManuelYPixel_textChanged()
{
    this->actualiserCoordonneesPointManuel();
}

void EcranPrincipal::on_pushButtonPointDepart_clicked()
{
    this->activerBouton(this->ui->pushButtonPointDepart);
}

void EcranPrincipal::on_pushButtonPointArrivee_clicked()
{
    this->activerBouton(this->ui->pushButtonPointArrivee);
}

void EcranPrincipal::on_pushButtonPointManuel_clicked()
{
    this->activerBouton(this->ui->pushButtonPointManuel);
}

void EcranPrincipal::on_pushButtonAjouter_clicked()
{
    const int pointPixelX = this->ui->lineEditPointManuelXPixel->text().toInt();
    const int pointPixelY = this->ui->lineEditPointManuelYPixel->text().toInt();
    double pointReelX = 0.0;
    double pointReelY = 0.0;
    this->etude.getRepere().pixelVersReel(pointPixelX, pointPixelY, pointReelX, pointReelY);

    QList<Point> listeDePoints = this->etude.getListeDePoints();
    Point point(pointPixelX, pointPixelY, pointReelX, pointReelY, Point::MANUEL);
    listeDePoints.append(point);
    this->etude.setListeDePoints(listeDePoints);

    this->actualiserCoordonneesListeDePoints();
    this->dessinerVueGraphiqueEtude();
}

void EcranPrincipal::on_pushButtonRechercher_clicked()
{
    const QPoint pointPixelDepart = QPoint(this->ui->lineEditPointDepartXPixel->text().toInt(),
            this->ui->lineEditPointDepartYPixel->text().toInt());
    const QPoint pointPixelArrivee = QPoint(this->ui->lineEditPointArriveeXPixel->text().toInt(),
            this->ui->lineEditPointArriveeYPixel->text().toInt());
    const QList<Courbe> listeDeCourbes = this->etude.rechercherCourbes(pointPixelDepart,
            pointPixelArrivee);

    QList<Point> listeDePoints = this->etude.getListeDePoints();
    const int nombreDeCourbes = listeDeCourbes.count();
    for (int itCourbe = 0; itCourbe < nombreDeCourbes; itCourbe++)
    {
        const Courbe& courbe = listeDeCourbes.at(itCourbe);
        const int nombreDePointsCourbe = courbe.count();
        for (int itPointCourbe = 0; itPointCourbe < nombreDePointsCourbe; itPointCourbe++)
        {
            const Point& pointCourbe = courbe.at(itPointCourbe);
            listeDePoints.append(pointCourbe);
        }
    }
    this->etude.setListeDePoints(listeDePoints);

    this->actualiserCoordonneesListeDePoints();
    this->dessinerVueGraphiqueEtude();
}

void EcranPrincipal::on_pushButtonSupprimer_clicked()
{
    const QModelIndexList listeLignesSelectionnees =
            this->ui->tableWidgetListePoints->selectionModel()->selectedRows();

    QList<Point> listeDePoints = this->etude.getListeDePoints();
    const int nombreLignesSelectionnees = listeLignesSelectionnees.count();
    for (int itLigneSelectionnee = (nombreLignesSelectionnees - 1); itLigneSelectionnee >= 0;
            itLigneSelectionnee--)
    {
        listeDePoints.removeAt(listeLignesSelectionnees.at(itLigneSelectionnee).row());
    }
    if (nombreLignesSelectionnees == 0)
    {
        listeDePoints.clear();
    }

    const QList<Courbe> listeDeCourbes = this->etude.getListeDeCourbes();
    const int nombreDeCourbes = listeDeCourbes.count();
    for (int itCourbe = 0; itCourbe < nombreDeCourbes; itCourbe++)
    {
        Courbe listeDePointsCourbe = listeDeCourbes.at(itCourbe);
        int nombreDePointsCourbe = listeDePointsCourbe.count();
        for (int itPointCourbe = (nombreDePointsCourbe - 1); itPointCourbe >= 0; itPointCourbe--)
        {
            const Point& pointCourbe = listeDePointsCourbe.at(itPointCourbe);
            if (!listeDePoints.contains(pointCourbe))
            {
                listeDePointsCourbe.removeAt(itPointCourbe);
            }
        }
        nombreDePointsCourbe = listeDePointsCourbe.count();
        if (nombreDePointsCourbe > 1)
        {
            Point premierPointCourbe = listeDePointsCourbe.at(0);
            Point dernierPointCourbe = listeDePointsCourbe.at(nombreDePointsCourbe - 1);
            const int itPremierPointCourbe = listeDePoints.indexOf(premierPointCourbe);
            const int itDernierPointCourbe = listeDePoints.indexOf(dernierPointCourbe);
            premierPointCourbe.setTypePoint(Point::COURBE_DEBUT);
            dernierPointCourbe.setTypePoint(Point::COURBE_FIN);
            listeDePoints[itPremierPointCourbe] = premierPointCourbe;
            listeDePoints[itDernierPointCourbe] = dernierPointCourbe;
        }
        else if (nombreDePointsCourbe > 0)
        {
            Point pointCourbe = listeDePointsCourbe.at(0);
            const int itPointCourbe = listeDePoints.indexOf(pointCourbe);
            pointCourbe.setTypePoint(Point::MANUEL);
            listeDePoints[itPointCourbe] = pointCourbe;
        }
    }

    this->etude.setListeDePoints(listeDePoints);

    this->actualiserCoordonneesListeDePoints();
    this->dessinerVueGraphiqueEtude();
}

void EcranPrincipal::on_pushButtonGraphique_clicked()
{
    const QList<Courbe> listeDeCourbes = this->etude.getListeDeCourbes();
    const QList<Point> listeDePointsManuels = this->etude.getListeDePointsManuels();
    const ParametresGraphique parametresGraphiques = this->etude.getParametresGraphiques();
    Parametres parametres = this->etude.getParametres();
    ParametresAffichage parametresAffichage = parametres.getParametresAffichage();
    ParametresFichiers parametresFichiers = parametres.getParametresFichiers();
    FenetreGraphique* fenetreGraphique = new FenetreGraphique(this);
    fenetreGraphique->setListeDeCourbes(listeDeCourbes);
    fenetreGraphique->setListeDePointsManuels(listeDePointsManuels);
    fenetreGraphique->setParametresGraphique(parametresGraphiques);
    fenetreGraphique->setParametresAffichage(parametresAffichage);
    fenetreGraphique->setParametresFichiers(parametresFichiers);
    fenetreGraphique->actualiserElementsGraphiques();
    if (fenetreGraphique->exec() == QDialog::Rejected)
        return;
    parametresFichiers = fenetreGraphique->getParametresFichiers();
    parametres.setParametresFichiers(parametresFichiers);
    this->etude.setParametres(parametres);
}

void EcranPrincipal::mousePressEventSlot(const QPointF pointVueGraphique)
{
    this->actualiserPoint(pointVueGraphique);

    this->activerBouton(nullptr);
}

void EcranPrincipal::mouseMoveEventSlot(const QPointF pointVueGraphique)
{
    this->actualiserBarreStatut(pointVueGraphique);
}
