//==============================================================================
// Name        : FenetreParametresConversion.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Source file of the FenetreParametresConversion class
//==============================================================================

#include "FenetreParametresConversion.h"
#include "ui_FenetreParametresConversion.h"
#include <QDialogButtonBox>
#include <QPushButton>

FenetreParametresConversion::FenetreParametresConversion(QWidget* parent) :
        QDialog(parent), ui(new Ui::FenetreParametresConversion)
{
    this->ui->setupUi(this);
    this->initialiserElementsGraphiques();
    this->actualiserElementsGraphiques();
}

FenetreParametresConversion::~FenetreParametresConversion()
{
    delete this->ui;
}

const ParametresConversion& FenetreParametresConversion::getParametresConversion() const
{
    return this->parametresConversion;
}

void FenetreParametresConversion::setParametresConversion(
        const ParametresConversion& parametresConversion)
{
    this->parametresConversion = parametresConversion;
}

void FenetreParametresConversion::initialiserElementsGraphiques()
{
    this->ui->spinBoxSeuilNoirEtBlanc->setMinimum(0);
    this->ui->spinBoxSeuilNoirEtBlanc->setMaximum(255);
    this->ui->doubleSpinBoxSeuilNoirEtBlancFacteur->setMinimum(0.0);
    this->ui->doubleSpinBoxSeuilNoirEtBlancFacteur->setMaximum(100.0);
    this->ui->spinBoxNombreNiveauxDeGris->setMinimum(2);
    this->ui->spinBoxNombreNiveauxDeGris->setMaximum(256);
    this->ui->spinBoxNombreTeintesSaturees->setMinimum(1);
    this->ui->spinBoxNombreTeintesSaturees->setMaximum(360);
    this->ui->spinBoxSeuilSaturation->setMinimum(0);
    this->ui->spinBoxSeuilSaturation->setMaximum(255);
    this->ui->doubleSpinBoxSeuilSaturationFacteur->setMinimum(0.0);
    this->ui->doubleSpinBoxSeuilSaturationFacteur->setMaximum(100.0);
    this->ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Annuler");
}

void FenetreParametresConversion::actualiserElementsGraphiques()
{
    this->ui->spinBoxSeuilNoirEtBlanc->setValue(this->parametresConversion.getSeuilNoirEtBlanc());
    this->ui->doubleSpinBoxSeuilNoirEtBlancFacteur->setValue(
            this->parametresConversion.getSeuilNoirEtBlancFacteur() * 100.0);
    this->ui->spinBoxNombreNiveauxDeGris->setValue(
            this->parametresConversion.getNombreNiveauxDeGris());
    this->ui->spinBoxNombreTeintesSaturees->setValue(
            this->parametresConversion.getNombreTeintesSaturees());
    this->ui->spinBoxSeuilSaturation->setValue(this->parametresConversion.getSeuilSaturation());
    this->ui->doubleSpinBoxSeuilSaturationFacteur->setValue(
            this->parametresConversion.getSeuilSaturationFacteur() * 100.0);
}

void FenetreParametresConversion::on_spinBoxSeuilNoirEtBlanc_valueChanged()
{
    this->parametresConversion.setSeuilNoirEtBlanc(this->ui->spinBoxSeuilNoirEtBlanc->value());
    this->ui->doubleSpinBoxSeuilNoirEtBlancFacteur->blockSignals(true);
    this->ui->doubleSpinBoxSeuilNoirEtBlancFacteur->setValue(
            this->parametresConversion.getSeuilNoirEtBlancFacteur() * 100.0);
    this->ui->doubleSpinBoxSeuilNoirEtBlancFacteur->blockSignals(false);
}

void FenetreParametresConversion::on_doubleSpinBoxSeuilNoirEtBlancFacteur_valueChanged()
{
    this->parametresConversion.setSeuilNoirEtBlancFacteur(
            this->ui->doubleSpinBoxSeuilNoirEtBlancFacteur->value() / 100.0);
    this->ui->spinBoxSeuilNoirEtBlanc->blockSignals(true);
    this->ui->spinBoxSeuilNoirEtBlanc->setValue(this->parametresConversion.getSeuilNoirEtBlanc());
    this->ui->spinBoxSeuilNoirEtBlanc->blockSignals(false);
}

void FenetreParametresConversion::on_spinBoxNombreNiveauxDeGris_valueChanged()
{
    this->parametresConversion.setNombreNiveauxDeGris(
            this->ui->spinBoxNombreNiveauxDeGris->value());
}

void FenetreParametresConversion::on_spinBoxNombreTeintesSaturees_valueChanged()
{
    this->parametresConversion.setNombreTeintesSaturees(
            this->ui->spinBoxNombreTeintesSaturees->value());
}

void FenetreParametresConversion::on_spinBoxSeuilSaturation_valueChanged()
{
    this->parametresConversion.setSeuilSaturation(this->ui->spinBoxSeuilSaturation->value());
    this->ui->doubleSpinBoxSeuilSaturationFacteur->blockSignals(true);
    this->ui->doubleSpinBoxSeuilSaturationFacteur->setValue(
            this->parametresConversion.getSeuilSaturationFacteur() * 100.0);
    this->ui->doubleSpinBoxSeuilSaturationFacteur->blockSignals(false);
}

void FenetreParametresConversion::on_doubleSpinBoxSeuilSaturationFacteur_valueChanged()
{
    this->parametresConversion.setSeuilSaturationFacteur(
            this->ui->doubleSpinBoxSeuilSaturationFacteur->value() / 100.0);
    this->ui->spinBoxSeuilSaturation->blockSignals(true);
    this->ui->spinBoxSeuilSaturation->setValue(this->parametresConversion.getSeuilSaturation());
    this->ui->spinBoxSeuilSaturation->blockSignals(false);
}
