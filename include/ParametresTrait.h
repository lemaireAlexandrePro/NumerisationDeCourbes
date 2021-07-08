//==============================================================================
// Name        : ParametresTrait.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Header file of the ParametresTrait class
//==============================================================================

#ifndef PARAMETRESTRAIT_H
#define PARAMETRESTRAIT_H

#include <QChar>
#include <QMap>
#include <QRgb>
#include <QString>

class ParametresTrait
{
public:
    // Constructeurs et destructeurs
    ParametresTrait();
    ParametresTrait(const int& styleTrait, const int& epaisseurTrait, const QRgb& couleurTrait);
    ParametresTrait(const ParametresTrait& parametresTrait);
    virtual ~ParametresTrait();

    // Opérateurs
    ParametresTrait& operator=(const ParametresTrait& parametresTrait);
    bool operator==(const ParametresTrait& parametresTrait) const;
    bool operator!=(const ParametresTrait& parametresTrait) const;

    // Getters
    const int& getStyleTrait() const;
    const int& getEpaisseurTrait() const;
    const QRgb& getCouleurTrait() const;

    // Setters
    void setStyleTrait(const int& styleTrait);
    void setEpaisseurTrait(const int& epaisseurTrait);
    void setCouleurTrait(const QRgb& couleurTrait);

    // Méthodes génériques
    void clear();
    void set(const int& styleTrait, const int& epaisseurTrait, const QRgb& couleurTrait);
    void copy(const ParametresTrait& parametresTrait);
    bool equals(const ParametresTrait& parametresTrait) const;
    void fromString(const QString& fromString, const QChar& sep);
    const QString toString(const QChar& sep) const;

    // Méthodes spécifiques
    const QString getStyleTraitTexte() const;
    void setStyleTraitTexte(const QString& styleTraitTexte);

    // Enumération des styles de traits
    enum stylesTraits
    {
        LIGNE, TIRETS, POINTILLES
    };

    // Définition des valeurs par défaut des paramètres d'un trait
    static const int styleTraitDefaut;
    static const int epaisseurTraitDefaut;
    static const QRgb couleurTraitDefaut;
    static const QRgb couleurTraitAxeDefaut;
    static const QRgb couleurTraitCourbeDefaut;

private:
    // Attributs de classe
    int styleTrait;
    int epaisseurTrait;
    QRgb couleurTrait;

    // Attributs de classe inaccessibles
    static const QMap<int, QString> stylesTraitsTexte;
};

#endif /* PARAMETRESTRAIT_H */
