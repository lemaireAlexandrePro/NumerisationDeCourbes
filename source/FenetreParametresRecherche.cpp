//==============================================================================
// Name        : FenetreParametresRecherche.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Source file of the FenetreParametresRecherche class
//==============================================================================

#include "FenetreParametresRecherche.h"
#include "ui_FenetreParametresRecherche.h"
#include <QDialogButtonBox>
#include <QPushButton>

FenetreParametresRecherche::FenetreParametresRecherche(QWidget* parent) :
        QDialog(parent), ui(new Ui::FenetreParametresRecherche)
{
    this->ui->setupUi(this);
    this->initialiserElementsGraphiques();
    this->actualiserElementsGraphiques();
}

FenetreParametresRecherche::~FenetreParametresRecherche()
{
    delete this->ui;
}

const ParametresRecherche& FenetreParametresRecherche::getParametresRecherche() const
{
    return this->parametresRecherche;
}

void FenetreParametresRecherche::setParametresRecherche(
        const ParametresRecherche& parametresRecherche)
{
    this->parametresRecherche = parametresRecherche;
}

void FenetreParametresRecherche::initialiserElementsGraphiques()
{
    this->ui->spinBoxSeuilToleranceNiveauxDeGris->setMinimum(0);
    this->ui->spinBoxSeuilToleranceNiveauxDeGris->setMaximum(255);
    this->ui->doubleSpinBoxSeuilToleranceNiveauxDeGrisFacteur->setMinimum(0.0);
    this->ui->doubleSpinBoxSeuilToleranceNiveauxDeGrisFacteur->setMaximum(100.0);
    this->ui->spinBoxSeuilToleranceTeintesSaturees->setMinimum(0);
    this->ui->spinBoxSeuilToleranceTeintesSaturees->setMaximum(360);
    this->ui->doubleSpinBoxSeuilToleranceTeintesSatureesFacteur->setMinimum(0.0);
    this->ui->doubleSpinBoxSeuilToleranceTeintesSatureesFacteur->setMaximum(100.0);
    this->ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Annuler");
}

void FenetreParametresRecherche::actualiserElementsGraphiques()
{
    this->ui->spinBoxSeuilToleranceNiveauxDeGris->setValue(
            this->parametresRecherche.getSeuilToleranceNiveauxDeGris());
    this->ui->doubleSpinBoxSeuilToleranceNiveauxDeGrisFacteur->setValue(
            this->parametresRecherche.getSeuilToleranceNiveauxDeGrisFacteur() * 100.0);
    this->ui->spinBoxSeuilToleranceTeintesSaturees->setValue(
            this->parametresRecherche.getSeuilToleranceTeintesSaturees());
    this->ui->doubleSpinBoxSeuilToleranceTeintesSatureesFacteur->setValue(
            this->parametresRecherche.getSeuilToleranceTeintesSatureesFacteur() * 100.0);
    this->ui->checkBoxSelectionValeursMoyennes->setChecked(
            this->parametresRecherche.getSelectionValeursMoyennes());
    this->ui->checkBoxSelectionValeursMinimales->setChecked(
            this->parametresRecherche.getSelectionValeursMinimales());
    this->ui->checkBoxSelectionValeursMaximales->setChecked(
            this->parametresRecherche.getSelectionValeursMaximales());
}

void FenetreParametresRecherche::on_spinBoxSeuilToleranceNiveauxDeGris_valueChanged()
{
    this->parametresRecherche.setSeuilToleranceNiveauxDeGris(
            this->ui->spinBoxSeuilToleranceNiveauxDeGris->value());
    this->ui->doubleSpinBoxSeuilToleranceNiveauxDeGrisFacteur->blockSignals(true);
    this->ui->doubleSpinBoxSeuilToleranceNiveauxDeGrisFacteur->setValue(
            this->parametresRecherche.getSeuilToleranceNiveauxDeGrisFacteur() * 100.0);
    this->ui->doubleSpinBoxSeuilToleranceNiveauxDeGrisFacteur->blockSignals(false);
}

void FenetreParametresRecherche::on_doubleSpinBoxSeuilToleranceNiveauxDeGrisFacteur_valueChanged()
{
    this->parametresRecherche.setSeuilToleranceNiveauxDeGrisFacteur(
            this->ui->doubleSpinBoxSeuilToleranceNiveauxDeGrisFacteur->value() / 100.0);
    this->ui->spinBoxSeuilToleranceNiveauxDeGris->blockSignals(true);
    this->ui->spinBoxSeuilToleranceNiveauxDeGris->setValue(
            this->parametresRecherche.getSeuilToleranceNiveauxDeGris());
    this->ui->spinBoxSeuilToleranceNiveauxDeGris->blockSignals(false);
}

void FenetreParametresRecherche::on_spinBoxSeuilToleranceTeintesSaturees_valueChanged()
{
    this->parametresRecherche.setSeuilToleranceTeintesSaturees(
            this->ui->spinBoxSeuilToleranceTeintesSaturees->value());
    this->ui->doubleSpinBoxSeuilToleranceTeintesSatureesFacteur->blockSignals(true);
    this->ui->doubleSpinBoxSeuilToleranceTeintesSatureesFacteur->setValue(
            this->parametresRecherche.getSeuilToleranceTeintesSatureesFacteur() * 100.0);
    this->ui->doubleSpinBoxSeuilToleranceTeintesSatureesFacteur->blockSignals(false);
}

void FenetreParametresRecherche::on_doubleSpinBoxSeuilToleranceTeintesSatureesFacteur_valueChanged()
{
    this->parametresRecherche.setSeuilToleranceTeintesSatureesFacteur(
            this->ui->doubleSpinBoxSeuilToleranceTeintesSatureesFacteur->value() / 100.0);
    this->ui->spinBoxSeuilToleranceTeintesSaturees->blockSignals(true);
    this->ui->spinBoxSeuilToleranceTeintesSaturees->setValue(
            this->parametresRecherche.getSeuilToleranceTeintesSaturees());
    this->ui->spinBoxSeuilToleranceTeintesSaturees->blockSignals(false);
}

void FenetreParametresRecherche::on_checkBoxSelectionValeursMoyennes_stateChanged()
{
    this->parametresRecherche.setSelectionValeursMoyennes(
            this->ui->checkBoxSelectionValeursMoyennes->isChecked());
}

void FenetreParametresRecherche::on_checkBoxSelectionValeursMinimales_stateChanged()
{
    this->parametresRecherche.setSelectionValeursMinimales(
            this->ui->checkBoxSelectionValeursMinimales->isChecked());
}

void FenetreParametresRecherche::on_checkBoxSelectionValeursMaximales_stateChanged()
{
    this->parametresRecherche.setSelectionValeursMaximales(
            this->ui->checkBoxSelectionValeursMaximales->isChecked());
}
