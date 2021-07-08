//==============================================================================
// Name        : ParametresRecherche.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Source file of the ParametresRecherche class
//==============================================================================

#include "ParametresRecherche.h"
#include "Outils.h"
#include <cmath>
#include <QStringList>

const int ParametresRecherche::seuilToleranceNiveauxDeGrisDefaut = 32;
const int ParametresRecherche::seuilToleranceTeintesSatureesDefaut = 60;
const bool ParametresRecherche::selectionValeursMoyennesDefaut = true;
const bool ParametresRecherche::selectionValeursMinimalesDefaut = false;
const bool ParametresRecherche::selectionValeursMaximalesDefaut = false;

ParametresRecherche::ParametresRecherche() :
        seuilToleranceNiveauxDeGris(seuilToleranceNiveauxDeGrisDefaut),
                seuilToleranceTeintesSaturees(seuilToleranceTeintesSatureesDefaut),
                selectionValeursMoyennes(selectionValeursMoyennesDefaut),
                selectionValeursMinimales(selectionValeursMinimalesDefaut),
                selectionValeursMaximales(selectionValeursMaximalesDefaut)
{
    this->clear();
}

ParametresRecherche::ParametresRecherche(const int& seuilToleranceNiveauxDeGris,
        const int& seuilToleranceTeintesSaturees, const bool& selectionValeursMoyennes,
        const bool& selectionValeursMinimales, const bool& selectionValeursMaximales) :
        ParametresRecherche()
{
    this->set(seuilToleranceNiveauxDeGris, seuilToleranceTeintesSaturees, selectionValeursMoyennes,
            selectionValeursMinimales, selectionValeursMaximales);
}

ParametresRecherche::ParametresRecherche(const ParametresRecherche& parametresRecherche) :
        ParametresRecherche()
{
    this->copy(parametresRecherche);
}

ParametresRecherche::~ParametresRecherche()
{
}

ParametresRecherche& ParametresRecherche::operator=(const ParametresRecherche& parametresRecherche)
{
    this->copy(parametresRecherche);
    return *this;
}

bool ParametresRecherche::operator==(const ParametresRecherche& parametresRecherche) const
{
    return this->equals(parametresRecherche);
}

bool ParametresRecherche::operator!=(const ParametresRecherche& parametresRecherche) const
{
    return !this->equals(parametresRecherche);
}

const int& ParametresRecherche::getSeuilToleranceNiveauxDeGris() const
{
    return this->seuilToleranceNiveauxDeGris;
}

const int& ParametresRecherche::getSeuilToleranceTeintesSaturees() const
{
    return this->seuilToleranceTeintesSaturees;
}

const bool& ParametresRecherche::getSelectionValeursMoyennes() const
{
    return this->selectionValeursMoyennes;
}

const bool& ParametresRecherche::getSelectionValeursMinimales() const
{
    return this->selectionValeursMinimales;
}

const bool& ParametresRecherche::getSelectionValeursMaximales() const
{
    return this->selectionValeursMaximales;
}

void ParametresRecherche::setSeuilToleranceNiveauxDeGris(const int& seuilToleranceNiveauxDeGris)
{
    this->seuilToleranceNiveauxDeGris = seuilToleranceNiveauxDeGris;
}

void ParametresRecherche::setSeuilToleranceTeintesSaturees(const int& seuilToleranceTeintesSaturees)
{
    this->seuilToleranceTeintesSaturees = seuilToleranceTeintesSaturees;
}

void ParametresRecherche::setSelectionValeursMoyennes(const bool& selectionValeursMoyennes)
{
    this->selectionValeursMoyennes = selectionValeursMoyennes;
}

void ParametresRecherche::setSelectionValeursMinimales(const bool& selectionValeursMinimales)
{
    this->selectionValeursMinimales = selectionValeursMinimales;
}

void ParametresRecherche::setSelectionValeursMaximales(const bool& selectionValeursMaximales)
{
    this->selectionValeursMaximales = selectionValeursMaximales;
}

void ParametresRecherche::clear()
{
    this->set(seuilToleranceNiveauxDeGrisDefaut, seuilToleranceTeintesSatureesDefaut,
            selectionValeursMoyennesDefaut, selectionValeursMinimalesDefaut,
            selectionValeursMaximalesDefaut);
}

