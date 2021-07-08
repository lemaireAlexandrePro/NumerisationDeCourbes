//==============================================================================
// Name        : ParametresAxe.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Source file of the ParametresAxe class
//==============================================================================

#include "ParametresAxe.h"
#include "Outils.h"
#include <QStringList>
#ifdef ENABLE_QWT
#include <qwt_scale_engine.h>
#endif

const double ParametresAxe::borneInferieureDefaut = 0.0;
const double ParametresAxe::borneSuperieureDefaut = 0.0;
const double ParametresAxe::pasPrincipalDefaut = 0.0;
const double ParametresAxe::pasSecondaireDefaut = 0.0;
const bool ParametresAxe::grillePrincipaleDefaut = true;
const bool ParametresAxe::grilleSecondaireDefaut = false;
const int ParametresAxe::nombreElementsPasPrincipalDefaut = 5;
const int ParametresAxe::nombreElementsPasSecondaireDefaut = 5;

ParametresAxe::ParametresAxe() :
        borneInferieure(borneInferieureDefaut), borneSuperieure(borneSuperieureDefaut),
                pasPrincipal(pasPrincipalDefaut), pasSecondaire(pasSecondaireDefaut),
                grillePrincipale(grillePrincipaleDefaut), grilleSecondaire(grilleSecondaireDefaut)
{
    this->clear();
}

ParametresAxe::ParametresAxe(const double& borneInferieure, const double& borneSuperieure,
        const double& pasPrincipal, const double& pasSecondaire, const bool& grillePrincipale,
        const bool& grilleSecondaire) :
        ParametresAxe()
{
    this->set(borneInferieure, borneSuperieure, pasPrincipal, pasSecondaire, grillePrincipale,
            grilleSecondaire);
}

ParametresAxe::ParametresAxe(const ParametresAxe& parametresAxe) :
        ParametresAxe()
{
    this->copy(parametresAxe);
}

ParametresAxe::~ParametresAxe()
{
}

ParametresAxe& ParametresAxe::operator=(const ParametresAxe& parametresAxe)
{
    this->copy(parametresAxe);
    return *this;
}

bool ParametresAxe::operator==(const ParametresAxe& parametresAxe) const
{
    return this->equals(parametresAxe);
}

bool ParametresAxe::operator!=(const ParametresAxe& parametresAxe) const
{
    return !this->equals(parametresAxe);
}

const double& ParametresAxe::getBorneInferieure() const
{
    return this->borneInferieure;
}

const double& ParametresAxe::getBorneSuperieure() const
{
    return this->borneSuperieure;
}

const double& ParametresAxe::getPasPrincipal() const
{
    return this->pasPrincipal;
}

const double& ParametresAxe::getPasSecondaire() const
{
    return this->pasSecondaire;
}

const bool& ParametresAxe::getGrillePrincipale() const
{
    return this->grillePrincipale;
}

const bool& ParametresAxe::getGrilleSecondaire() const
{
    return this->grilleSecondaire;
}

void ParametresAxe::setBorneInferieure(const double& borneInferieure)
{
    this->borneInferieure = borneInferieure;
}

void ParametresAxe::setBorneSuperieure(const double& borneSuperieure)
{
    this->borneSuperieure = borneSuperieure;
}

void ParametresAxe::setPasPrincipal(const double& pasPrincipal)
{
    this->pasPrincipal = pasPrincipal;
}

void ParametresAxe::setPasSecondaire(const double& pasSecondaire)
{
    this->pasSecondaire = pasSecondaire;
}

void ParametresAxe::setGrillePrincipale(const bool& grillePrincipale)
{
    this->grillePrincipale = grillePrincipale;
}

void ParametresAxe::setGrilleSecondaire(const bool& grilleSecondaire)
{
    this->grilleSecondaire = grilleSecondaire;
}

void ParametresAxe::clear()
{
    this->set(borneInferieureDefaut, borneSuperieureDefaut, pasPrincipalDefaut, pasSecondaireDefaut,
            grillePrincipaleDefaut, grilleSecondaireDefaut);
}

