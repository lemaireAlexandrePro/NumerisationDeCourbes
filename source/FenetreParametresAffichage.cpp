//==============================================================================
// Name        : FenetreParametresAffichage.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Source file of the FenetreParametresAffichage class
//==============================================================================

#include "FenetreParametresAffichage.h"
#include "ui_FenetreParametresAffichage.h"
#include "ParametresPoint.h"
#include "ParametresTrait.h"
#include <QColor>
#include <QColorDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QRgb>
#include <QString>

FenetreParametresAffichage::FenetreParametresAffichage(QWidget* parent) :
        QDialog(parent), ui(new Ui::FenetreParametresAffichage)
{
    this->ui->setupUi(this);
    this->initialiserElementsGraphiques();
    this->actualiserElementsGraphiques();
}

FenetreParametresAffichage::~FenetreParametresAffichage()
{
    delete this->ui;
}

const ParametresAffichage& FenetreParametresAffichage::getParametresAffichage() const
{
    return this->parametresAffichage;
}

void FenetreParametresAffichage::setParametresAffichage(
        const ParametresAffichage& parametresAffichage)
{
    this->parametresAffichage = parametresAffichage;
}

void FenetreParametresAffichage::initialiserElementsGraphiques()
{
    this->ui->spinBoxNombreDecimalesOuChiffresSignificatifs->setMinimum(0);
    this->ui->spinBoxNombreDecimalesOuChiffresSignificatifs->setMaximum(20);
    this->ui->spinBoxEpaisseurAxes->setMinimum(0);
    this->ui->spinBoxEpaisseurAxes->setMaximum(20);
    this->ui->spinBoxEpaisseurCourbes->setMinimum(0);
    this->ui->spinBoxEpaisseurCourbes->setMaximum(20);
    this->ui->spinBoxEpaisseurPointsAxes->setMinimum(0);
    this->ui->spinBoxEpaisseurPointsAxes->setMaximum(20);
    this->ui->spinBoxEpaisseurPointsCourbes->setMinimum(0);
    this->ui->spinBoxEpaisseurPointsCourbes->setMaximum(20);
    this->ui->spinBoxEpaisseurPointsManuels->setMinimum(0);
    this->ui->spinBoxEpaisseurPointsManuels->setMaximum(20);
    this->ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Annuler");
}

void FenetreParametresAffichage::actualiserElementsGraphiques()
{
    const QRgb& couleurAxes = this->parametresAffichage.getParametresAxes().getCouleurTrait();
    const QRgb& couleurCourbes = this->parametresAffichage.getParametresCourbes().getCouleurTrait();
    const QRgb& couleurPointsAxes =
            this->parametresAffichage.getParametresPointsAxes().getCouleurPoint();
    const QRgb& couleurPointsCourbes =
            this->parametresAffichage.getParametresPointsCourbes().getCouleurPoint();
    const QRgb& couleurPointsManuels =
            this->parametresAffichage.getParametresPointsManuels().getCouleurPoint();

    const QString texteCouleurAxes = QColor(couleurAxes).name().toUpper();
    const QString texteCouleurCourbes = QColor(couleurCourbes).name().toUpper();
    const QString texteCouleurPointsAxes = QColor(couleurPointsAxes).name().toUpper();
    const QString texteCouleurPointsCourbes = QColor(couleurPointsCourbes).name().toUpper();
    const QString texteCouleurPointsManuels = QColor(couleurPointsManuels).name().toUpper();

    this->ui->comboBoxFormatNotationNombres->setCurrentIndex(
            this->parametresAffichage.getFormatNotationNombres());
    this->ui->spinBoxNombreDecimalesOuChiffresSignificatifs->setValue(
            this->parametresAffichage.getNombreChiffresSignificatifs());
    this->ui->pushButtonCouleurAxes->setText(texteCouleurAxes);
    this->ui->pushButtonCouleurAxes->setStyleSheet(
            QString("background-color: %1").arg(texteCouleurAxes));
    this->ui->spinBoxEpaisseurAxes->setValue(
            this->parametresAffichage.getParametresAxes().getEpaisseurTrait());
    this->ui->comboBoxStyleAxes->setCurrentIndex(
            this->parametresAffichage.getParametresAxes().getStyleTrait());
    this->ui->pushButtonCouleurCourbes->setText(texteCouleurCourbes);
    this->ui->pushButtonCouleurCourbes->setStyleSheet(
            QString("background-color: %1").arg(texteCouleurCourbes));
    this->ui->spinBoxEpaisseurCourbes->setValue(
            this->parametresAffichage.getParametresCourbes().getEpaisseurTrait());
    this->ui->comboBoxStyleCourbes->setCurrentIndex(
            this->parametresAffichage.getParametresCourbes().getStyleTrait());
    this->ui->pushButtonCouleurPointsAxes->setText(texteCouleurPointsAxes);
    this->ui->pushButtonCouleurPointsAxes->setStyleSheet(
            QString("background-color: %1").arg(texteCouleurPointsAxes));
    this->ui->spinBoxEpaisseurPointsAxes->setValue(
            this->parametresAffichage.getParametresPointsAxes().getEpaisseurPoint());
    this->ui->comboBoxStylePointsAxes->setCurrentIndex(
            this->parametresAffichage.getParametresPointsAxes().getStylePoint());
    this->ui->pushButtonCouleurPointsCourbes->setText(texteCouleurPointsCourbes);
    this->ui->pushButtonCouleurPointsCourbes->setStyleSheet(
            QString("background-color: %1").arg(texteCouleurPointsCourbes));
    this->ui->spinBoxEpaisseurPointsCourbes->setValue(
            this->parametresAffichage.getParametresPointsCourbes().getEpaisseurPoint());
    this->ui->comboBoxStylePointsCourbes->setCurrentIndex(
            this->parametresAffichage.getParametresPointsCourbes().getStylePoint());
    this->ui->pushButtonCouleurPointsManuels->setText(texteCouleurPointsManuels);
    this->ui->pushButtonCouleurPointsManuels->setStyleSheet(
            QString("background-color: %1").arg(texteCouleurPointsManuels));
    this->ui->spinBoxEpaisseurPointsManuels->setValue(
            this->parametresAffichage.getParametresPointsManuels().getEpaisseurPoint());
    this->ui->comboBoxStylePointsManuels->setCurrentIndex(
            this->parametresAffichage.getParametresPointsManuels().getStylePoint());
}

