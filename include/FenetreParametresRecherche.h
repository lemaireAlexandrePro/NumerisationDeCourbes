//==============================================================================
// Name        : FenetreParametresRecherche.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Header file of the FenetreParametresRecherche class
//==============================================================================

#ifndef FENETREPARAMETRESRECHERCHE_H
#define FENETREPARAMETRESRECHERCHE_H

#include "ParametresRecherche.h"
#include <QDialog>
#include <QWidget>

namespace Ui
{
class FenetreParametresRecherche;
}

class FenetreParametresRecherche : public QDialog
{
    Q_OBJECT

public:
    // Constructeurs et destructeurs
    explicit FenetreParametresRecherche(QWidget* parent = nullptr);
    ~FenetreParametresRecherche();

    // Getters
    const ParametresRecherche& getParametresRecherche() const;

    // Setters
    void setParametresRecherche(const ParametresRecherche& parametresRecherche);

    // Méthodes génériques

    // Méthodes spécifiques
    void actualiserElementsGraphiques();

protected:
    // Méthodes spécifiques
    void initialiserElementsGraphiques();

protected slots:
    // Connecteurs spécifiques
    void on_spinBoxSeuilToleranceNiveauxDeGris_valueChanged();
    void on_doubleSpinBoxSeuilToleranceNiveauxDeGrisFacteur_valueChanged();
    void on_spinBoxSeuilToleranceTeintesSaturees_valueChanged();
    void on_doubleSpinBoxSeuilToleranceTeintesSatureesFacteur_valueChanged();
    void on_checkBoxSelectionValeursMoyennes_stateChanged();
    void on_checkBoxSelectionValeursMinimales_stateChanged();
    void on_checkBoxSelectionValeursMaximales_stateChanged();

private:
    // Attributs de classe
    Ui::FenetreParametresRecherche* ui;
    ParametresRecherche parametresRecherche;
};

#endif /* FENETREPARAMETRESRECHERCHE_H */
