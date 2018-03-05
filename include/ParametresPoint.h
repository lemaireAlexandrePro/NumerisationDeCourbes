//==============================================================================
// Name        : ParametresPoint.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.1.1 (05/03/2018)
// Description : Header file of the ParametresPoint class
//==============================================================================

#ifndef PARAMETRESPOINT_H
#define PARAMETRESPOINT_H

#include <QMap>
#include <QRgb>
#include <QString>

class ParametresPoint
{
public:
    // Constructeurs et destructeurs
    ParametresPoint();
    ParametresPoint(const int& stylePoint, const int& epaisseurPoint, const QRgb& couleurPoint);
    ParametresPoint(const ParametresPoint& parametresPoint);
    virtual ~ParametresPoint();

    // Getters
    const int& getStylePoint() const;
    const int& getEpaisseurPoint() const;
    const QRgb& getCouleurPoint() const;

    // Setters
    void setStylePoint(const int& stylePoint);
    void setEpaisseurPoint(const int& epaisseurPoint);
    void setCouleurPoint(const QRgb& couleurPoint);

    // Méthodes génériques
    void clear();
    void set(const int& stylePoint, const int& epaisseurPoint, const QRgb& couleurPoint);
    void copy(const ParametresPoint& parametresPoint);
    bool equals(const ParametresPoint& parametresPoint) const;
    void fromString(const QString& fromString, const char& sep);
    const QString toString(const char& sep) const;

    // Méthodes spécifiques
    const QString getStylePointTexte() const;
    void setStylePointTexte(const QString& stylePointTexte);

    // Enumération des styles de points
    enum stylesPoints
    {
        CARRE, CERCLE
    };

    // Définition des valeurs par défaut des paramètres d'un point
    static const int stylePointDefaut;
    static const int epaisseurPointDefaut;
    static const QRgb couleurPointDefaut;
    static const QRgb couleurPointAxeDefaut;
    static const QRgb couleurPointCourbeDefaut;
    static const QRgb couleurPointManuelDefaut;

private:
    // Attributs de classe
    int stylePoint;
    int epaisseurPoint;
    QRgb couleurPoint;

    // Attributs de classe inaccessibles
    static const QMap<int, QString> stylesPointsTexte;
};

#endif /* PARAMETRESPOINT_H */
