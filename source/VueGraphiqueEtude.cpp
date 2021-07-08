//==============================================================================
// Name        : VueGraphiqueEtude.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Source file of the VueGraphiqueEtude class
//==============================================================================

#include "VueGraphiqueEtude.h"
#include <cmath>
#include <QBrush>
#include <QColor>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPainterPath>
#include <QPen>
#include <QPixmap>
#include <QPoint>
#include <QPolygon>
#include <QRgb>

const double VueGraphiqueEtude::facteurZoomIn = 1.25;
const double VueGraphiqueEtude::facteurZoomOut = 0.8;

VueGraphiqueEtude::VueGraphiqueEtude(QWidget* parent) :
        QGraphicsView(parent)
{
    QGraphicsScene* graphicsScene = new QGraphicsScene(parent);
    this->setScene(graphicsScene);
}

VueGraphiqueEtude::VueGraphiqueEtude(QGraphicsScene* scene, QWidget* parent) :
        QGraphicsView(scene, parent)
{
}

VueGraphiqueEtude::~VueGraphiqueEtude()
{
}

void VueGraphiqueEtude::repositionner()
{
    this->resetTransform();
}

void VueGraphiqueEtude::effacer()
{
    this->scene()->clear();
}

void VueGraphiqueEtude::dessiner(const Etude& etude)
{
    const Image& image = etude.getImage();
    const Repere& repere = etude.getRepere();
    const ParametresTrait& parametresAxes =
            etude.getParametres().getParametresAffichage().getParametresAxes();
    const ParametresTrait& parametresCourbes =
            etude.getParametres().getParametresAffichage().getParametresCourbes();
    const ParametresPoint& parametresPointsAxes =
            etude.getParametres().getParametresAffichage().getParametresPointsAxes();
    const ParametresPoint& parametresPointsCourbes =
            etude.getParametres().getParametresAffichage().getParametresPointsCourbes();
    const ParametresPoint& parametresPointsManuels =
            etude.getParametres().getParametresAffichage().getParametresPointsManuels();

    const QList<Courbe> listeDeCourbes = etude.getListeDeCourbes();
    const QList<Point> listeDePointsManuels = etude.getListeDePointsManuels();
    const int nombreDeCourbes = listeDeCourbes.count();
    const int nombreDePointsManuels = listeDePointsManuels.count();

    this->effacer();
    this->dessinerImage(image);
    this->dessinerRepere(repere, parametresAxes, parametresPointsAxes);
    for (int itCourbe = 0; itCourbe < nombreDeCourbes; itCourbe++)
    {
        const Courbe& courbe = listeDeCourbes.at(itCourbe);
        this->dessinerCourbe(courbe, parametresCourbes, parametresPointsCourbes);
    }
    for (int itPointManuel = 0; itPointManuel < nombreDePointsManuels; itPointManuel++)
    {
        const Point& pointManuel = listeDePointsManuels.at(itPointManuel);
        this->dessinerPointManuel(pointManuel, parametresPointsManuels);
    }
}

void VueGraphiqueEtude::dessinerImage(const Image& image)
{
    const QImage& imageConvertie = image.getImageConvertie();
    const int largeurImage = imageConvertie.width();
    const int hauteurImage = imageConvertie.height();
    QGraphicsPixmapItem* itemImage = new QGraphicsPixmapItem(QPixmap::fromImage(imageConvertie));
    this->scene()->addItem(itemImage);
    this->scene()->setSceneRect(0, 0, largeurImage, hauteurImage);
}

void VueGraphiqueEtude::dessinerRepere(const Repere& repere, const ParametresTrait& parametresAxes,
        const ParametresPoint& parametresPointsAxes)
{
    const Point& pointX0 = repere.getPointX0();
    const Point& pointX1 = repere.getPointX1();
    const Point& pointY0 = repere.getPointY0();
    const Point& pointY1 = repere.getPointY1();

    this->dessinerTrait(pointX0, pointX1, parametresAxes);
    this->dessinerTrait(pointY0, pointY1, parametresAxes);
    this->dessinerPoint(pointX0, parametresPointsAxes);
    this->dessinerPoint(pointX1, parametresPointsAxes);
    this->dessinerPoint(pointY0, parametresPointsAxes);
    this->dessinerPoint(pointY1, parametresPointsAxes);
}

void VueGraphiqueEtude::dessinerCourbe(const Courbe& courbe,
        const ParametresTrait& parametresCourbes, const ParametresPoint& parametresPointsCourbes)
{
    const int nombreDePointsCourbe = courbe.count();
    const Point& premierPoint = courbe.at(0);
    const Point& dernierPoint = courbe.at(nombreDePointsCourbe - 1);
    this->dessinerTraitContinu(courbe, parametresCourbes);
    this->dessinerPoint(premierPoint, parametresPointsCourbes);
    this->dessinerPoint(dernierPoint, parametresPointsCourbes);
}

