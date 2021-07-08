//==============================================================================
// Name        : Point.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Header file of the Point class
//==============================================================================

#ifndef POINT_H
#define POINT_H

#include <QChar>
#include <QList>
#include <QMap>
#include <QPoint>
#include <QPointF>
#include <QString>

class Point
{
public:
    // Constructeurs et destructeurs
    Point();
    Point(const QPoint& pointPixel, const QPointF& pointReel, const int& typePoint);
    Point(const int& pointPixelX, const int& pointPixelY, const double& pointReelX,
            const double& pointReelY, const int& typePoint);
    Point(const Point& point);
    virtual ~Point();

    // Opérateurs
    Point& operator=(const Point& point);
    bool operator==(const Point& point) const;
    bool operator!=(const Point& point) const;

    // Getters
    const QPoint& getPointPixel() const;
    const QPointF& getPointReel() const;
    const int& getTypePoint() const;
    int getPointPixelX() const;
    int getPointPixelY() const;
    double getPointReelX() const;
    double getPointReelY() const;

    // Setters
    void setPointPixel(const QPoint& pointPixel);
    void setPointReel(const QPointF& pointReel);
    void setTypePoint(const int& typePoint);
    void setPointPixelX(const int& pointPixelX);
    void setPointPixelY(const int& pointPixelY);
    void setPointReelX(const double& pointReelX);
    void setPointReelY(const double& pointReelY);

    // Méthodes génériques
    void clear();
    void set(const QPoint& pointPixel, const QPointF& pointReel, const int& typePoint);
    void set(const int& pointPixelX, const int& pointPixelY, const double& pointReelX,
            const double& pointReelY, const int& typePoint);
    void copy(const Point& point);
    bool equals(const Point& point) const;
    void fromString(const QString& fromString, const QChar& sep);
    const QString toString(const QChar& sep) const;

    // Méthodes spécifiques
    const QString getTypePointTexte() const;
    void setTypePointTexte(const QString& typePointTexte);

    // Enumération des types de points
    enum typesPoints
    {
        INDEFINI, REPERE, MANUEL, COURBE, COURBE_DEBUT, COURBE_FIN
    };

private:
    // Attributs de classe
    QPoint pointPixel;
    QPointF pointReel;
    int typePoint;

    // Attributs de classe inaccessibles
    static const QMap<int, QString> typesPointsTexte;
};

typedef QList<Point> Courbe;

#endif /* POINT_H */
