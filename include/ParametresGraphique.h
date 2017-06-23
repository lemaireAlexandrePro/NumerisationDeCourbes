//==============================================================================
// Name        : ParametresGraphique.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.5 (07/06/2017)
// Description : Header file of the ParametresGraphique class
//==============================================================================

#ifndef PARAMETRESGRAPHIQUE_H_
#define PARAMETRESGRAPHIQUE_H_

#include "ParametresAxe.h"
#include <QString>

class ParametresGraphique
{
public:
    // Constructeurs et destructeurs
    ParametresGraphique();
    ParametresGraphique(const ParametresAxe& parametresAxeHorizontal,
            const ParametresAxe& parametresAxeVertical);
    ParametresGraphique(const ParametresGraphique& parametresGraphique);
    virtual ~ParametresGraphique();

    // Getters
    const ParametresAxe& getParametresAxeHorizontal() const;
    const ParametresAxe& getParametresAxeVertical() const;

    // Setters
    void setParametresAxeHorizontal(const ParametresAxe& parametresAxeHorizontal);
    void setParametresAxeVertical(const ParametresAxe& parametresAxeVertical);

    // Méthodes génériques
    void clear();
    void set(const ParametresAxe& parametresAxeHorizontal,
            const ParametresAxe& parametresAxeVertical);
    void copy(const ParametresGraphique& parametresGraphique);
    bool equals(const ParametresGraphique& parametresGraphique) const;
    void fromString(const QString& fromString, const char& sep);
    const QString toString(const char& sep) const;

    // Méthodes spécifiques
    // TODO Méthodes spécifiques "ParametresGraphique"

private:
    // Attributs de classe
    ParametresAxe parametresAxeHorizontal;
    ParametresAxe parametresAxeVertical;
};

#endif /* PARAMETRESGRAPHIQUE_H_ */