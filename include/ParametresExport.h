//==============================================================================
// Name        : ParametresExport.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Header file of the ParametresExport class
//==============================================================================

#ifndef PARAMETRESEXPORT_H
#define PARAMETRESEXPORT_H

#include <QChar>
#include <QMap>
#include <QString>

class ParametresExport
{
public:
    // Constructeurs et destructeurs
    ParametresExport();
    ParametresExport(const int& formatNotationNombres, const int& nombreChiffresSignificatifs,
            const char& caractereSeparation, const char& caractereSeparateurDecimal,
            const double& seuilInterpolationNumerique);
    ParametresExport(const ParametresExport& parametresExport);
    virtual ~ParametresExport();

    // Opérateurs
    ParametresExport& operator=(const ParametresExport& parametresExport);
    bool operator==(const ParametresExport& parametresExport) const;
    bool operator!=(const ParametresExport& parametresExport) const;

    // Getters
    const int& getFormatNotationNombres() const;
    const int& getNombreChiffresSignificatifs() const;
    const char& getCaractereSeparation() const;
    const char& getCaractereSeparateurDecimal() const;
    const double& getSeuilInterpolationNumerique() const;

    // Setters
    void setFormatNotationNombres(const int& formatNotationNombres);
    void setNombreChiffresSignificatifs(const int& nombreChiffresSignificatifs);
    void setCaractereSeparation(const char& caractereSeparation);
    void setCaractereSeparateurDecimal(const char& caractereSeparateurDecimal);
    void setSeuilInterpolationNumerique(const double& seuilInterpolationNumerique);

    // Méthodes génériques
    void clear();
    void set(const int& formatNotationNombres, const int& nombreChiffresSignificatifs,
            const char& caractereSeparation, const char& caractereSeparateurDecimal,
            const double& seuilInterpolationNumerique);
    void copy(const ParametresExport& parametresExport);
    bool equals(const ParametresExport& parametresExport) const;
    void fromString(const QString& fromString, const QChar& sep);
    const QString toString(const QChar& sep) const;

    // Méthodes spécifiques
    char getFormatNotationNombresCaractere() const;
    const QString getFormatNotationNombresTexte() const;
    int getCaractereSeparationIndice() const;
    const QString getCaractereSeparationTexte() const;
    int getCaractereSeparateurDecimalIndice() const;
    const QString getCaractereSeparateurDecimalTexte() const;
    void setFormatNotationNombresCaractere(const char& formatNotationNombresCaractere);
    void setFormatNotationNombresTexte(const QString& formatNotationNombresTexte);
    void setCaractereSeparationIndice(const int& caractereSeparationIndice);
    void setCaractereSeparationTexte(const QString& caractereSeparationTexte);
    void setCaractereSeparateurDecimalIndice(const int& caractereSeparateurDecimalIndice);
    void setCaractereSeparateurDecimalTexte(const QString& caractereSeparateurDecimalTexte);

    // Enumération des formats de notation des nombres
    enum formatsNotationNombres
    {
        STANDARD, SCIENTIFIQUE
    };

    // Enumération des correspondances entre caractères de séparation et indices
    enum indicesCaracteresSeparation
    {
        ESPACE, TABULATION, POINT_VIRGULE
    };

    // Enumération des correspondances entre caractères de séparateur décimal et indices
    enum indicesCaracteresSeparateurDecimal
    {
        POINT, VIRGULE
    };

    // Définition des valeurs par défaut des paramètres d'export
    static const int formatNotationNombresDefaut;
    static const int nombreChiffresSignificatifsDefaut;
    static const char caractereSeparationDefaut;
    static const char caractereSeparateurDecimalDefaut;
    static const double seuilInterpolationNumeriqueDefaut;

private:
    // Attributs de classe
    int formatNotationNombres;
    int nombreChiffresSignificatifs;
    char caractereSeparation;
    char caractereSeparateurDecimal;
    double seuilInterpolationNumerique;

    // Attributs de classe inaccessibles
    static const QMap<int, char> formatsNotationNombresCaractere;
    static const QMap<int, QString> formatsNotationNombresTexte;
    static const QMap<char, int> caracteresSeparationIndice;
    static const QMap<char, QString> caracteresSeparationTexte;
    static const QMap<char, int> caracteresSeparateurDecimalIndice;
    static const QMap<char, QString> caracteresSeparateurDecimalTexte;
};

#endif /* PARAMETRESEXPORT_H */
