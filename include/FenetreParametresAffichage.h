//==============================================================================
// Name        : FenetreParametresAffichage.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Header file of the FenetreParametresAffichage class
//==============================================================================

#ifndef FENETREPARAMETRESAFFICHAGE_H
#define FENETREPARAMETRESAFFICHAGE_H

#include "ParametresAffichage.h"
#include <QDialog>
#include <QWidget>

namespace Ui
{
class FenetreParametresAffichage;
}

class FenetreParametresAffichage : public QDialog
{
    Q_OBJECT

public:
    // Constructeurs et destructeurs
    explicit FenetreParametresAffichage(QWidget* parent = nullptr);
    ~FenetreParametresAffichage();

    // Getters
    const ParametresAffichage& getParametresAffichage() const;

    // Setters
    void setParametresAffichage(const ParametresAffichage& parametresAffichage);

    // Méthodes génériques

    // Méthodes spécifiques
    void actualiserElementsGraphiques();

protected:
    // Méthodes spécifiques
    void initialiserElementsGraphiques();

protected slots:
    // Connecteurs spécifiques
    void on_comboBoxFormatNotationNombres_currentIndexChanged();
    void on_spinBoxNombreDecimalesOuChiffresSignificatifs_valueChanged();
    void on_pushButtonCouleurAxes_clicked();
    void on_comboBoxStyleAxes_currentIndexChanged();
    void on_spinBoxEpaisseurAxes_valueChanged();
    void on_pushButtonCouleurCourbes_clicked();
    void on_comboBoxStyleCourbes_currentIndexChanged();
    void on_spinBoxEpaisseurCourbes_valueChanged();
    void on_pushButtonCouleurPointsAxes_clicked();
    void on_comboBoxStylePointsAxes_currentIndexChanged();
    void on_spinBoxEpaisseurPointsAxes_valueChanged();
    void on_pushButtonCouleurPointsCourbes_clicked();
    void on_comboBoxStylePointsCourbes_currentIndexChanged();
    void on_spinBoxEpaisseurPointsCourbes_valueChanged();
    void on_pushButtonCouleurPointsManuels_clicked();
    void on_comboBoxStylePointsManuels_currentIndexChanged();
    void on_spinBoxEpaisseurPointsManuels_valueChanged();

private:
    // Attributs de classe
    Ui::FenetreParametresAffichage* ui;
    ParametresAffichage parametresAffichage;
};

#endif /* FENETREPARAMETRESAFFICHAGE_H */
