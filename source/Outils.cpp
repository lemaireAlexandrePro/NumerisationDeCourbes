//==============================================================================
// Name        : Outils.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Source file of the Outils elements
//==============================================================================

#include "Outils.h"
#include "Image.h"
#include <cmath>
#include <QChar>
#include <QColor>
#include <QImage>

bool lessThanQPoint(const QPoint& point1, const QPoint& point2)
{
    return (point1.x() != point2.x()) ? (point1.x() < point2.x()) : (point1.y() < point2.y());
}

int getValeurMoyenne(const QList<int>& listeValeurs)
{
    int sommeValeurs = 0;
    const int nombreValeurs = listeValeurs.count();
    for (int itValeur = 0; itValeur < nombreValeurs; itValeur++)
    {
        const int& valeur = listeValeurs.at(itValeur);
        sommeValeurs += valeur;
    }
    const int valeurMoyenne =
            (nombreValeurs > 0) ?
                    static_cast<int>(round(
                            static_cast<double>(sommeValeurs) / static_cast<double>(nombreValeurs))) :
                    0;
    return valeurMoyenne;
}

int getValeurMinimale(const QList<int>& listeValeurs)
{
    int valeurMinimale = listeValeurs.at(0);
    const int nombreValeurs = listeValeurs.count();
    for (int itValeur = 0; itValeur < nombreValeurs; itValeur++)
    {
        const int& valeur = listeValeurs.at(itValeur);
        if (valeur < valeurMinimale)
        {
            valeurMinimale = valeur;
        }
    }
    return valeurMinimale;
}

int getValeurMaximale(const QList<int>& listeValeurs)
{
    int valeurMaximale = listeValeurs.at(0);
    const int nombreValeurs = listeValeurs.count();
    for (int itValeur = 0; itValeur < nombreValeurs; itValeur++)
    {
        const int& valeur = listeValeurs.at(itValeur);
        if (valeur > valeurMaximale)
        {
            valeurMaximale = valeur;
        }
    }
    return valeurMaximale;
}

const QList<QList<int>> listesValeursAdjacentes(const QList<int>& listeValeurs)
{
    QList<QList<int>> listesValeursAdjacentes;
    QList<int> listeValeursAdjacentes;
    int valeurPrecedente = listeValeurs.at(0);
    const int nombreValeurs = listeValeurs.count();
    for (int itValeur = 0; itValeur < nombreValeurs; itValeur++)
    {
        const int& valeur = listeValeurs.at(itValeur);
        if (valeur > (valeurPrecedente + 1))
        {
            listesValeursAdjacentes.append(listeValeursAdjacentes);
            listeValeursAdjacentes.clear();
        }
        listeValeursAdjacentes.append(valeur);
        valeurPrecedente = valeur;
    }
    listesValeursAdjacentes.append(listeValeursAdjacentes);
    return listesValeursAdjacentes;
}

const QStringList listeSousElements(const QString& chaineElements, const QChar& sep)
{
    QStringList listeSousElements;
    QString elementCourant;
    int compteurParentheses = 0;
    const int nombreChaineElements = chaineElements.count();
    for (int itChaineElements = 0; itChaineElements < nombreChaineElements; itChaineElements++)
    {
        const QChar& caractereCourant = chaineElements.at(itChaineElements);
        if (caractereCourant == '(')
        {
            compteurParentheses++;
        }
        else if (caractereCourant == ')')
        {
            compteurParentheses--;
        }
        if (caractereCourant == sep && compteurParentheses == 0)
        {
            listeSousElements.append(elementCourant);
            elementCourant.clear();
        }
        else if (!(caractereCourant == '(' && compteurParentheses == 1)
                && !(caractereCourant == ')' && compteurParentheses == 0))
        {
            elementCourant += caractereCourant;
        }
    }
    listeSousElements.append(elementCourant);
    return listeSousElements;
}

void interpolationNumerique(const double& x1, const double& y1, const double& x2, const double& y2,
        const double& x, double& y)
{
    const double pente = (x1 != x2) ? ((y2 - y1) / (x2 - x1)) : (y2 - y1);
    y = pente * (x - x1) + y1;
}

void interpolationNumerique(const Point& point1, const Point& point2, Point& point)
{
    const double p1px = point1.getPointPixelX();
    const double p1py = point1.getPointPixelY();
    const double p2px = point2.getPointPixelX();
    const double p2py = point2.getPointPixelY();
    const double p1rx = point1.getPointReelX();
    const double p1ry = point1.getPointReelY();
    const double p2rx = point2.getPointReelX();
    const double p2ry = point2.getPointReelY();

    const double ppx = point.getPointPixelX();
    const double prx = point.getPointReelX();
    double ppy = 0.0;
    double pry = 0.0;
    interpolationNumerique(p1px, p1py, p2px, p2py, ppx, ppy);
    interpolationNumerique(p1rx, p1ry, p2rx, p2ry, prx, pry);
    point.setPointPixelY(static_cast<int>(round(ppy)));
    point.setPointReelY(pry);
}

