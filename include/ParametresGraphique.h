//==============================================================================
// Name        : ParametresGraphique.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Header file of the ParametresGraphique class
//==============================================================================

#ifndef PARAMETRESGRAPHIQUE_H
#define PARAMETRESGRAPHIQUE_H

#include "ParametresAxe.h"
#include <QChar>
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

    // Opérateurs
    ParametresGraphique& operator=(const ParametresGraphique& parametresGraphique);
    bool operator==(const ParametresGraphique& parametresGraphique) const;
    bool operator!=(const ParametresGraphique& parametresGraphique) const;

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
    void fromString(const QString& fromString, const QChar& sep);
    const QString toString(const QChar& sep) const;

    // Méthodes spécifiques

private:
    // Attributs de classe
    ParametresAxe parametresAxeHorizontal;
    ParametresAxe parametresAxeVertical;
};

#endif /* PARAMETRESGRAPHIQUE_H */