void FenetreParametresAffichage::on_comboBoxFormatNotationNombres_currentIndexChanged()
{
    this->parametresAffichage.setFormatNotationNombres(
            this->ui->comboBoxFormatNotationNombres->currentIndex());
}

void FenetreParametresAffichage::on_spinBoxNombreDecimalesOuChiffresSignificatifs_valueChanged()
{
    this->parametresAffichage.setNombreChiffresSignificatifs(
            this->ui->spinBoxNombreDecimalesOuChiffresSignificatifs->value());
}

void FenetreParametresAffichage::on_pushButtonCouleurAxes_clicked()
{
    ParametresTrait parametresAxes = this->parametresAffichage.getParametresAxes();
    QColorDialog* fenetreCouleurAxes = new QColorDialog(QColor(parametresAxes.getCouleurTrait()),
            this);
    if (fenetreCouleurAxes->exec() == QColorDialog::Rejected)
        return;
    parametresAxes.setCouleurTrait(fenetreCouleurAxes->selectedColor().rgb());
    this->parametresAffichage.setParametresAxes(parametresAxes);
    this->actualiserElementsGraphiques();
}

void FenetreParametresAffichage::on_comboBoxStyleAxes_currentIndexChanged()
{
    ParametresTrait parametresAxes = this->parametresAffichage.getParametresAxes();
    parametresAxes.setStyleTrait(this->ui->comboBoxStyleAxes->currentIndex());
    this->parametresAffichage.setParametresAxes(parametresAxes);
}

void FenetreParametresAffichage::on_spinBoxEpaisseurAxes_valueChanged()
{
    ParametresTrait parametresAxes = this->parametresAffichage.getParametresAxes();
    parametresAxes.setEpaisseurTrait(this->ui->spinBoxEpaisseurAxes->value());
    this->parametresAffichage.setParametresAxes(parametresAxes);
}

void FenetreParametresAffichage::on_pushButtonCouleurCourbes_clicked()
{
    ParametresTrait parametresCourbes = this->parametresAffichage.getParametresCourbes();
    QColorDialog* fenetreCouleurCourbes = new QColorDialog(
            QColor(parametresCourbes.getCouleurTrait()), this);
    if (fenetreCouleurCourbes->exec() == QColorDialog::Rejected)
        return;
    parametresCourbes.setCouleurTrait(fenetreCouleurCourbes->selectedColor().rgb());
    this->parametresAffichage.setParametresCourbes(parametresCourbes);
    this->actualiserElementsGraphiques();
}

void FenetreParametresAffichage::on_comboBoxStyleCourbes_currentIndexChanged()
{
    ParametresTrait parametresCourbes = this->parametresAffichage.getParametresCourbes();
    parametresCourbes.setStyleTrait(this->ui->comboBoxStyleCourbes->currentIndex());
    this->parametresAffichage.setParametresCourbes(parametresCourbes);
}

void FenetreParametresAffichage::on_spinBoxEpaisseurCourbes_valueChanged()
{
    ParametresTrait parametresCourbes = this->parametresAffichage.getParametresCourbes();
    parametresCourbes.setEpaisseurTrait(this->ui->spinBoxEpaisseurCourbes->value());
    this->parametresAffichage.setParametresCourbes(parametresCourbes);
}

