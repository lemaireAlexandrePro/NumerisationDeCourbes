//==============================================================================
// Name        : Repere.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Source file of the Repere class
//==============================================================================

#include "Repere.h"
#include "Outils.h"
#include <QStringList>

Repere::Repere()
{
    this->clear();
}

Repere::Repere(const Point& pointX0, const Point& pointX1, const Point& pointY0,
        const Point& pointY1) :
        Repere()
{
    this->set(pointX0, pointX1, pointY0, pointY1);
}

Repere::Repere(const Repere& repere) :
        Repere()
{
    this->copy(repere);
}

Repere::~Repere()
{
}

Repere& Repere::operator=(const Repere& repere)
{
    this->copy(repere);
    return *this;
}

bool Repere::operator==(const Repere& repere) const
{
    return this->equals(repere);
}

bool Repere::operator!=(const Repere& repere) const
{
    return !this->equals(repere);
}

const Point& Repere::getPointX0() const
{
    return this->pointX0;
}

const Point& Repere::getPointX1() const
{
    return this->pointX1;
}

const Point& Repere::getPointY0() const
{
    return this->pointY0;
}

const Point& Repere::getPointY1() const
{
    return this->pointY1;
}

void Repere::setPointX0(const Point& pointX0)
{
    this->pointX0 = pointX0;
}

void Repere::setPointX1(const Point& pointX1)
{
    this->pointX1 = pointX1;
}

void Repere::setPointY0(const Point& pointY0)
{
    this->pointY0 = pointY0;
}

void Repere::setPointY1(const Point& pointY1)
{
    this->pointY1 = pointY1;
}

void Repere::clear()
{
    this->set(Point(0, 0, 0.0, 0.0, Point::REPERE), Point(0, 0, 0.0, 0.0, Point::REPERE),
            Point(0, 0, 0.0, 0.0, Point::REPERE), Point(0, 0, 0.0, 0.0, Point::REPERE));
}

void Repere::set(const Point& pointX0, const Point& pointX1, const Point& pointY0,
        const Point& pointY1)
{
    this->setPointX0(pointX0);
    this->setPointX1(pointX1);
    this->setPointY0(pointY0);
    this->setPointY1(pointY1);
}

void Repere::copy(const Repere& repere)
{
    this->set(repere.getPointX0(), repere.getPointX1(), repere.getPointY0(), repere.getPointY1());
}

bool Repere::equals(const Repere& repere) const
{
    if (!this->getPointX0().equals(repere.getPointX0()))
        return false;
    if (!this->getPointX1().equals(repere.getPointX1()))
        return false;
    if (!this->getPointY0().equals(repere.getPointY0()))
        return false;
    if (!this->getPointY1().equals(repere.getPointY1()))
        return false;
    return true;
}

void Repere::fromString(const QString& fromString, const QChar& sep)
{
    const QStringList fromStringList = listeSousElements(fromString, sep);
    Point pointX0 = this->getPointX0();
    Point pointX1 = this->getPointX1();
    Point pointY0 = this->getPointY0();
    Point pointY1 = this->getPointY1();
    pointX0.fromString(fromStringList.at(0), sep);
    pointX1.fromString(fromStringList.at(1), sep);
    pointY0.fromString(fromStringList.at(2), sep);
    pointY1.fromString(fromStringList.at(3), sep);
    this->setPointX0(pointX0);
    this->setPointX1(pointX1);
    this->setPointY0(pointY0);
    this->setPointY1(pointY1);
}

const QString Repere::toString(const QChar& sep) const
{
    QString toString;
    toString += QString("(%1)").arg(this->getPointX0().toString(sep)) + sep;
    toString += QString("(%1)").arg(this->getPointX1().toString(sep)) + sep;
    toString += QString("(%1)").arg(this->getPointY0().toString(sep)) + sep;
    toString += QString("(%1)").arg(this->getPointY1().toString(sep));
    return toString;
}

void Repere::pixelVersReel(Point& point) const
{
    const int pointPixelX = point.getPointPixelX();
    const int pointPixelY = point.getPointPixelY();
    double pointReelX = 0.0;
    double pointReelY = 0.0;
    this->pixelVersReel(pointPixelX, pointPixelY, pointReelX, pointReelY);
    point.setPointReelX(pointReelX);
    point.setPointReelY(pointReelY);
}

void Repere::pixelVersReel(const int& pointPixelX, const int& pointPixelY, double& pointReelX,
        double& pointReelY) const
{
    const Point& pointX0 = this->getPointX0();
    const Point& pointX1 = this->getPointX1();
    const Point& pointY0 = this->getPointY0();
    const Point& pointY1 = this->getPointY1();

    const double x0px = pointX0.getPointPixelX();
    const double x0py = pointX0.getPointPixelY();
    const double x1px = pointX1.getPointPixelX();
    const double x1py = pointX1.getPointPixelY();
    const double y0px = pointY0.getPointPixelX();
    const double y0py = pointY0.getPointPixelY();
    const double y1px = pointY1.getPointPixelX();
    const double y1py = pointY1.getPointPixelY();

    const double x0rx = pointX0.getPointReelX();
    const double x1rx = pointX1.getPointReelX();
    const double y0ry = pointY0.getPointReelY();
    const double y1ry = pointY1.getPointReelY();

    const double x21 = x1px - x0px;
    const double y21 = x1py - x0py;
    const double x43 = y1px - y0px;
    const double y43 = y1py - y0py;

    const double penteX = ((x0px - pointPixelX) - (x0py - pointPixelY) * (x43 / y43))
            / (x21 - y21 * (x43 / y43));
    const double penteY = ((y0py - pointPixelY) - (y0px - pointPixelX) * (y21 / x21))
            / (y43 - x43 * (y21 / x21));

    pointReelX = -penteX * (x1rx - x0rx) + x0rx;
    pointReelY = -penteY * (y1ry - y0ry) + y0ry;
}
