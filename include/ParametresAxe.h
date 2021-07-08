//==============================================================================
// Name        : ParametresAxe.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Header file of the ParametresAxe class
//==============================================================================

#ifndef PARAMETRESAXE_H
#define PARAMETRESAXE_H

#include <QChar>
#include <QString>

class ParametresAxe
{
public:
    // Constructeurs et destructeurs
    ParametresAxe();
    ParametresAxe(const double& borneInferieure, const double& borneSuperieure,
            const double& pasPrincipal, const double& pasSecondaire, const bool& grillePrincipale,
            const bool& grilleSecondaire);
    ParametresAxe(const ParametresAxe& parametresAxe);
    virtual ~ParametresAxe();

    // Opérateurs
    ParametresAxe& operator=(const ParametresAxe& parametresAxe);
    bool operator==(const ParametresAxe& parametresAxe) const;
    bool operator!=(const ParametresAxe& parametresAxe) const;

    // Getters
    const double& getBorneInferieure() const;
    const double& getBorneSuperieure() const;
    const double& getPasPrincipal() const;
    const double& getPasSecondaire() const;
    const bool& getGrillePrincipale() const;
    const bool& getGrilleSecondaire() const;

    // Setters
    void setBorneInferieure(const double& borneInferieure);
    void setBorneSuperieure(const double& borneSuperieure);
    void setPasPrincipal(const double& pasPrincipal);
    void setPasSecondaire(const double& pasSecondaire);
    void setGrillePrincipale(const bool& grillePrincipale);
    void setGrilleSecondaire(const bool& grilleSecondaire);

    // Méthodes génériques
    void clear();
    void set(const double& borneInferieure, const double& borneSuperieure,
            const double& pasPrincipal, const double& pasSecondaire, const bool& grillePrincipale,
            const bool& grilleSecondaire);
    void copy(const ParametresAxe& parametresAxe);
    bool equals(const ParametresAxe& parametresAxe) const;
    void fromString(const QString& fromString, const QChar& sep);
    const QString toString(const QChar& sep) const;

    // Méthodes spécifiques
    void ajuster();
    void ajusterBornes();
    void ajusterPasPrincipal();
    void ajusterPasSecondaire();

    // Définition des valeurs par défaut des paramètres d'axe
    static const double borneInferieureDefaut;
    static const double borneSuperieureDefaut;
    static const double pasPrincipalDefaut;
    static const double pasSecondaireDefaut;
    static const bool grillePrincipaleDefaut;
    static const bool grilleSecondaireDefaut;
    static const int nombreElementsPasPrincipalDefaut;
    static const int nombreElementsPasSecondaireDefaut;

private:
    // Attributs de classe
    double borneInferieure;
    double borneSuperieure;
    double pasPrincipal;
    double pasSecondaire;
    bool grillePrincipale;
    bool grilleSecondaire;
};

#endif /* PARAMETRESAXE_H */
