//==============================================================================
// Name        : ParametresConversion.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Source file of the ParametresConversion class
//==============================================================================

#include "ParametresConversion.h"
#include "Outils.h"
#include <cmath>
#include <QStringList>

const int ParametresConversion::methodeConversionDefaut = BRUTE;
const int ParametresConversion::seuilNoirEtBlancDefaut = 223;
const int ParametresConversion::nombreNiveauxDeGrisDefaut = 5;
const int ParametresConversion::nombreTeintesSatureesDefaut = 6;
const int ParametresConversion::seuilSaturationDefaut = 32;

const QMap<int, QString> ParametresConversion::methodesConversionTexte =
        QMap<int, QString>(
                std::map<int, QString> { { BRUTE, QString::fromUtf8("Brute") }, { NOIR_ET_BLANC,
                        QString::fromUtf8("Noir et blanc") }, { NIVEAUX_DE_GRIS, QString::fromUtf8(
                        "Niveaux de gris") }, { TEINTES_SATUREES, QString::fromUtf8(
                        "Teintes saturées") } });

ParametresConversion::ParametresConversion() :
        methodeConversion(methodeConversionDefaut), seuilNoirEtBlanc(seuilNoirEtBlancDefaut),
                nombreNiveauxDeGris(nombreNiveauxDeGrisDefaut),
                nombreTeintesSaturees(nombreTeintesSatureesDefaut),
                seuilSaturation(seuilSaturationDefaut)
{
    this->clear();
}

ParametresConversion::ParametresConversion(const int& methodeConversion,
        const int& seuilNoirEtBlanc, const int& nombreNiveauxDeGris,
        const int& nombreTeintesSaturees, const int& seuilSaturation) :
        ParametresConversion()
{
    this->set(methodeConversion, seuilNoirEtBlanc, nombreNiveauxDeGris, nombreTeintesSaturees,
            seuilSaturation);
}

ParametresConversion::ParametresConversion(const ParametresConversion& parametresConversion) :
        ParametresConversion()
{
    this->copy(parametresConversion);
}

ParametresConversion::~ParametresConversion()
{
}

ParametresConversion& ParametresConversion::operator=(
        const ParametresConversion& parametresConversion)
{
    this->copy(parametresConversion);
    return *this;
}

bool ParametresConversion::operator==(const ParametresConversion& parametresConversion) const
{
    return this->equals(parametresConversion);
}

bool ParametresConversion::operator!=(const ParametresConversion& parametresConversion) const
{
    return !this->equals(parametresConversion);
}

const int& ParametresConversion::getMethodeConversion() const
{
    return this->methodeConversion;
}

const int& ParametresConversion::getSeuilNoirEtBlanc() const
{
    return this->seuilNoirEtBlanc;
}

const int& ParametresConversion::getNombreNiveauxDeGris() const
{
    return this->nombreNiveauxDeGris;
}

const int& ParametresConversion::getNombreTeintesSaturees() const
{
    return this->nombreTeintesSaturees;
}

const int& ParametresConversion::getSeuilSaturation() const
{
    return this->seuilSaturation;
}

void ParametresConversion::setMethodeConversion(const int& methodeConversion)
{
    this->methodeConversion = methodeConversion;
}

void ParametresConversion::setSeuilNoirEtBlanc(const int& seuilNoirEtBlanc)
{
    this->seuilNoirEtBlanc = seuilNoirEtBlanc;
}

void ParametresConversion::setNombreNiveauxDeGris(const int& nombreNiveauxDeGris)
{
    this->nombreNiveauxDeGris = nombreNiveauxDeGris;
}

void ParametresConversion::setNombreTeintesSaturees(const int& nombreTeintesSaturees)
{
    this->nombreTeintesSaturees = nombreTeintesSaturees;
}

void ParametresConversion::setSeuilSaturation(const int& seuilSaturation)
{
    this->seuilSaturation = seuilSaturation;
}

