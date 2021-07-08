//==============================================================================
// Name        : ParametresFichiers.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Source file of the ParametresFichiers class
//==============================================================================

#include "ParametresFichiers.h"
#include "Outils.h"
#include <QStringList>

ParametresFichiers::ParametresFichiers()
{
    this->clear();
}

ParametresFichiers::ParametresFichiers(const QString& cheminFichierEtude,
        const QString& cheminFichierImageSource, const QString& cheminFichierImageConvertie,
        const QString& cheminFichierExport, const QString& cheminFichierParametres,
        const QString& cheminFichierGraphique) :
        ParametresFichiers()
{
    this->set(cheminFichierEtude, cheminFichierImageSource, cheminFichierImageConvertie,
            cheminFichierExport, cheminFichierParametres, cheminFichierGraphique);
}

ParametresFichiers::ParametresFichiers(const ParametresFichiers& parametresFichiers) :
        ParametresFichiers()
{
    this->copy(parametresFichiers);
}

ParametresFichiers::~ParametresFichiers()
{
}

ParametresFichiers& ParametresFichiers::operator=(const ParametresFichiers& parametresFichiers)
{
    this->copy(parametresFichiers);
    return *this;
}

bool ParametresFichiers::operator==(const ParametresFichiers& parametresFichiers) const
{
    return this->equals(parametresFichiers);
}

bool ParametresFichiers::operator!=(const ParametresFichiers& parametresFichiers) const
{
    return !this->equals(parametresFichiers);
}

const QString& ParametresFichiers::getCheminFichierEtude() const
{
    return this->cheminFichierEtude;
}

const QString& ParametresFichiers::getCheminFichierImageSource() const
{
    return this->cheminFichierImageSource;
}

const QString& ParametresFichiers::getCheminFichierImageConvertie() const
{
    return this->cheminFichierImageConvertie;
}

const QString& ParametresFichiers::getCheminFichierExport() const
{
    return this->cheminFichierExport;
}

const QString& ParametresFichiers::getCheminFichierParametres() const
{
    return this->cheminFichierParametres;
}

const QString& ParametresFichiers::getCheminFichierGraphique() const
{
    return this->cheminFichierGraphique;
}

void ParametresFichiers::setCheminFichierEtude(const QString& cheminFichierEtude)
{
    this->cheminFichierEtude = cheminFichierEtude;
}

void ParametresFichiers::setCheminFichierImageSource(const QString& cheminFichierImageSource)
{
    this->cheminFichierImageSource = cheminFichierImageSource;
}

void ParametresFichiers::setCheminFichierImageConvertie(const QString& cheminFichierImageConvertie)
{
    this->cheminFichierImageConvertie = cheminFichierImageConvertie;
}

void ParametresFichiers::setCheminFichierExport(const QString& cheminFichierExport)
{
    this->cheminFichierExport = cheminFichierExport;
}

void ParametresFichiers::setCheminFichierParametres(const QString& cheminFichierParametres)
{
    this->cheminFichierParametres = cheminFichierParametres;
}

void ParametresFichiers::setCheminFichierGraphique(const QString& cheminFichierGraphique)
{
    this->cheminFichierGraphique = cheminFichierGraphique;
}

void ParametresFichiers::clear()
{
    this->set(QString(), QString(), QString(), QString(), QString(), QString());
}

void ParametresFichiers::set(const QString& cheminFichierEtude,
        const QString& cheminFichierImageSource, const QString& cheminFichierImageConvertie,
        const QString& cheminFichierExport, const QString& cheminFichierParametres,
        const QString& cheminFichierGraphique)
{
    this->setCheminFichierEtude(cheminFichierEtude);
    this->setCheminFichierImageSource(cheminFichierImageSource);
    this->setCheminFichierImageConvertie(cheminFichierImageConvertie);
    this->setCheminFichierExport(cheminFichierExport);
    this->setCheminFichierParametres(cheminFichierParametres);
    this->setCheminFichierGraphique(cheminFichierGraphique);
}

void ParametresFichiers::copy(const ParametresFichiers& parametresFichiers)
{
    this->set(parametresFichiers.getCheminFichierEtude(),
            parametresFichiers.getCheminFichierImageSource(),
            parametresFichiers.getCheminFichierImageConvertie(),
            parametresFichiers.getCheminFichierExport(),
            parametresFichiers.getCheminFichierParametres(),
            parametresFichiers.getCheminFichierGraphique());
}

bool ParametresFichiers::equals(const ParametresFichiers& parametresFichiers) const
{
    if (this->getCheminFichierEtude() != parametresFichiers.getCheminFichierEtude())
        return false;
    if (this->getCheminFichierImageSource() != parametresFichiers.getCheminFichierImageSource())
        return false;
    if (this->getCheminFichierImageConvertie()
            != parametresFichiers.getCheminFichierImageConvertie())
        return false;
    if (this->getCheminFichierExport() != parametresFichiers.getCheminFichierExport())
        return false;
    if (this->getCheminFichierParametres() != parametresFichiers.getCheminFichierParametres())
        return false;
    if (this->getCheminFichierGraphique() != parametresFichiers.getCheminFichierGraphique())
        return false;
    return true;
}

void ParametresFichiers::fromString(const QString& fromString, const QChar& sep)
{
    const QStringList fromStringList = listeSousElements(fromString, sep);
    this->setCheminFichierEtude(fromStringList.at(0).mid(1, (fromStringList.at(0).count() - 2)));
    this->setCheminFichierImageSource(
            fromStringList.at(1).mid(1, (fromStringList.at(1).count() - 2)));
    this->setCheminFichierImageConvertie(
            fromStringList.at(2).mid(1, (fromStringList.at(2).count() - 2)));
    this->setCheminFichierExport(fromStringList.at(3).mid(1, (fromStringList.at(3).count() - 2)));
    this->setCheminFichierParametres(
            fromStringList.at(4).mid(1, (fromStringList.at(4).count() - 2)));
    this->setCheminFichierGraphique(
            fromStringList.at(5).mid(1, (fromStringList.at(5).count() - 2)));
}

const QString ParametresFichiers::toString(const QChar& sep) const
{
    QString toString;
    toString += "\"" + this->getCheminFichierEtude() + "\"" + sep;
    toString += "\"" + this->getCheminFichierImageSource() + "\"" + sep;
    toString += "\"" + this->getCheminFichierImageConvertie() + "\"" + sep;
    toString += "\"" + this->getCheminFichierExport() + "\"" + sep;
    toString += "\"" + this->getCheminFichierParametres() + "\"" + sep;
    toString += "\"" + this->getCheminFichierGraphique() + "\"";
    return toString;
}
