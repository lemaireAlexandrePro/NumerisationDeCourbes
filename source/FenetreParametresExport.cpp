//==============================================================================
// Name        : FenetreParametresExport.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Source file of the FenetreParametresExport class
//==============================================================================

#include "FenetreParametresExport.h"
#include "ui_FenetreParametresExport.h"
#include <QDialogButtonBox>
#include <QDoubleValidator>
#include <QPushButton>
#include <QString>

FenetreParametresExport::FenetreParametresExport(QWidget* parent) :
        QDialog(parent), ui(new Ui::FenetreParametresExport)
{
    this->ui->setupUi(this);
    this->initialiserElementsGraphiques();
    this->actualiserElementsGraphiques();
}

FenetreParametresExport::~FenetreParametresExport()
{
    delete this->ui;
}

const ParametresExport& FenetreParametresExport::getParametresExport() const
{
    return this->parametresExport;
}

void FenetreParametresExport::setParametresExport(const ParametresExport& parametresExport)
{
    this->parametresExport = parametresExport;
}

void FenetreParametresExport::initialiserElementsGraphiques()
{
    const QDoubleValidator* nombreReel = new QDoubleValidator(this);
    this->ui->lineEditSeuilInterpolationNumerique->setValidator(nombreReel);
    this->ui->lineEditSeuilInterpolationNumerique->setValidator(nombreReel);
    this->ui->spinBoxNombreDecimalesOuChiffresSignificatifs->setMinimum(0);
    this->ui->spinBoxNombreDecimalesOuChiffresSignificatifs->setMaximum(20);
    this->ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Annuler");
}

void FenetreParametresExport::actualiserElementsGraphiques()
{
    this->ui->comboBoxCaractereSeparation->setCurrentIndex(
            this->parametresExport.getCaractereSeparationIndice());
    this->ui->lineEditSeuilInterpolationNumerique->setText(
            QString::number(this->parametresExport.getSeuilInterpolationNumerique()));
    this->ui->comboBoxFormatNotationNombres->setCurrentIndex(
            this->parametresExport.getFormatNotationNombres());
    this->ui->comboBoxCaractereSeparateurDecimal->setCurrentIndex(
            this->parametresExport.getCaractereSeparateurDecimalIndice());
    this->ui->spinBoxNombreDecimalesOuChiffresSignificatifs->setValue(
            this->parametresExport.getNombreChiffresSignificatifs());
}

void FenetreParametresExport::on_comboBoxCaractereSeparation_currentIndexChanged()
{
    this->parametresExport.setCaractereSeparationIndice(
            this->ui->comboBoxCaractereSeparation->currentIndex());
}

void FenetreParametresExport::on_comboBoxFormatNotationNombres_currentIndexChanged()
{
    this->parametresExport.setFormatNotationNombres(
            this->ui->comboBoxFormatNotationNombres->currentIndex());
}

void FenetreParametresExport::on_comboBoxCaractereSeparateurDecimal_currentIndexChanged()
{
    this->parametresExport.setCaractereSeparateurDecimalIndice(
            this->ui->comboBoxCaractereSeparateurDecimal->currentIndex());
}

void FenetreParametresExport::on_spinBoxNombreDecimalesOuChiffresSignificatifs_valueChanged()
{
    this->parametresExport.setNombreChiffresSignificatifs(
            this->ui->spinBoxNombreDecimalesOuChiffresSignificatifs->value());
}

void FenetreParametresExport::on_lineEditSeuilInterpolationNumerique_textChanged()
{
    this->parametresExport.setSeuilInterpolationNumerique(
            this->ui->lineEditSeuilInterpolationNumerique->text().toDouble());
}
