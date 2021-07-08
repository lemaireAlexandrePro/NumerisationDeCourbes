//==============================================================================
// Name        : EcranPrincipal.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Header file of the EcranPrincipal class
//==============================================================================

#ifndef ECRANPRINCIPAL_H
#define ECRANPRINCIPAL_H

#include "Etude.h"
#include <QMainWindow>
#include <QPointF>
#include <QPushButton>
#include <QWidget>

namespace Ui
{
class EcranPrincipal;
}

class EcranPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    // Constructeurs et destructeurs
    explicit EcranPrincipal(QWidget* parent = nullptr);
    ~EcranPrincipal();

    // Getters

    // Setters

    // Méthodes génériques

    // Méthodes spécifiques

protected:
    // Méthodes spécifiques
    void initialiserElementsGraphiques();
    void effacerElementsGraphiques();
    void actualiserElementsGraphiques();
    void creerNouvelleEtude();
    void chargerEtudeExistante();
    void sauverEtudeCourante();
    void exporterListeDePointsCourante();
    void exporterImageConvertieCourante();
    void chargerParametresExistants();
    void sauverParametresCourants();
    void verifierEtatSauvegardeEtude();
    void actualiserEtudeReference();
    void actualiserCoordonneesPoints();
    void actualiserCoordonneesPointDepart();
    void actualiserCoordonneesPointArrivee();
    void actualiserCoordonneesPointManuel();
    void actualiserCoordonneesListeDePoints();
    void repositionnerVueGraphiqueEtude();
    void effacerVueGraphiqueEtude();
    void dessinerVueGraphiqueEtude();
    void activerBouton(const QPushButton* pushButton);
    void actualiserPoint(const QPointF& pointVueGraphique);
    void actualiserPointRepere(const QPointF& pointVueGraphique);
    void actualiserPointCourbe(const QPointF& pointVueGraphique);
    void actualiserBarreStatut(const QPointF& pointVueGraphique);

protected slots:
    // Connecteurs spécifiques
    void on_actionCreerEtude_triggered();
    void on_actionChargerEtude_triggered();
    void on_actionSauverEtude_triggered();
    void on_actionExporterListePoints_triggered();
    void on_actionExporterImage_triggered();
    void on_actionQuitter_triggered();
    void on_actionParametresAffichage_triggered();
    void on_actionParametresConversion_triggered();
    void on_actionParametresRecherche_triggered();
    void on_actionParametresExport_triggered();
    void on_actionChargerParametres_triggered();
    void on_actionSauverParametres_triggered();
    void on_actionDocumentation_triggered();
    void on_actionAbout_triggered();
    void on_pushButtonConvertir_clicked();
    void on_pushButtonRestaurer_clicked();
    void on_lineEditPointX0XPixel_textChanged();
    void on_lineEditPointX0YPixel_textChanged();
    void on_lineEditPointX0Valeur_textChanged();
    void on_lineEditPointX1XPixel_textChanged();
    void on_lineEditPointX1YPixel_textChanged();
    void on_lineEditPointX1Valeur_textChanged();
    void on_lineEditPointY0XPixel_textChanged();
    void on_lineEditPointY0YPixel_textChanged();
    void on_lineEditPointY0Valeur_textChanged();
    void on_lineEditPointY1XPixel_textChanged();
    void on_lineEditPointY1YPixel_textChanged();
    void on_lineEditPointY1Valeur_textChanged();
    void on_pushButtonPointX0_clicked();
    void on_pushButtonPointX1_clicked();
    void on_pushButtonPointY0_clicked();
    void on_pushButtonPointY1_clicked();
    void on_lineEditPointDepartXPixel_textChanged();
    void on_lineEditPointDepartYPixel_textChanged();
    void on_lineEditPointArriveeXPixel_textChanged();
    void on_lineEditPointArriveeYPixel_textChanged();
    void on_lineEditPointManuelXPixel_textChanged();
    void on_lineEditPointManuelYPixel_textChanged();
    void on_pushButtonPointDepart_clicked();
    void on_pushButtonPointArrivee_clicked();
    void on_pushButtonPointManuel_clicked();
    void on_pushButtonAjouter_clicked();
    void on_pushButtonRechercher_clicked();
    void on_pushButtonSupprimer_clicked();
    void on_pushButtonGraphique_clicked();
    void mousePressEventSlot(const QPointF pointVueGraphique);
    void mouseMoveEventSlot(const QPointF pointVueGraphique);

private:
    // Attributs de classe
    Ui::EcranPrincipal* ui;
    Etude etude;
    Etude etudeReference;
    QPushButton* pushButtonActif;
};

#endif /* ECRANPRINCIPAL_H */
