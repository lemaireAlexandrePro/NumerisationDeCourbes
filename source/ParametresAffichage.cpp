//==============================================================================
// Name        : ParametresAffichage.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Source file of the ParametresAffichage class
//==============================================================================

#include "ParametresAffichage.h"
#include "Outils.h"
#include <QStringList>

const int ParametresAffichage::formatNotationNombresDefaut = STANDARD;
const int ParametresAffichage::nombreChiffresSignificatifsDefaut = 6;
const ParametresTrait ParametresAffichage::parametresAxesDefaut = ParametresTrait(
        ParametresTrait::styleTraitDefaut, ParametresTrait::epaisseurTraitDefaut,
        ParametresTrait::couleurTraitAxeDefaut);
const ParametresTrait ParametresAffichage::parametresCourbesDefaut = ParametresTrait(
        ParametresTrait::styleTraitDefaut, ParametresTrait::epaisseurTraitDefaut,
        ParametresTrait::couleurTraitCourbeDefaut);
const ParametresPoint ParametresAffichage::parametresPointsAxesDefaut = ParametresPoint(
        ParametresPoint::stylePointDefaut, ParametresPoint::epaisseurPointDefaut,
        ParametresPoint::couleurPointAxeDefaut);
const ParametresPoint ParametresAffichage::parametresPointsCourbesDefaut = ParametresPoint(
        ParametresPoint::stylePointDefaut, ParametresPoint::epaisseurPointDefaut,
        ParametresPoint::couleurPointCourbeDefaut);
const ParametresPoint ParametresAffichage::parametresPointsManuelsDefaut = ParametresPoint(
        ParametresPoint::stylePointDefaut, ParametresPoint::epaisseurPointDefaut,
        ParametresPoint::couleurPointManuelDefaut);

const QMap<int, char> ParametresAffichage::formatsNotationNombresCaractere = QMap<int, char>(
        std::map<int, char> { { STANDARD, 'f' }, { SCIENTIFIQUE, 'e' } });
const QMap<int, QString> ParametresAffichage::formatsNotationNombresTexte = QMap<int, QString>(
        std::map<int, QString> { { STANDARD, QString::fromUtf8("Standard") }, { SCIENTIFIQUE,
                QString::fromUtf8("Scientifique") } });

ParametresAffichage::ParametresAffichage() :
        formatNotationNombres(formatNotationNombresDefaut),
                nombreChiffresSignificatifs(nombreChiffresSignificatifsDefaut)
{
    this->clear();
}

ParametresAffichage::ParametresAffichage(const int& formatNotationNombres,
        const int& nombreChiffresSignificatifs, const ParametresTrait& parametresAxes,
        const ParametresTrait& parametresCourbes, const ParametresPoint& parametresPointsAxes,
        const ParametresPoint& parametresPointsCourbes,
        const ParametresPoint& parametresPointsManuels) :
        ParametresAffichage()
{
    this->set(formatNotationNombres, nombreChiffresSignificatifs, parametresAxes, parametresCourbes,
            parametresPointsAxes, parametresPointsCourbes, parametresPointsManuels);
}

ParametresAffichage::ParametresAffichage(const ParametresAffichage& parametresAffichage) :
        ParametresAffichage()
{
    this->copy(parametresAffichage);
}

ParametresAffichage::~ParametresAffichage()
{
}

ParametresAffichage& ParametresAffichage::operator=(const ParametresAffichage& parametresAffichage)
{
    this->copy(parametresAffichage);
    return *this;
}

bool ParametresAffichage::operator==(const ParametresAffichage& parametresAffichage) const
{
    return this->equals(parametresAffichage);
}

bool ParametresAffichage::operator!=(const ParametresAffichage& parametresAffichage) const
{
    return !this->equals(parametresAffichage);
}

const int& ParametresAffichage::getFormatNotationNombres() const
{
    return this->formatNotationNombres;
}

const int& ParametresAffichage::getNombreChiffresSignificatifs() const
{
    return this->nombreChiffresSignificatifs;
}

const ParametresTrait& ParametresAffichage::getParametresAxes() const
{
    return this->parametresAxes;
}

const ParametresTrait& ParametresAffichage::getParametresCourbes() const
{
    return this->parametresCourbes;
}

const ParametresPoint& ParametresAffichage::getParametresPointsAxes() const
{
    return this->parametresPointsAxes;
}

const ParametresPoint& ParametresAffichage::getParametresPointsCourbes() const
{
    return this->parametresPointsCourbes;
}

const ParametresPoint& ParametresAffichage::getParametresPointsManuels() const
{
    return this->parametresPointsManuels;
}

void ParametresAffichage::setFormatNotationNombres(const int& formatNotationNombres)
{
    this->formatNotationNombres = formatNotationNombres;
}

void ParametresAffichage::setNombreChiffresSignificatifs(const int& nombreChiffresSignificatifs)
{
    this->nombreChiffresSignificatifs = nombreChiffresSignificatifs;
}

void ParametresAffichage::setParametresAxes(const ParametresTrait& parametresAxes)
{
    this->parametresAxes = parametresAxes;
}

void ParametresAffichage::setParametresCourbes(const ParametresTrait& parametresCourbes)
{
    this->parametresCourbes = parametresCourbes;
}

void ParametresAffichage::setParametresPointsAxes(const ParametresPoint& parametresPointsAxes)
{
    this->parametresPointsAxes = parametresPointsAxes;
}

void ParametresAffichage::setParametresPointsCourbes(const ParametresPoint& parametresPointsCourbes)
{
    this->parametresPointsCourbes = parametresPointsCourbes;
}

