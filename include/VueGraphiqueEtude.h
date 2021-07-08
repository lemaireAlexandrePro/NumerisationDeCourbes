//==============================================================================
// Name        : VueGraphiqueEtude.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Header file of the VueGraphiqueEtude class
//==============================================================================

#ifndef VUEGRAPHIQUEETUDE_H
#define VUEGRAPHIQUEETUDE_H

#include "Etude.h"
#include "Image.h"
#include "ParametresPoint.h"
#include "ParametresTrait.h"
#include "Point.h"
#include "Repere.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QList>
#include <QMouseEvent>
#include <QPointF>
#include <QWheelEvent>
#include <QWidget>

class VueGraphiqueEtude : public QGraphicsView
{
    Q_OBJECT

public:
    // Constructeurs et destructeurs
    explicit VueGraphiqueEtude(QWidget* parent);
    explicit VueGraphiqueEtude(QGraphicsScene* scene, QWidget* parent);
    ~VueGraphiqueEtude();

    // Getters

    // Setters

    // Méthodes génériques

    // Méthodes spécifiques
    void repositionner();
    void effacer();
    void dessiner(const Etude& etude);
    void dessinerImage(const Image& image);
    void dessinerRepere(const Repere& repere, const ParametresTrait& parametresAxes,
            const ParametresPoint& parametresPointsAxes);
    void dessinerCourbe(const Courbe& courbe, const ParametresTrait& parametresCourbes,
            const ParametresPoint& parametresPointsCourbes);
    void dessinerPointManuel(const Point& pointManuel,
            const ParametresPoint& parametresPointsManuels);
    void dessinerPoint(const Point& point, const ParametresPoint& parametresPoint);
    void dessinerTrait(const Point& point1, const Point& point2,
            const ParametresTrait& parametresTrait);
    void dessinerTraitContinu(const QList<Point>& listeDePoints,
            const ParametresTrait& parametresTrait);

protected:
    // Méthodes spécifiques
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

private:
    // Attributs de classe

    // Attributs de classe inaccessibles
    static const double facteurZoomIn;
    static const double facteurZoomOut;

signals:
    // Signaux spécifiques
    void mousePressEventSignal(const QPointF pointVueGraphique);
    void mouseMoveEventSignal(const QPointF pointVueGraphique);
};

#endif /* VUEGRAPHIQUEETUDE_H */
