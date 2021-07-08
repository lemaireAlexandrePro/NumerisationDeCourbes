//==============================================================================
// Name        : ParametresAffichage.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Header file of the ParametresAffichage class
//==============================================================================

#ifndef PARAMETRESAFFICHAGE_H
#define PARAMETRESAFFICHAGE_H

#include "ParametresPoint.h"
#include "ParametresTrait.h"
#include <QChar>
#include <QMap>
#include <QString>

class ParametresAffichage
{
public:
    // Constructeurs et destructeurs
    ParametresAffichage();
    ParametresAffichage(const int& formatNotationNombres, const int& nombreChiffresSignificatifs,
            const ParametresTrait& parametresAxes, const ParametresTrait& parametresCourbes,
            const ParametresPoint& parametresPointsAxes,
            const ParametresPoint& parametresPointsCourbes,
            const ParametresPoint& parametresPointsManuels);
    ParametresAffichage(const ParametresAffichage& parametresAffichage);
    virtual ~ParametresAffichage();

    // Opérateurs
    ParametresAffichage& operator=(const ParametresAffichage& parametresAffichage);
    bool operator==(const ParametresAffichage& parametresAffichage) const;
    bool operator!=(const ParametresAffichage& parametresAffichage) const;

    // Getters
    const int& getFormatNotationNombres() const;
    const int& getNombreChiffresSignificatifs() const;
    const ParametresTrait& getParametresAxes() const;
    const ParametresTrait& getParametresCourbes() const;
    const ParametresPoint& getParametresPointsAxes() const;
    const ParametresPoint& getParametresPointsCourbes() const;
    const ParametresPoint& getParametresPointsManuels() const;

    // Setters
    void setFormatNotationNombres(const int& formatNotationNombres);
    void setNombreChiffresSignificatifs(const int& nombreChiffresSignificatifs);
    void setParametresAxes(const ParametresTrait& parametresAxes);
    void setParametresCourbes(const ParametresTrait& parametresCourbes);
    void setParametresPointsAxes(const ParametresPoint& parametresPointsAxes);
    void setParametresPointsCourbes(const ParametresPoint& parametresPointsCourbes);
    void setParametresPointsManuels(const ParametresPoint& parametresPointsManuels);

    // Méthodes génériques
    void clear();
    void set(const int& formatNotationNombres, const int& nombreChiffresSignificatifs,
            const ParametresTrait& parametresAxes, const ParametresTrait& parametresCourbes,
            const ParametresPoint& parametresPointsAxes,
            const ParametresPoint& parametresPointsCourbes,
            const ParametresPoint& parametresPointsManuels);
    void copy(const ParametresAffichage& parametresAffichage);
    bool equals(const ParametresAffichage& parametresAffichage) const;
    void fromString(const QString& fromString, const QChar& sep);
    const QString toString(const QChar& sep) const;

    // Méthodes spécifiques
    char getFormatNotationNombresCaractere() const;
    const QString getFormatNotationNombresTexte() const;
    void setFormatNotationNombresCaractere(const char& formatNotationNombresCaractere);
    void setFormatNotationNombresTexte(const QString& formatNotationNombresTexte);

    // Enumération des formats de notation des nombres
    enum formatsNotationNombres
    {
        STANDARD, SCIENTIFIQUE
    };

    // Définition des valeurs par défaut des paramètres d'affichage
    static const int formatNotationNombresDefaut;
    static const int nombreChiffresSignificatifsDefaut;
    static const ParametresTrait parametresAxesDefaut;
    static const ParametresTrait parametresCourbesDefaut;
    static const ParametresPoint parametresPointsAxesDefaut;
    static const ParametresPoint parametresPointsCourbesDefaut;
    static const ParametresPoint parametresPointsManuelsDefaut;

private:
    // Attributs de classe
    int formatNotationNombres;
    int nombreChiffresSignificatifs;
    ParametresTrait parametresAxes;
    ParametresTrait parametresCourbes;
    ParametresPoint parametresPointsAxes;
    ParametresPoint parametresPointsCourbes;
    ParametresPoint parametresPointsManuels;

    // Attributs de classe inaccessibles
    static const QMap<int, char> formatsNotationNombresCaractere;
    static const QMap<int, QString> formatsNotationNombresTexte;
};

#endif /* PARAMETRESAFFICHAGE_H */