void FenetreParametresAffichage::on_pushButtonCouleurPointsAxes_clicked()
{
    ParametresPoint parametresPointsAxes = this->parametresAffichage.getParametresPointsAxes();
    QColorDialog* fenetreCouleurPointsAxes = new QColorDialog(
            QColor(parametresPointsAxes.getCouleurPoint()), this);
    if (fenetreCouleurPointsAxes->exec() == QColorDialog::Rejected)
        return;
    parametresPointsAxes.setCouleurPoint(fenetreCouleurPointsAxes->selectedColor().rgb());
    this->parametresAffichage.setParametresPointsAxes(parametresPointsAxes);
    this->actualiserElementsGraphiques();
}

void FenetreParametresAffichage::on_comboBoxStylePointsAxes_currentIndexChanged()
{
    ParametresPoint parametresPointsAxes = this->parametresAffichage.getParametresPointsAxes();
    parametresPointsAxes.setStylePoint(this->ui->comboBoxStylePointsAxes->currentIndex());
    this->parametresAffichage.setParametresPointsAxes(parametresPointsAxes);
}

void FenetreParametresAffichage::on_spinBoxEpaisseurPointsAxes_valueChanged()
{
    ParametresPoint parametresPointsAxes = this->parametresAffichage.getParametresPointsAxes();
    parametresPointsAxes.setEpaisseurPoint(this->ui->spinBoxEpaisseurPointsAxes->value());
    this->parametresAffichage.setParametresPointsAxes(parametresPointsAxes);
}

void FenetreParametresAffichage::on_pushButtonCouleurPointsCourbes_clicked()
{
    ParametresPoint parametresPointsCourbes =
            this->parametresAffichage.getParametresPointsCourbes();
    QColorDialog* fenetreCouleurPointsCourbes = new QColorDialog(
            QColor(parametresPointsCourbes.getCouleurPoint()), this);
    if (fenetreCouleurPointsCourbes->exec() == QColorDialog::Rejected)
        return;
    parametresPointsCourbes.setCouleurPoint(fenetreCouleurPointsCourbes->selectedColor().rgb());
    this->parametresAffichage.setParametresPointsCourbes(parametresPointsCourbes);
    this->actualiserElementsGraphiques();
}

void FenetreParametresAffichage::on_comboBoxStylePointsCourbes_currentIndexChanged()
{
    ParametresPoint parametresPointsCourbes =
            this->parametresAffichage.getParametresPointsCourbes();
    parametresPointsCourbes.setStylePoint(this->ui->comboBoxStylePointsCourbes->currentIndex());
    this->parametresAffichage.setParametresPointsCourbes(parametresPointsCourbes);
}

void FenetreParametresAffichage::on_spinBoxEpaisseurPointsCourbes_valueChanged()
{
    ParametresPoint parametresPointsCourbes =
            this->parametresAffichage.getParametresPointsCourbes();
    parametresPointsCourbes.setEpaisseurPoint(this->ui->spinBoxEpaisseurPointsCourbes->value());
    this->parametresAffichage.setParametresPointsCourbes(parametresPointsCourbes);
}

void FenetreParametresAffichage::on_pushButtonCouleurPointsManuels_clicked()
{
    ParametresPoint parametresPointsManuels =
            this->parametresAffichage.getParametresPointsManuels();
    QColorDialog* fenetreCouleurPointsManuels = new QColorDialog(
            QColor(parametresPointsManuels.getCouleurPoint()), this);
    if (fenetreCouleurPointsManuels->exec() == QColorDialog::Rejected)
        return;
    parametresPointsManuels.setCouleurPoint(fenetreCouleurPointsManuels->selectedColor().rgb());
    this->parametresAffichage.setParametresPointsManuels(parametresPointsManuels);
    this->actualiserElementsGraphiques();
}

void FenetreParametresAffichage::on_comboBoxStylePointsManuels_currentIndexChanged()
{
    ParametresPoint parametresPointsManuels =
            this->parametresAffichage.getParametresPointsManuels();
    parametresPointsManuels.setStylePoint(this->ui->comboBoxStylePointsManuels->currentIndex());
    this->parametresAffichage.setParametresPointsManuels(parametresPointsManuels);
}

void FenetreParametresAffichage::on_spinBoxEpaisseurPointsManuels_valueChanged()
{
    ParametresPoint parametresPointsManuels =
            this->parametresAffichage.getParametresPointsManuels();
    parametresPointsManuels.setEpaisseurPoint(this->ui->spinBoxEpaisseurPointsManuels->value());
    this->parametresAffichage.setParametresPointsManuels(parametresPointsManuels);
}
