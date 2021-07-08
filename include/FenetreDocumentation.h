//==============================================================================
// Name        : FenetreDocumentation.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Header file of the FenetreDocumentation class
//==============================================================================

#ifndef FENETREDOCUMENTATION_H
#define FENETREDOCUMENTATION_H

#include <QDialog>
#include <QWidget>

namespace Ui
{
class FenetreDocumentation;
}

class FenetreDocumentation : public QDialog
{
    Q_OBJECT

public:
    // Constructeurs et destructeurs
    explicit FenetreDocumentation(QWidget* parent = nullptr);
    ~FenetreDocumentation();

    // Getters

    // Setters

    // Méthodes génériques

    // Méthodes spécifiques

private:
    // Attributs de classe
    Ui::FenetreDocumentation* ui;
};

#endif /* FENETREDOCUMENTATION_H */