void VueGraphiqueEtude::dessinerPointManuel(const Point& pointManuel,
        const ParametresPoint& parametresPointsManuels)
{
    this->dessinerPoint(pointManuel, parametresPointsManuels);
}

void VueGraphiqueEtude::dessinerPoint(const Point& point, const ParametresPoint& parametresPoint)
{
    const int& stylePoint = parametresPoint.getStylePoint();
    const int& epaisseurPoint = parametresPoint.getEpaisseurPoint();
    const QRgb& couleurPoint = parametresPoint.getCouleurPoint();
    const QBrush brossePoint = QBrush(QColor(couleurPoint), Qt::SolidPattern);
    const QPen pinceauPoint = QPen(brossePoint, 0, Qt::SolidLine);

    const double ppx = point.getPointPixelX();
    const double ppy = point.getPointPixelY();
    const double ppx_edit = ppx - floor(epaisseurPoint / 2.0);
    const double ppy_edit = ppy - floor(epaisseurPoint / 2.0);

    if (stylePoint == ParametresPoint::CARRE)
    {
        this->scene()->addRect(ppx_edit, ppy_edit, epaisseurPoint, epaisseurPoint, pinceauPoint,
                brossePoint);
    }
    else if (stylePoint == ParametresPoint::CERCLE)
    {
        this->scene()->addEllipse(ppx_edit, ppy_edit, epaisseurPoint, epaisseurPoint, pinceauPoint,
                brossePoint);
    }
}

void VueGraphiqueEtude::dessinerTrait(const Point& point1, const Point& point2,
        const ParametresTrait& parametresTrait)
{
    const int& styleTrait = parametresTrait.getStyleTrait();
    const int& epaisseurTrait = parametresTrait.getEpaisseurTrait();
    const QRgb& couleurTrait = parametresTrait.getCouleurTrait();
    const QBrush brosseTrait = QBrush(QColor(couleurTrait), Qt::SolidPattern);
    const QPen pinceauTrait = QPen(brosseTrait, epaisseurTrait,
            static_cast<Qt::PenStyle>(styleTrait + 1), Qt::RoundCap, Qt::RoundJoin);

    const double p1px = point1.getPointPixelX();
    const double p1py = point1.getPointPixelY();
    const double p2px = point2.getPointPixelX();
    const double p2py = point2.getPointPixelY();

    this->scene()->addLine(p1px, p1py, p2px, p2py, pinceauTrait);
}

void VueGraphiqueEtude::dessinerTraitContinu(const QList<Point>& listeDePoints,
        const ParametresTrait& parametresTrait)
{
    const int& styleTrait = parametresTrait.getStyleTrait();
    const int& epaisseurTrait = parametresTrait.getEpaisseurTrait();
    const QRgb& couleurTrait = parametresTrait.getCouleurTrait();
    const QBrush brosseTrait = QBrush(QColor(couleurTrait), Qt::SolidPattern);
    const QPen pinceauTrait = QPen(brosseTrait, epaisseurTrait,
            static_cast<Qt::PenStyle>(styleTrait + 1), Qt::RoundCap, Qt::RoundJoin);

    QPolygon polygone;
    const int nombreDePoints = listeDePoints.count();
    for (int itPoint = 0; itPoint < nombreDePoints; itPoint++)
    {
        const Point& pointCourant = listeDePoints.at(itPoint);
        const QPoint& pointPixelCourant = pointCourant.getPointPixel();
        polygone.append(pointPixelCourant);
    }
    QPainterPath chemin;
    chemin.addPolygon(polygone);

    this->scene()->addPath(chemin, pinceauTrait);
}

void VueGraphiqueEtude::keyPressEvent(QKeyEvent* event)
{
    QGraphicsView::keyPressEvent(event);

    if (event->key() == Qt::Key_Plus)
    {
        this->scale(facteurZoomIn, facteurZoomIn);
    }
    else if (event->key() == Qt::Key_Minus)
    {
        this->scale(facteurZoomOut, facteurZoomOut);
    }
    else if (event->key() == Qt::Key_0)
    {
        this->resetTransform();
    }
}

void VueGraphiqueEtude::mousePressEvent(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event);

    if (event->button() == Qt::LeftButton)
    {
        emit this->mousePressEventSignal(this->mapToScene(event->pos()));
    }
}

void VueGraphiqueEtude::mouseMoveEvent(QMouseEvent* event)
{
    QGraphicsView::mouseMoveEvent(event);

    emit this->mouseMoveEventSignal(this->mapToScene(event->pos()));
}

void VueGraphiqueEtude::wheelEvent(QWheelEvent* event)
{
    QGraphicsView::wheelEvent(event);

    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    if (event->delta() > 0)
    {
        this->scale(facteurZoomIn, facteurZoomIn);
    }
    else if (event->delta() < 0)
    {
        this->scale(facteurZoomOut, facteurZoomOut);
    }
}
