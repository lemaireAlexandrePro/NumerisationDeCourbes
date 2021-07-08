//==============================================================================
// Name        : Outils.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Header file of the Outils elements
//==============================================================================

#ifndef OUTILS_H
#define OUTILS_H

#include "Point.h"
#include <QChar>
#include <QList>
#include <QPoint>
#include <QString>
#include <QStringList>

bool lessThanQPoint(const QPoint& point1, const QPoint& point2);
int getValeurMoyenne(const QList<int>& listeValeurs);
int getValeurMinimale(const QList<int>& listeValeurs);
int getValeurMaximale(const QList<int>& listeValeurs);
const QList<QList<int>> listesValeursAdjacentes(const QList<int>& listeValeurs);
const QStringList listeSousElements(const QString& chaineElements, const QChar& sep);
void interpolationNumerique(const double& x1, const double& y1, const double& x2, const double& y2,
        const double& x, double& y);
void interpolationNumerique(const Point& point1, const Point& point2, Point& point);
const QList<Point> interpolationNumerique(const QList<Point>& listeDePoints, const double& pas);
void genererImageTest();
void testerConversionNoirEtBlanc(const int& seuilNoirEtBlanc);
void testerConversionNiveauxDeGris(const int& nombreNiveauxDeGris);
void testerConversionTeintesSaturees(const int& nombreNiveauxDeGris,
        const int& nombreTeintesSaturees, const int& seuilSaturation);

#endif /* OUTILS_H */
