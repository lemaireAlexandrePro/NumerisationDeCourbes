//==============================================================================
// Name        : ParametresRecherche.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Header file of the ParametresRecherche class
//==============================================================================

#ifndef PARAMETRESRECHERCHE_H
#define PARAMETRESRECHERCHE_H

#include <QChar>
#include <QString>

class ParametresRecherche
{
public:
    // Constructeurs et destructeurs
    ParametresRecherche();
    ParametresRecherche(const int& seuilToleranceNiveauxDeGris,
            const int& seuilToleranceTeintesSaturees, const bool& selectionValeursMoyennes,
            const bool& selectionValeursMinimales, const bool& selectionValeursMaximales);
    ParametresRecherche(const ParametresRecherche& parametresRecherche);
    virtual ~ParametresRecherche();

    // Opérateurs
    ParametresRecherche& operator=(const ParametresRecherche& parametresRecherche);
    bool operator==(const ParametresRecherche& parametresRecherche) const;
    bool operator!=(const ParametresRecherche& parametresRecherche) const;

    // Getters
    const int& getSeuilToleranceNiveauxDeGris() const;
    const int& getSeuilToleranceTeintesSaturees() const;
    const bool& getSelectionValeursMoyennes() const;
    const bool& getSelectionValeursMinimales() const;
    const bool& getSelectionValeursMaximales() const;

    // Setters
    void setSeuilToleranceNiveauxDeGris(const int& seuilToleranceNiveauxDeGris);
    void setSeuilToleranceTeintesSaturees(const int& seuilToleranceTeintesSaturees);
    void setSelectionValeursMoyennes(const bool& selectionValeursMoyennes);
    void setSelectionValeursMinimales(const bool& selectionValeursMinimales);
    void setSelectionValeursMaximales(const bool& selectionValeursMaximales);

    // Méthodes génériques
    void clear();
    void set(const int& seuilToleranceNiveauxDeGris, const int& seuilToleranceTeintesSaturees,
            const bool& selectionValeursMoyennes, const bool& selectionValeursMinimales,
            const bool& selectionValeursMaximales);
    void copy(const ParametresRecherche& parametresRecherche);
    bool equals(const ParametresRecherche& parametresRecherche) const;
    void fromString(const QString& fromString, const QChar& sep);
    const QString toString(const QChar& sep) const;

    // Méthodes spécifiques
    double getSeuilToleranceNiveauxDeGrisFacteur() const;
    double getSeuilToleranceTeintesSatureesFacteur() const;
    void setSeuilToleranceNiveauxDeGrisFacteur(const double& seuilToleranceNiveauxDeGrisFacteur);
    void setSeuilToleranceTeintesSatureesFacteur(
            const double& seuilToleranceTeintesSatureesFacteur);

    // Définition des valeurs par défaut des paramètres de recherche
    static const int seuilToleranceNiveauxDeGrisDefaut;
    static const int seuilToleranceTeintesSatureesDefaut;
    static const bool selectionValeursMoyennesDefaut;
    static const bool selectionValeursMinimalesDefaut;
    static const bool selectionValeursMaximalesDefaut;

private:
    // Attributs de classe
    int seuilToleranceNiveauxDeGris;
    int seuilToleranceTeintesSaturees;
    bool selectionValeursMoyennes;
    bool selectionValeursMinimales;
    bool selectionValeursMaximales;
};

#endif /* PARAMETRESRECHERCHE_H */