void ParametresConversion::clear()
{
    this->set(methodeConversionDefaut, seuilNoirEtBlancDefaut, nombreNiveauxDeGrisDefaut,
            nombreTeintesSatureesDefaut, seuilSaturationDefaut);
}

void ParametresConversion::set(const int& methodeConversion, const int& seuilNoirEtBlanc,
        const int& nombreNiveauxDeGris, const int& nombreTeintesSaturees,
        const int& seuilSaturation)
{
    this->setMethodeConversion(methodeConversion);
    this->setSeuilNoirEtBlanc(seuilNoirEtBlanc);
    this->setNombreNiveauxDeGris(nombreNiveauxDeGris);
    this->setNombreTeintesSaturees(nombreTeintesSaturees);
    this->setSeuilSaturation(seuilSaturation);
}

void ParametresConversion::copy(const ParametresConversion& parametresConversion)
{
    this->set(parametresConversion.getMethodeConversion(),
            parametresConversion.getSeuilNoirEtBlanc(),
            parametresConversion.getNombreNiveauxDeGris(),
            parametresConversion.getNombreTeintesSaturees(),
            parametresConversion.getSeuilSaturation());
}

bool ParametresConversion::equals(const ParametresConversion& parametresConversion) const
{
    if (this->getMethodeConversion() != parametresConversion.getMethodeConversion())
        return false;
    if (this->getSeuilNoirEtBlanc() != parametresConversion.getSeuilNoirEtBlanc())
        return false;
    if (this->getNombreNiveauxDeGris() != parametresConversion.getNombreNiveauxDeGris())
        return false;
    if (this->getNombreTeintesSaturees() != parametresConversion.getNombreTeintesSaturees())
        return false;
    if (this->getSeuilSaturation() != parametresConversion.getSeuilSaturation())
        return false;
    return true;
}

void ParametresConversion::fromString(const QString& fromString, const QChar& sep)
{
    const QStringList fromStringList = listeSousElements(fromString, sep);
    this->setMethodeConversion(fromStringList.at(0).toInt());
    this->setSeuilNoirEtBlanc(fromStringList.at(1).toInt());
    this->setNombreNiveauxDeGris(fromStringList.at(2).toInt());
    this->setNombreTeintesSaturees(fromStringList.at(3).toInt());
    this->setSeuilSaturation(fromStringList.at(4).toInt());
}

const QString ParametresConversion::toString(const QChar& sep) const
{
    QString toString;
    toString += QString::number(this->getMethodeConversion()) + sep;
    toString += QString::number(this->getSeuilNoirEtBlanc()) + sep;
    toString += QString::number(this->getNombreNiveauxDeGris()) + sep;
    toString += QString::number(this->getNombreTeintesSaturees()) + sep;
    toString += QString::number(this->getSeuilSaturation());
    return toString;
}

const QString ParametresConversion::getMethodeConversionTexte() const
{
    return methodesConversionTexte.value(this->getMethodeConversion());
}

double ParametresConversion::getSeuilNoirEtBlancFacteur() const
{
    return (this->getSeuilNoirEtBlanc() / 255.0);
}

double ParametresConversion::getSeuilSaturationFacteur() const
{
    return (this->getSeuilSaturation() / 255.0);
}

void ParametresConversion::setMethodeConversionTexte(const QString& methodeConversionTexte)
{
    this->setMethodeConversion(methodesConversionTexte.key(methodeConversionTexte));
}

void ParametresConversion::setSeuilNoirEtBlancFacteur(const double& seuilNoirEtBlancFacteur)
{
    this->setSeuilNoirEtBlanc(static_cast<int>(round(seuilNoirEtBlancFacteur * 255.0)));
}

void ParametresConversion::setSeuilSaturationFacteur(const double& seuilSaturationFacteur)
{
    this->setSeuilSaturation(static_cast<int>(round(seuilSaturationFacteur * 255.0)));
}
