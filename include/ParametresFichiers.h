//==============================================================================
// Name        : ParametresFichiers.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Header file of the ParametresFichiers class
//==============================================================================

#ifndef PARAMETRESFICHIERS_H
#define PARAMETRESFICHIERS_H

#include <QChar>
#include <QString>

class ParametresFichiers
{
public:
    // Constructeurs et destructeurs
    ParametresFichiers();
    ParametresFichiers(const QString& cheminFichierEtude, const QString& cheminFichierImageSource,
            const QString& cheminFichierImageConvertie, const QString& cheminFichierExport,
            const QString& cheminFichierParametres, const QString& cheminFichierGraphique);
    ParametresFichiers(const ParametresFichiers& parametresFichiers);
    virtual ~ParametresFichiers();

    // Opérateurs
    ParametresFichiers& operator=(const ParametresFichiers& parametresFichiers);
    bool operator==(const ParametresFichiers& parametresFichiers) const;
    bool operator!=(const ParametresFichiers& parametresFichiers) const;

    // Getters
    const QString& getCheminFichierEtude() const;
    const QString& getCheminFichierImageSource() const;
    const QString& getCheminFichierImageConvertie() const;
    const QString& getCheminFichierExport() const;
    const QString& getCheminFichierParametres() const;
    const QString& getCheminFichierGraphique() const;

    // Setters
    void setCheminFichierEtude(const QString& cheminFichierEtude);
    void setCheminFichierImageSource(const QString& cheminFichierImageSource);
    void setCheminFichierImageConvertie(const QString& cheminFichierImageConvertie);
    void setCheminFichierExport(const QString& cheminFichierExport);
    void setCheminFichierParametres(const QString& cheminFichierParametres);
    void setCheminFichierGraphique(const QString& cheminFichierGraphique);

    // Méthodes génériques
    void clear();
    void set(const QString& cheminFichierEtude, const QString& cheminFichierImageSource,
            const QString& cheminFichierImageConvertie, const QString& cheminFichierExport,
            const QString& cheminFichierParametres, const QString& cheminFichierGraphique);
    void copy(const ParametresFichiers& parametresFichiers);
    bool equals(const ParametresFichiers& parametresFichiers) const;
    void fromString(const QString& fromString, const QChar& sep);
    const QString toString(const QChar& sep) const;

    // Méthodes spécifiques

private:
    // Attributs de classe
    QString cheminFichierEtude;
    QString cheminFichierImageSource;
    QString cheminFichierImageConvertie;
    QString cheminFichierExport;
    QString cheminFichierParametres;
    QString cheminFichierGraphique;
};

#endif /* PARAMETRESFICHIERS_H */