void ParametresAffichage::setParametresPointsManuels(const ParametresPoint& parametresPointsManuels)
{
    this->parametresPointsManuels = parametresPointsManuels;
}

void ParametresAffichage::clear()
{
    this->set(formatNotationNombresDefaut, nombreChiffresSignificatifsDefaut, parametresAxesDefaut,
            parametresCourbesDefaut, parametresPointsAxesDefaut, parametresPointsCourbesDefaut,
            parametresPointsManuelsDefaut);
}

void ParametresAffichage::set(const int& formatNotationNombres,
        const int& nombreChiffresSignificatifs, const ParametresTrait& parametresAxes,
        const ParametresTrait& parametresCourbes, const ParametresPoint& parametresPointsAxes,
        const ParametresPoint& parametresPointsCourbes,
        const ParametresPoint& parametresPointsManuels)
{
    this->setFormatNotationNombres(formatNotationNombres);
    this->setNombreChiffresSignificatifs(nombreChiffresSignificatifs);
    this->setParametresAxes(parametresAxes);
    this->setParametresCourbes(parametresCourbes);
    this->setParametresPointsAxes(parametresPointsAxes);
    this->setParametresPointsCourbes(parametresPointsCourbes);
    this->setParametresPointsManuels(parametresPointsManuels);
}

void ParametresAffichage::copy(const ParametresAffichage& parametresAffichage)
{
    this->set(parametresAffichage.getFormatNotationNombres(),
            parametresAffichage.getNombreChiffresSignificatifs(),
            parametresAffichage.getParametresAxes(), parametresAffichage.getParametresCourbes(),
            parametresAffichage.getParametresPointsAxes(),
            parametresAffichage.getParametresPointsCourbes(),
            parametresAffichage.getParametresPointsManuels());
}

bool ParametresAffichage::equals(const ParametresAffichage& parametresAffichage) const
{
    if (this->getFormatNotationNombres() != parametresAffichage.getFormatNotationNombres())
        return false;
    if (this->getNombreChiffresSignificatifs()
            != parametresAffichage.getNombreChiffresSignificatifs())
        return false;
    if (!this->getParametresAxes().equals(parametresAffichage.getParametresAxes()))
        return false;
    if (!this->getParametresCourbes().equals(parametresAffichage.getParametresCourbes()))
        return false;
    if (!this->getParametresPointsAxes().equals(parametresAffichage.getParametresPointsAxes()))
        return false;
    if (!this->getParametresPointsCourbes().equals(
            parametresAffichage.getParametresPointsCourbes()))
        return false;
    if (!this->getParametresPointsManuels().equals(
            parametresAffichage.getParametresPointsManuels()))
        return false;
    return true;
}

void ParametresAffichage::fromString(const QString& fromString, const QChar& sep)
{
    const QStringList fromStringList = listeSousElements(fromString, sep);
    ParametresTrait parametresAxes = this->getParametresAxes();
    ParametresTrait parametresCourbes = this->getParametresCourbes();
    ParametresPoint parametresPointsAxes = this->getParametresPointsAxes();
    ParametresPoint parametresPointsCourbes = this->getParametresPointsCourbes();
    ParametresPoint parametresPointsManuels = this->getParametresPointsManuels();
    parametresAxes.fromString(fromStringList.at(2), sep);
    parametresCourbes.fromString(fromStringList.at(3), sep);
    parametresPointsAxes.fromString(fromStringList.at(4), sep);
    parametresPointsCourbes.fromString(fromStringList.at(5), sep);
    parametresPointsManuels.fromString(fromStringList.at(6), sep);
    this->setFormatNotationNombres(fromStringList.at(0).toInt());
    this->setNombreChiffresSignificatifs(fromStringList.at(1).toInt());
    this->setParametresAxes(parametresAxes);
    this->setParametresCourbes(parametresCourbes);
    this->setParametresPointsAxes(parametresPointsAxes);
    this->setParametresPointsCourbes(parametresPointsCourbes);
    this->setParametresPointsManuels(parametresPointsManuels);
}

const QString ParametresAffichage::toString(const QChar& sep) const
{
    QString toString;
    toString += QString::number(this->getFormatNotationNombres()) + sep;
    toString += QString::number(this->getNombreChiffresSignificatifs()) + sep;
    toString += QString("(%1)").arg(this->getParametresAxes().toString(sep)) + sep;
    toString += QString("(%1)").arg(this->getParametresCourbes().toString(sep)) + sep;
    toString += QString("(%1)").arg(this->getParametresPointsAxes().toString(sep)) + sep;
    toString += QString("(%1)").arg(this->getParametresPointsCourbes().toString(sep)) + sep;
    toString += QString("(%1)").arg(this->getParametresPointsManuels().toString(sep));
    return toString;
}

char ParametresAffichage::getFormatNotationNombresCaractere() const
{
    return formatsNotationNombresCaractere.value(this->getFormatNotationNombres());
}

const QString ParametresAffichage::getFormatNotationNombresTexte() const
{
    return formatsNotationNombresTexte.value(this->getFormatNotationNombres());
}

void ParametresAffichage::setFormatNotationNombresCaractere(
        const char& formatNotationNombresCaractere)
{
    this->setFormatNotationNombres(
            formatsNotationNombresCaractere.key(formatNotationNombresCaractere));
}

void ParametresAffichage::setFormatNotationNombresTexte(const QString& formatNotationNombresTexte)
{
    this->setFormatNotationNombres(formatsNotationNombresTexte.key(formatNotationNombresTexte));
}
