//==============================================================================
// Name        : ParametresGraphique.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Source file of the ParametresGraphique class
//==============================================================================

#include "ParametresGraphique.h"
#include "Outils.h"
#include <QStringList>

ParametresGraphique::ParametresGraphique()
{
    this->clear();
}

ParametresGraphique::ParametresGraphique(const ParametresAxe& parametresAxeHorizontal,
        const ParametresAxe& parametresAxeVertical) :
        ParametresGraphique()
{
    this->set(parametresAxeHorizontal, parametresAxeVertical);
}

ParametresGraphique::ParametresGraphique(const ParametresGraphique& parametresGraphique) :
        ParametresGraphique()
{
    this->copy(parametresGraphique);
}

ParametresGraphique::~ParametresGraphique()
{
}

ParametresGraphique& ParametresGraphique::operator=(const ParametresGraphique& parametresGraphique)
{
    this->copy(parametresGraphique);
    return *this;
}

bool ParametresGraphique::operator==(const ParametresGraphique& parametresGraphique) const
{
    return this->equals(parametresGraphique);
}

bool ParametresGraphique::operator!=(const ParametresGraphique& parametresGraphique) const
{
    return !this->equals(parametresGraphique);
}

const ParametresAxe& ParametresGraphique::getParametresAxeHorizontal() const
{
    return this->parametresAxeHorizontal;
}

const ParametresAxe& ParametresGraphique::getParametresAxeVertical() const
{
    return this->parametresAxeVertical;
}

void ParametresGraphique::setParametresAxeHorizontal(const ParametresAxe& parametresAxeHorizontal)
{
    this->parametresAxeHorizontal = parametresAxeHorizontal;
}

void ParametresGraphique::setParametresAxeVertical(const ParametresAxe& parametresAxeVertical)
{
    this->parametresAxeVertical = parametresAxeVertical;
}

void ParametresGraphique::clear()
{
    this->set(ParametresAxe(), ParametresAxe());
}

void ParametresGraphique::set(const ParametresAxe& parametresAxeHorizontal,
        const ParametresAxe& parametresAxeVertical)
{
    this->setParametresAxeHorizontal(parametresAxeHorizontal);
    this->setParametresAxeVertical(parametresAxeVertical);
}

void ParametresGraphique::copy(const ParametresGraphique& parametresGraphique)
{
    this->set(parametresGraphique.getParametresAxeHorizontal(),
            parametresGraphique.getParametresAxeVertical());
}

bool ParametresGraphique::equals(const ParametresGraphique& parametresGraphique) const
{
    if (!this->getParametresAxeHorizontal().equals(
            parametresGraphique.getParametresAxeHorizontal()))
        return false;
    if (!this->getParametresAxeVertical().equals(parametresGraphique.getParametresAxeVertical()))
        return false;
    return true;
}

void ParametresGraphique::fromString(const QString& fromString, const QChar& sep)
{
    const QStringList fromStringList = listeSousElements(fromString, sep);
    ParametresAxe parametresAxeHorizontal = this->getParametresAxeHorizontal();
    ParametresAxe parametresAxeVertical = this->getParametresAxeVertical();
    parametresAxeHorizontal.fromString(fromStringList.at(0), sep);
    parametresAxeVertical.fromString(fromStringList.at(1), sep);
    this->setParametresAxeHorizontal(parametresAxeHorizontal);
    this->setParametresAxeVertical(parametresAxeVertical);
}

const QString ParametresGraphique::toString(const QChar& sep) const
{
    QString toString;
    toString += QString("(%1)").arg(this->getParametresAxeHorizontal().toString(sep)) + sep;
    toString += QString("(%1)").arg(this->getParametresAxeVertical().toString(sep));
    return toString;
}