void ParametresAxe::set(const double& borneInferieure, const double& borneSuperieure,
        const double& pasPrincipal, const double& pasSecondaire, const bool& grillePrincipale,
        const bool& grilleSecondaire)
{
    this->setBorneInferieure(borneInferieure);
    this->setBorneSuperieure(borneSuperieure);
    this->setPasPrincipal(pasPrincipal);
    this->setPasSecondaire(pasSecondaire);
    this->setGrillePrincipale(grillePrincipale);
    this->setGrilleSecondaire(grilleSecondaire);
}

void ParametresAxe::copy(const ParametresAxe& parametresAxe)
{
    this->set(parametresAxe.getBorneInferieure(), parametresAxe.getBorneSuperieure(),
            parametresAxe.getPasPrincipal(), parametresAxe.getPasSecondaire(),
            parametresAxe.getGrillePrincipale(), parametresAxe.getGrilleSecondaire());
}

bool ParametresAxe::equals(const ParametresAxe& parametresAxe) const
{
    if (this->getBorneInferieure() != parametresAxe.getBorneInferieure())
        return false;
    if (this->getBorneSuperieure() != parametresAxe.getBorneSuperieure())
        return false;
    if (this->getPasPrincipal() != parametresAxe.getPasPrincipal())
        return false;
    if (this->getPasSecondaire() != parametresAxe.getPasSecondaire())
        return false;
    if (this->getGrillePrincipale() != parametresAxe.getGrillePrincipale())
        return false;
    if (this->getGrilleSecondaire() != parametresAxe.getGrilleSecondaire())
        return false;
    return true;
}

void ParametresAxe::fromString(const QString& fromString, const QChar& sep)
{
    const QStringList fromStringList = listeSousElements(fromString, sep);
    this->setBorneInferieure(fromStringList.at(0).toDouble());
    this->setBorneSuperieure(fromStringList.at(1).toDouble());
    this->setPasPrincipal(fromStringList.at(2).toDouble());
    this->setPasSecondaire(fromStringList.at(3).toDouble());
    this->setPasSecondaire(static_cast<bool>(fromStringList.at(4).toInt()));
    this->setPasSecondaire(static_cast<bool>(fromStringList.at(5).toInt()));
}

const QString ParametresAxe::toString(const QChar& sep) const
{
    QString toString;
    toString += QString::number(this->getBorneInferieure()) + sep;
    toString += QString::number(this->getBorneSuperieure()) + sep;
    toString += QString::number(this->getPasPrincipal()) + sep;
    toString += QString::number(this->getPasSecondaire()) + sep;
    toString += QString::number(this->getGrillePrincipale()) + sep;
    toString += QString::number(this->getGrilleSecondaire());
    return toString;
}

void ParametresAxe::ajuster()
{
    this->ajusterBornes();
    this->ajusterPasPrincipal();
    this->ajusterPasSecondaire();
}

void ParametresAxe::ajusterBornes()
{
#ifdef ENABLE_QWT
    double borneInferieure = this->getBorneInferieure();
    double borneSuperieure = this->getBorneSuperieure();
    double pasPrincipal = this->getPasPrincipal();
    QwtLinearScaleEngine echelle;
    echelle.autoScale(nombreElementsPasPrincipalDefaut, borneInferieure, borneSuperieure,
            pasPrincipal);
    this->setBorneInferieure(borneInferieure);
    this->setBorneSuperieure(borneSuperieure);
#endif
}

void ParametresAxe::ajusterPasPrincipal()
{
#ifdef ENABLE_QWT
    double borneInferieure = this->getBorneInferieure();
    double borneSuperieure = this->getBorneSuperieure();
    double pasPrincipal = this->getPasPrincipal();
    QwtLinearScaleEngine echelle;
    echelle.autoScale(nombreElementsPasPrincipalDefaut, borneInferieure, borneSuperieure,
            pasPrincipal);
    this->setPasPrincipal(pasPrincipal);
#endif
}

void ParametresAxe::ajusterPasSecondaire()
{
#ifdef ENABLE_QWT
    double borneInferieure = this->getBorneInferieure();
    double pasPrincipal = this->getPasPrincipal();
    double pasSecondaire = this->getPasSecondaire();
    double elementIntermediaire = borneInferieure + pasPrincipal;
    QwtLinearScaleEngine echelle;
    echelle.autoScale(nombreElementsPasSecondaireDefaut, borneInferieure, elementIntermediaire,
            pasSecondaire);
    this->setPasSecondaire(pasSecondaire);
#endif
}
