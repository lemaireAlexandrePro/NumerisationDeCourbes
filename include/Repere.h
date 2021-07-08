//==============================================================================
// Name        : Repere.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Header file of the Repere class
//==============================================================================

#ifndef REPERE_H
#define REPERE_H

#include "Point.h"
#include <QChar>
#include <QString>

class Repere
{
public:
    // Constructeurs et destructeurs
    Repere();
    Repere(const Point& pointX0, const Point& pointX1, const Point& pointY0, const Point& pointY1);
    Repere(const Repere& repere);
    virtual ~Repere();

    // Opérateurs
    Repere& operator=(const Repere& repere);
    bool operator==(const Repere& repere) const;
    bool operator!=(const Repere& repere) const;

    // Getters
    const Point& getPointX0() const;
    const Point& getPointX1() const;
    const Point& getPointY0() const;
    const Point& getPointY1() const;

    // Setters
    void setPointX0(const Point& pointX0);
    void setPointX1(const Point& pointX1);
    void setPointY0(const Point& pointY0);
    void setPointY1(const Point& pointY1);

    // Méthodes génériques
    void clear();
    void set(const Point& pointX0, const Point& pointX1, const Point& pointY0,
            const Point& pointY1);
    void copy(const Repere& repere);
    bool equals(const Repere& repere) const;
    void fromString(const QString& fromString, const QChar& sep);
    const QString toString(const QChar& sep) const;

    // Méthodes spécifiques
    void pixelVersReel(Point& point) const;
    void pixelVersReel(const int& pointPixelX, const int& pointPixelY, double& pointReelX,
            double& pointReelY) const;

private:
    // Attributs de classe
    Point pointX0;
    Point pointX1;
    Point pointY0;
    Point pointY1;
};

#endif /* REPERE_H */
