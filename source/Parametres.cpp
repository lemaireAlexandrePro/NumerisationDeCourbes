//==============================================================================
// Name        : Parametres.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Source file of the Parametres class
//==============================================================================

#include "Parametres.h"
#include "Outils.h"
#include <QStringList>

Parametres::Parametres()
{
    this->clear();
}

Parametres::Parametres(const ParametresFichiers& parametresFichiers,
        const ParametresAffichage& parametresAffichage,
        const ParametresConversion& parametresConversion,
        const ParametresRecherche& parametresRecherche, const ParametresExport& parametresExport) :
        Parametres()
{
    this->set(parametresFichiers, parametresAffichage, parametresConversion, parametresRecherche,
            parametresExport);
}

Parametres::Parametres(const Parametres& parametres) :
        Parametres()
{
    this->copy(parametres);
}

Parametres::~Parametres()
{
}

Parametres& Parametres::operator=(const Parametres& parametres)
{
    this->copy(parametres);
    return *this;
}

bool Parametres::operator==(const Parametres& parametres) const
{
    return this->equals(parametres);
}

bool Parametres::operator!=(const Parametres& parametres) const
{
    return !this->equals(parametres);
}

const ParametresFichiers& Parametres::getParametresFichiers() const
{
    return this->parametresFichiers;
}

const ParametresAffichage& Parametres::getParametresAffichage() const
{
    return this->parametresAffichage;
}

const ParametresConversion& Parametres::getParametresConversion() const
{
    return this->parametresConversion;
}

const ParametresRecherche& Parametres::getParametresRecherche() const
{
    return this->parametresRecherche;
}

const ParametresExport& Parametres::getParametresExport() const
{
    return this->parametresExport;
}

void Parametres::setParametresFichiers(const ParametresFichiers& parametresFichiers)
{
    this->parametresFichiers = parametresFichiers;
}

void Parametres::setParametresAffichage(const ParametresAffichage& parametresAffichage)
{
    this->parametresAffichage = parametresAffichage;
}

void Parametres::setParametresConversion(const ParametresConversion& parametresConversion)
{
    this->parametresConversion = parametresConversion;
}

void Parametres::setParametresRecherche(const ParametresRecherche& parametresRecherche)
{
    this->parametresRecherche = parametresRecherche;
}

void Parametres::setParametresExport(const ParametresExport& parametresExport)
{
    this->parametresExport = parametresExport;
}

void Parametres::clear()
{
    this->set(ParametresFichiers(), ParametresAffichage(), ParametresConversion(),
            ParametresRecherche(), ParametresExport());
}

void Parametres::set(const ParametresFichiers& parametresFichiers,
        const ParametresAffichage& parametresAffichage,
        const ParametresConversion& parametresConversion,
        const ParametresRecherche& parametresRecherche, const ParametresExport& parametresExport)
{
    this->setParametresFichiers(parametresFichiers);
    this->setParametresAffichage(parametresAffichage);
    this->setParametresConversion(parametresConversion);
    this->setParametresRecherche(parametresRecherche);
    this->setParametresExport(parametresExport);
}

void Parametres::copy(const Parametres& parametres)
{
    this->set(parametres.getParametresFichiers(), parametres.getParametresAffichage(),
            parametres.getParametresConversion(), parametres.getParametresRecherche(),
            parametres.getParametresExport());
}

bool Parametres::equals(const Parametres& parametres) const
{
    if (!this->getParametresFichiers().equals(parametres.getParametresFichiers()))
        return false;
    if (!this->getParametresAffichage().equals(parametres.getParametresAffichage()))
        return false;
    if (!this->getParametresConversion().equals(parametres.getParametresConversion()))
        return false;
    if (!this->getParametresRecherche().equals(parametres.getParametresRecherche()))
        return false;
    if (!this->getParametresExport().equals(parametres.getParametresExport()))
        return false;
    return true;
}

void Parametres::fromString(const QString& fromString, const QChar& sep)
{
    const QStringList fromStringList = listeSousElements(fromString, sep);
    ParametresFichiers parametresFichiers = this->getParametresFichiers();
    ParametresAffichage parametresAffichage = this->getParametresAffichage();
    ParametresConversion parametresConversion = this->getParametresConversion();
    ParametresRecherche parametresRecherche = this->getParametresRecherche();
    ParametresExport parametresExport = this->getParametresExport();
    parametresFichiers.fromString(fromStringList.at(0), sep);
    parametresAffichage.fromString(fromStringList.at(1), sep);
    parametresConversion.fromString(fromStringList.at(2), sep);
    parametresRecherche.fromString(fromStringList.at(3), sep);
    parametresExport.fromString(fromStringList.at(4), sep);
    this->setParametresFichiers(parametresFichiers);
    this->setParametresAffichage(parametresAffichage);
    this->setParametresConversion(parametresConversion);
    this->setParametresRecherche(parametresRecherche);
    this->setParametresExport(parametresExport);
}

const QString Parametres::toString(const QChar& sep) const
{
    QString toString;
    toString += QString("(%1)").arg(this->getParametresFichiers().toString(sep)) + sep;
    toString += QString("(%1)").arg(this->getParametresAffichage().toString(sep)) + sep;
    toString += QString("(%1)").arg(this->getParametresConversion().toString(sep)) + sep;
    toString += QString("(%1)").arg(this->getParametresRecherche().toString(sep)) + sep;
    toString += QString("(%1)").arg(this->getParametresExport().toString(sep));
    return toString;
}