const QList<Point> interpolationNumerique(const QList<Point>& listeDePoints, const double& pas)
{
    QList<Point> listeDePointsInterpoles;
    const int nombreDePoints = listeDePoints.count();
    if (nombreDePoints > 0 && pas > 0.0)
    {
        const double borneInferieure = listeDePoints.at(0).getPointReelX();
        const double borneSuperieure = listeDePoints.at(nombreDePoints - 1).getPointReelX();
        const double xMinimal = floor(borneInferieure / pas) * pas;
        const double xMaximal = ceil(borneSuperieure / pas) * pas;
        const int nombreDePointsInterpoles = static_cast<int>(round((xMaximal - xMinimal) / pas))
                + 1;
        for (int itPas = 0; itPas < nombreDePointsInterpoles; itPas++)
        {
            const double xInterpole = xMinimal + (itPas * pas);
            Point pointInterpole;
            Point pointPrecedent;
            Point pointSuivant;
            for (int itPoint = 0; itPoint < nombreDePoints; itPoint++)
            {
                const Point& pointReference = listeDePoints.at(itPoint);
                const double xReference = pointReference.getPointReelX();
                if (xReference <= xInterpole)
                {
                    pointPrecedent = pointReference;
                }
                if (xReference >= xInterpole)
                {
                    pointSuivant = pointReference;
                    break;
                }
            }
            if (pointPrecedent.getTypePoint() == Point::INDEFINI)
            {
                pointPrecedent = listeDePoints.at(0);
                pointSuivant = (nombreDePoints > 1) ? listeDePoints.at(1) : listeDePoints.at(0);
            }
            if (pointSuivant.getTypePoint() == Point::INDEFINI)
            {
                pointPrecedent =
                        (nombreDePoints > 1) ?
                                listeDePoints.at(nombreDePoints - 2) :
                                listeDePoints.at(nombreDePoints - 1);
                pointSuivant = listeDePoints.at(nombreDePoints - 1);
            }
            pointInterpole.setPointReelX(xInterpole);
            interpolationNumerique(pointPrecedent, pointSuivant, pointInterpole);
            listeDePointsInterpoles.append(pointInterpole);
        }
    }
    return listeDePointsInterpoles;
}

void genererImageTest()
{
    // Définition de l'image de test
    const int largeurImage = 640;
    const int hauteurImage = 480;
    const int largeurSpectre = 600;
    const int hauteurSpectre = 50;
    const int hauteurSpectreTeinte = 230;
    QImage imageTest = QImage(largeurImage, hauteurImage, QImage::Format_RGB32);

    // Fond blanc
    const QColor couleurBlanc = QColor(Qt::white);
    for (int x = 0; x < largeurImage; x++)
    {
        for (int y = 0; y < hauteurImage; y++)
        {
            imageTest.setPixel(x, y, couleurBlanc.rgb());
        }
    }

    // Spectre de gris
    QColor couleurGris = QColor(Qt::black);
    for (int x = 0; x < largeurSpectre; x++)
    {
        for (int y = 0; y < hauteurSpectre; y++)
        {
            const int valeurGris = static_cast<int>(round(x * (255.0 / largeurSpectre)));
            couleurGris.setRgb(valeurGris, valeurGris, valeurGris);
            imageTest.setPixel((x + 20), (y + 20), couleurGris.rgb());
        }
    }

    // Spectre de saturation
    QColor couleurSaturation = QColor(Qt::red);
    for (int x = 0; x < largeurSpectre; x++)
    {
        for (int y = 0; y < hauteurSpectre; y++)
        {
            const int valeurSaturation = static_cast<int>(round(x * (255.0 / largeurSpectre)));
            couleurSaturation = QColor::fromHsv(couleurSaturation.hue(), valeurSaturation, 255);
            imageTest.setPixel((x + 20), (y + 90), couleurSaturation.rgb());
        }
    }

    // Spectre de brillance
    QColor couleurBrillance = QColor(Qt::red);
    for (int x = 0; x < largeurSpectre; x++)
    {
        for (int y = 0; y < hauteurSpectre; y++)
        {
            const int valeurBrillance = static_cast<int>(round(x * (255.0 / largeurSpectre)));
            couleurBrillance = QColor::fromHsv(couleurBrillance.hue(), 255, valeurBrillance);
            imageTest.setPixel((x + 20), (y + 160), couleurBrillance.rgb());
        }
    }

    // Spectre de teinte
    QColor couleurTeinte = QColor(Qt::black);
    for (int x = 0; x < largeurSpectre; x++)
    {
        for (int y = 0; y < hauteurSpectreTeinte; y++)
        {
            const int valeurTeinte = static_cast<int>(round(x * (360.0 / largeurSpectre)));
            couleurTeinte = QColor::fromHsv(valeurTeinte, 255, 255);
            imageTest.setPixel((x + 20), (y + 230), couleurTeinte.rgb());
        }
    }

    // Ecriture de l'image
    imageTest.save("ImageTest.png");
}

void testerConversionNoirEtBlanc(const int& seuilNoirEtBlanc)
{
    genererImageTest();
    Image imageTest = Image(QImage("ImageTest.png"), QImage());
    imageTest.convertirImageNoirEtBlanc(seuilNoirEtBlanc);
    imageTest.getImageConvertie().save("ImageTestConversionNoirEtBlanc.png");
}

void testerConversionNiveauxDeGris(const int& nombreNiveauxDeGris)
{
    genererImageTest();
    Image imageTest = Image(QImage("ImageTest.png"), QImage());
    imageTest.convertirImageNiveauxDeGris(nombreNiveauxDeGris);
    imageTest.getImageConvertie().save("ImageTestConversionNiveauxDeGris.png");
}

void testerConversionTeintesSaturees(const int& nombreNiveauxDeGris,
        const int& nombreTeintesSaturees, const int& seuilSaturation)
{
    genererImageTest();
    Image imageTest = Image(QImage("ImageTest.png"), QImage());
    imageTest.convertirImageTeintesSaturees(nombreNiveauxDeGris, nombreTeintesSaturees,
            seuilSaturation);
    imageTest.getImageConvertie().save("ImageTestConversionTeintesSaturees.png");
}
