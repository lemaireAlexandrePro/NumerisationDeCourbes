//==============================================================================
// Name        : ParametresPoint.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Source file of the ParametresPoint class
//==============================================================================

#include "ParametresPoint.h"
#include "Outils.h"
#include <QColor>
#include <QStringList>

const int ParametresPoint::stylePointDefaut = CARRE;
const int ParametresPoint::epaisseurPointDefaut = 4;
const QRgb ParametresPoint::couleurPointDefaut = 0xFF000000; // QColor(Qt::black).rgb()
const QRgb ParametresPoint::couleurPointAxeDefaut = 0xFFFF0000; // QColor(Qt::red).rgb()
const QRgb ParametresPoint::couleurPointCourbeDefaut = 0xFF0000FF; // QColor(Qt::blue).rgb()
const QRgb ParametresPoint::couleurPointManuelDefaut = 0xFF00FF00; // QColor(Qt::green).rgb()
// Note : Initialisations des valeurs par défaut des paramètres d'un point avec les valeurs
//        hexadécimales correspondantes afin d'en disposer pour les initialisations des valeurs par
//        défaut des paramètres d'affichage.

const QMap<int, QString> ParametresPoint::stylesPointsTexte = QMap<int, QString>(
        std::map<int, QString> { { CARRE, QString::fromUtf8("Carré") }, { CERCLE, QString::fromUtf8(
                "Cercle") } });

ParametresPoint::ParametresPoint() :
        stylePoint(stylePointDefaut), epaisseurPoint(epaisseurPointDefaut),
                couleurPoint(couleurPointDefaut)
{
    this->clear();
}

ParametresPoint::ParametresPoint(const int& stylePoint, const int& epaisseurPoint,
        const QRgb& couleurPoint) :
        ParametresPoint()
{
    this->set(stylePoint, epaisseurPoint, couleurPoint);
}

ParametresPoint::ParametresPoint(const ParametresPoint& parametresPoint) :
        ParametresPoint()
{
    this->copy(parametresPoint);
}

ParametresPoint::~ParametresPoint()
{
}

ParametresPoint& ParametresPoint::operator=(const ParametresPoint& parametresPoint)
{
    this->copy(parametresPoint);
    return *this;
}

bool ParametresPoint::operator==(const ParametresPoint& parametresPoint) const
{
    return this->equals(parametresPoint);
}

bool ParametresPoint::operator!=(const ParametresPoint& parametresPoint) const
{
    return !this->equals(parametresPoint);
}

const int& ParametresPoint::getStylePoint() const
{
    return this->stylePoint;
}

const int& ParametresPoint::getEpaisseurPoint() const
{
    return this->epaisseurPoint;
}

const QRgb& ParametresPoint::getCouleurPoint() const
{
    return this->couleurPoint;
}

void ParametresPoint::setStylePoint(const int& stylePoint)
{
    this->stylePoint = stylePoint;
}

void ParametresPoint::setEpaisseurPoint(const int& epaisseurPoint)
{
    this->epaisseurPoint = epaisseurPoint;
}

void ParametresPoint::setCouleurPoint(const QRgb& couleurPoint)
{
    this->couleurPoint = couleurPoint;
}

void ParametresPoint::clear()
{
    this->set(stylePointDefaut, epaisseurPointDefaut, couleurPointDefaut);
}

void ParametresPoint::set(const int& stylePoint, const int& epaisseurPoint,
        const QRgb& couleurPoint)
{
    this->setStylePoint(stylePoint);
    this->setEpaisseurPoint(epaisseurPoint);
    this->setCouleurPoint(couleurPoint);
}

void ParametresPoint::copy(const ParametresPoint& parametresPoint)
{
    this->set(parametresPoint.getStylePoint(), parametresPoint.getEpaisseurPoint(),
            parametresPoint.getCouleurPoint());
}

bool ParametresPoint::equals(const ParametresPoint& parametresPoint) const
{
    if (this->getStylePoint() != parametresPoint.getStylePoint())
        return false;
    if (this->getEpaisseurPoint() != parametresPoint.getEpaisseurPoint())
        return false;
    if (this->getCouleurPoint() != parametresPoint.getCouleurPoint())
        return false;
    return true;
}

void ParametresPoint::fromString(const QString& fromString, const QChar& sep)
{
    const QStringList fromStringList = listeSousElements(fromString, sep);
    this->setStylePoint(fromStringList.at(0).toInt());
    this->setEpaisseurPoint(fromStringList.at(1).toInt());
    this->setCouleurPoint(QColor(fromStringList.at(2)).rgb());
}

const QString ParametresPoint::toString(const QChar& sep) const
{
    QString toString;
    toString += QString::number(this->getStylePoint()) + sep;
    toString += QString::number(this->getEpaisseurPoint()) + sep;
    toString += QColor(this->getCouleurPoint()).name();
    return toString;
}

const QString ParametresPoint::getStylePointTexte() const
{
    return stylesPointsTexte.value(this->getStylePoint());
}

void ParametresPoint::setStylePointTexte(const QString& stylePointTexte)
{
    this->setStylePoint(stylesPointsTexte.key(stylePointTexte));
}
