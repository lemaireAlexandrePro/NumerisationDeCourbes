//==============================================================================
// Name        : ParametresTrait.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Source file of the ParametresTrait class
//==============================================================================

#include "ParametresTrait.h"
#include "Outils.h"
#include <QColor>
#include <QStringList>

const int ParametresTrait::styleTraitDefaut = LIGNE;
const int ParametresTrait::epaisseurTraitDefaut = 2;
const QRgb ParametresTrait::couleurTraitDefaut = 0xFF000000; // QColor(Qt::black).rgb()
const QRgb ParametresTrait::couleurTraitAxeDefaut = 0xFFFF0000; // QColor(Qt::red).rgb()
const QRgb ParametresTrait::couleurTraitCourbeDefaut = 0xFF0000FF; // QColor(Qt::blue).rgb()
// Note : Initialisations des valeurs par défaut des paramètres d'un trait avec les valeurs
//        hexadécimales correspondantes afin d'en disposer pour les initialisations des valeurs par
//        défaut des paramètres d'affichage.

const QMap<int, QString> ParametresTrait::stylesTraitsTexte = QMap<int, QString>(
        std::map<int, QString> { { LIGNE, QString::fromUtf8("Ligne") }, { TIRETS, QString::fromUtf8(
                "Tirets") }, { POINTILLES, QString::fromUtf8("Pointillés") } });

ParametresTrait::ParametresTrait() :
        styleTrait(styleTraitDefaut), epaisseurTrait(epaisseurTraitDefaut),
                couleurTrait(couleurTraitDefaut)
{
    this->clear();
}

ParametresTrait::ParametresTrait(const int& styleTrait, const int& epaisseurTrait,
        const QRgb& couleurTrait) :
        ParametresTrait()
{
    this->set(styleTrait, epaisseurTrait, couleurTrait);
}

ParametresTrait::ParametresTrait(const ParametresTrait& parametresTrait) :
        ParametresTrait()
{
    this->copy(parametresTrait);
}

ParametresTrait::~ParametresTrait()
{
}

ParametresTrait& ParametresTrait::operator=(const ParametresTrait& parametresTrait)
{
    this->copy(parametresTrait);
    return *this;
}

bool ParametresTrait::operator==(const ParametresTrait& parametresTrait) const
{
    return this->equals(parametresTrait);
}

bool ParametresTrait::operator!=(const ParametresTrait& parametresTrait) const
{
    return !this->equals(parametresTrait);
}

const int& ParametresTrait::getStyleTrait() const
{
    return this->styleTrait;
}

const int& ParametresTrait::getEpaisseurTrait() const
{
    return this->epaisseurTrait;
}

const QRgb& ParametresTrait::getCouleurTrait() const
{
    return this->couleurTrait;
}

void ParametresTrait::setStyleTrait(const int& styleTrait)
{
    this->styleTrait = styleTrait;
}

void ParametresTrait::setEpaisseurTrait(const int& epaisseurTrait)
{
    this->epaisseurTrait = epaisseurTrait;
}

void ParametresTrait::setCouleurTrait(const QRgb& couleurTrait)
{
    this->couleurTrait = couleurTrait;
}

void ParametresTrait::clear()
{
    this->set(styleTraitDefaut, epaisseurTraitDefaut, couleurTraitDefaut);
}

void ParametresTrait::set(const int& styleTrait, const int& epaisseurTrait,
        const QRgb& couleurTrait)
{
    this->setStyleTrait(styleTrait);
    this->setEpaisseurTrait(epaisseurTrait);
    this->setCouleurTrait(couleurTrait);
}

void ParametresTrait::copy(const ParametresTrait& parametresTrait)
{
    this->set(parametresTrait.getStyleTrait(), parametresTrait.getEpaisseurTrait(),
            parametresTrait.getCouleurTrait());
}

bool ParametresTrait::equals(const ParametresTrait& parametresTrait) const
{
    if (this->getStyleTrait() != parametresTrait.getStyleTrait())
        return false;
    if (this->getEpaisseurTrait() != parametresTrait.getEpaisseurTrait())
        return false;
    if (this->getCouleurTrait() != parametresTrait.getCouleurTrait())
        return false;
    return true;
}

void ParametresTrait::fromString(const QString& fromString, const QChar& sep)
{
    const QStringList fromStringList = listeSousElements(fromString, sep);
    this->setStyleTrait(fromStringList.at(0).toInt());
    this->setEpaisseurTrait(fromStringList.at(1).toInt());
    this->setCouleurTrait(QColor(fromStringList.at(2)).rgb());
}

const QString ParametresTrait::toString(const QChar& sep) const
{
    QString toString;
    toString += QString::number(this->getStyleTrait()) + sep;
    toString += QString::number(this->getEpaisseurTrait()) + sep;
    toString += QColor(this->getCouleurTrait()).name();
    return toString;
}

const QString ParametresTrait::getStyleTraitTexte() const
{
    return stylesTraitsTexte.value(this->getStyleTrait());
}

void ParametresTrait::setStyleTraitTexte(const QString& styleTraitTexte)
{
    this->setStyleTrait(stylesTraitsTexte.key(styleTraitTexte));
}