void ParametresRecherche::set(const int& seuilToleranceNiveauxDeGris,
        const int& seuilToleranceTeintesSaturees, const bool& selectionValeursMoyennes,
        const bool& selectionValeursMinimales, const bool& selectionValeursMaximales)
{
    this->setSeuilToleranceNiveauxDeGris(seuilToleranceNiveauxDeGris);
    this->setSeuilToleranceTeintesSaturees(seuilToleranceTeintesSaturees);
    this->setSelectionValeursMoyennes(selectionValeursMoyennes);
    this->setSelectionValeursMinimales(selectionValeursMinimales);
    this->setSelectionValeursMaximales(selectionValeursMaximales);
}

void ParametresRecherche::copy(const ParametresRecherche& parametresRecherche)
{
    this->set(parametresRecherche.getSeuilToleranceNiveauxDeGris(),
            parametresRecherche.getSeuilToleranceTeintesSaturees(),
            parametresRecherche.getSelectionValeursMoyennes(),
            parametresRecherche.getSelectionValeursMinimales(),
            parametresRecherche.getSelectionValeursMaximales());
}

bool ParametresRecherche::equals(const ParametresRecherche& parametresRecherche) const
{
    if (this->getSeuilToleranceNiveauxDeGris()
            != parametresRecherche.getSeuilToleranceNiveauxDeGris())
        return false;
    if (this->getSeuilToleranceTeintesSaturees()
            != parametresRecherche.getSeuilToleranceTeintesSaturees())
        return false;
    if (this->getSelectionValeursMoyennes() != parametresRecherche.getSelectionValeursMoyennes())
        return false;
    if (this->getSelectionValeursMinimales() != parametresRecherche.getSelectionValeursMinimales())
        return false;
    if (this->getSelectionValeursMaximales() != parametresRecherche.getSelectionValeursMaximales())
        return false;
    return true;
}

void ParametresRecherche::fromString(const QString& fromString, const QChar& sep)
{
    const QStringList fromStringList = listeSousElements(fromString, sep);
    this->setSeuilToleranceNiveauxDeGris(fromStringList.at(0).toInt());
    this->setSeuilToleranceTeintesSaturees(fromStringList.at(1).toInt());
    this->setSelectionValeursMoyennes(static_cast<bool>(fromStringList.at(2).toInt()));
    this->setSelectionValeursMinimales(static_cast<bool>(fromStringList.at(3).toInt()));
    this->setSelectionValeursMaximales(static_cast<bool>(fromStringList.at(4).toInt()));
}

const QString ParametresRecherche::toString(const QChar& sep) const
{
    QString toString;
    toString += QString::number(this->getSeuilToleranceNiveauxDeGris()) + sep;
    toString += QString::number(this->getSeuilToleranceTeintesSaturees()) + sep;
    toString += QString::number(this->getSelectionValeursMoyennes()) + sep;
    toString += QString::number(this->getSelectionValeursMinimales()) + sep;
    toString += QString::number(this->getSelectionValeursMaximales());
    return toString;
}

double ParametresRecherche::getSeuilToleranceNiveauxDeGrisFacteur() const
{
    return (this->getSeuilToleranceNiveauxDeGris() / 255.0);
}

double ParametresRecherche::getSeuilToleranceTeintesSatureesFacteur() const
{
    return (this->getSeuilToleranceTeintesSaturees() / 360.0);
}

void ParametresRecherche::setSeuilToleranceNiveauxDeGrisFacteur(
        const double& seuilToleranceNiveauxDeGrisFacteur)
{
    this->setSeuilToleranceNiveauxDeGris(
            static_cast<int>(round(seuilToleranceNiveauxDeGrisFacteur * 255.0)));
}

void ParametresRecherche::setSeuilToleranceTeintesSatureesFacteur(
        const double& seuilToleranceTeintesSatureesFacteur)
{
    this->setSeuilToleranceTeintesSaturees(
            static_cast<int>(round(seuilToleranceTeintesSatureesFacteur * 360.0)));
}
