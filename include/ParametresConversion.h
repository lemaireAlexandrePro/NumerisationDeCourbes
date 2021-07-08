//==============================================================================
// Name        : ParametresConversion.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Header file of the ParametresConversion class
//==============================================================================

#ifndef PARAMETRESCONVERSION_H
#define PARAMETRESCONVERSION_H

#include <QChar>
#include <QMap>
#include <QString>

class ParametresConversion
{
public:
    // Constructeurs et destructeurs
    ParametresConversion();
    ParametresConversion(const int& methodeConversion, const int& seuilNoirEtBlanc,
            const int& nombreNiveauxDeGris, const int& nombreTeintesSaturees,
            const int& seuilSaturation);
    ParametresConversion(const ParametresConversion& parametresConversion);
    virtual ~ParametresConversion();

    // Opérateurs
    ParametresConversion& operator=(const ParametresConversion& parametresConversion);
    bool operator==(const ParametresConversion& parametresConversion) const;
    bool operator!=(const ParametresConversion& parametresConversion) const;

    // Getters
    const int& getMethodeConversion() const;
    const int& getSeuilNoirEtBlanc() const;
    const int& getNombreNiveauxDeGris() const;
    const int& getNombreTeintesSaturees() const;
    const int& getSeuilSaturation() const;

    // Setters
    void setMethodeConversion(const int& methodeConversion);
    void setSeuilNoirEtBlanc(const int& seuilNoirEtBlanc);
    void setNombreNiveauxDeGris(const int& nombreNiveauxDeGris);
    void setNombreTeintesSaturees(const int& nombreTeintesSaturees);
    void setSeuilSaturation(const int& seuilSaturation);

    // Méthodes génériques
    void clear();
    void set(const int& methodeConversion, const int& seuilNoirEtBlanc,
            const int& nombreNiveauxDeGris, const int& nombreTeintesSaturees,
            const int& seuilSaturation);
    void copy(const ParametresConversion& parametresConversion);
    bool equals(const ParametresConversion& parametresConversion) const;
    void fromString(const QString& fromString, const QChar& sep);
    const QString toString(const QChar& sep) const;

    // Méthodes spécifiques
    const QString getMethodeConversionTexte() const;
    double getSeuilNoirEtBlancFacteur() const;
    double getSeuilSaturationFacteur() const;
    void setMethodeConversionTexte(const QString& methodeConversionTexte);
    void setSeuilNoirEtBlancFacteur(const double& seuilNoirEtBlancFacteur);
    void setSeuilSaturationFacteur(const double& seuilSaturationFacteur);

    // Enumération des méthodes de conversion
    enum methodesConversion
    {
        BRUTE, NOIR_ET_BLANC, NIVEAUX_DE_GRIS, TEINTES_SATUREES
    };

    // Définition des valeurs par défaut des paramètres de conversion
    static const int methodeConversionDefaut;
    static const int seuilNoirEtBlancDefaut;
    static const int nombreNiveauxDeGrisDefaut;
    static const int nombreTeintesSatureesDefaut;
    static const int seuilSaturationDefaut;

private:
    // Attributs de classe
    int methodeConversion;
    int seuilNoirEtBlanc;
    int nombreNiveauxDeGris;
    int nombreTeintesSaturees;
    int seuilSaturation;

    // Attributs de classe inaccessibles
    static const QMap<int, QString> methodesConversionTexte;
};

#endif /* PARAMETRESCONVERSION_H */
