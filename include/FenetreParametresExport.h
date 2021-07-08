//==============================================================================
// Name        : FenetreParametresExport.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Header file of the FenetreParametresExport class
//==============================================================================

#ifndef FENETREPARAMETRESEXPORT_H
#define FENETREPARAMETRESEXPORT_H

#include "ParametresExport.h"
#include <QDialog>
#include <QWidget>

namespace Ui
{
class FenetreParametresExport;
}

class FenetreParametresExport : public QDialog
{
    Q_OBJECT

public:
    // Constructeurs et destructeurs
    explicit FenetreParametresExport(QWidget* parent = nullptr);
    ~FenetreParametresExport();

    // Getters
    const ParametresExport& getParametresExport() const;

    // Setters
    void setParametresExport(const ParametresExport& parametresExport);

    // Méthodes génériques

    // Méthodes spécifiques
    void actualiserElementsGraphiques();

protected:
    // Méthodes spécifiques
    void initialiserElementsGraphiques();

protected slots:
    // Connecteurs spécifiques
    void on_comboBoxCaractereSeparation_currentIndexChanged();
    void on_comboBoxFormatNotationNombres_currentIndexChanged();
    void on_comboBoxCaractereSeparateurDecimal_currentIndexChanged();
    void on_spinBoxNombreDecimalesOuChiffresSignificatifs_valueChanged();
    void on_lineEditSeuilInterpolationNumerique_textChanged();

private:
    // Attributs de classe
    Ui::FenetreParametresExport* ui;
    ParametresExport parametresExport;
};

#endif /* FENETREPARAMETRESEXPORT_H */
