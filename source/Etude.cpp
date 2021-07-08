//==============================================================================
// Name        : Etude.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Source file of the Etude class
//==============================================================================

#include "Etude.h"
#include "Outils.h"
#include "ParametresAffichage.h"
#include "ParametresAxe.h"
#include "ParametresConversion.h"
#include "ParametresExport.h"
#include "ParametresFichiers.h"
#include "ParametresRecherche.h"
#include <cmath>
#include <QColor>
#include <QFile>
#include <QImage>
#include <QIODevice>
#include <QMap>
#include <QPointF>
#include <QTextStream>

Etude::Etude()
{
    this->clear();
}

Etude::Etude(const Image& image, const Repere& repere, const QList<Point>& listeDePoints,
        const Parametres& parametres) :
        Etude()
{
    this->set(image, repere, listeDePoints, parametres);
}

Etude::Etude(const Etude& etude) :
        Etude()
{
    this->copy(etude);
}

Etude::~Etude()
{
}

Etude& Etude::operator=(const Etude& etude)
{
    this->copy(etude);
    return *this;
}

bool Etude::operator==(const Etude& etude) const
{
    return this->equals(etude);
}

bool Etude::operator!=(const Etude& etude) const
{
    return !this->equals(etude);
}

const Image& Etude::getImage() const
{
    return this->image;
}

const Repere& Etude::getRepere() const
{
    return this->repere;
}

const QList<Point>& Etude::getListeDePoints() const
{
    return this->listeDePoints;
}

const Parametres& Etude::getParametres() const
{
    return this->parametres;
}

void Etude::setImage(const Image& image)
{
    this->image = image;
}

void Etude::setRepere(const Repere& repere)
{
    this->repere = repere;
}

void Etude::setListeDePoints(const QList<Point>& listeDePoints)
{
    this->listeDePoints = listeDePoints;
}

void Etude::setParametres(const Parametres& parametres)
{
    this->parametres = parametres;
}

void Etude::clear()
{
    this->set(Image(), Repere(), QList<Point>(), Parametres());
}

void Etude::set(const Image& image, const Repere& repere, const QList<Point>& listeDePoints,
        const Parametres& parametres)
{
    this->setImage(image);
    this->setRepere(repere);
    this->setListeDePoints(listeDePoints);
    this->setParametres(parametres);
}

void Etude::copy(const Etude& etude)
{
    this->set(etude.getImage(), etude.getRepere(), etude.getListeDePoints(), etude.getParametres());
}

bool Etude::equals(const Etude& etude) const
{
    if (!this->getImage().equals(etude.getImage()))
        return false;
    if (!this->getRepere().equals(etude.getRepere()))
        return false;
    if (this->getListeDePoints() != etude.getListeDePoints())
        return false;
    if (!this->getParametres().equals(etude.getParametres()))
        return false;
    return true;
}

void Etude::fromString(const QString& fromString, const QChar& sep)
{
    // TODO void Etude::fromString(const QString& fromString, const QChar& sep)
    Q_UNUSED(fromString);
    Q_UNUSED(sep);
}

const QString Etude::toString(const QChar& sep) const
{
    QString toString;
    const QList<Point>& listeDePoints = this->getListeDePoints();
    const int nombreDePoints = listeDePoints.count();
    toString += QString("(%1)").arg(this->getImage().toString(sep)) + sep;
    toString += QString("(%1)").arg(this->getRepere().toString(sep)) + sep;
    toString += QString("[");
    for (int itPoint = 0; itPoint < nombreDePoints; itPoint++)
    {
        const Point& pointCourant = listeDePoints.at(itPoint);
        toString += QString("(%1)").arg(pointCourant.toString(sep));
        if (itPoint < (nombreDePoints - 1))
        {
            toString += sep;
        }
    }
    toString += QString("]") + sep;
    toString += QString("(%1)").arg(this->getParametres().toString(sep));
    return toString;
}

const QList<Courbe> Etude::getListeDeCourbes() const
{
    QList<Courbe> listeDeCourbes;
    QList<Point> listeDePointsCourbe;
    const QList<Point>& listeDePoints = this->getListeDePoints();
    const int nombreDePoints = listeDePoints.count();
    for (int itPoint = 0; itPoint < nombreDePoints; itPoint++)
    {
        const Point& pointCourant = listeDePoints.at(itPoint);
        const int& typePointCourant = pointCourant.getTypePoint();
        if (typePointCourant == Point::COURBE_DEBUT)
        {
            listeDePointsCourbe.clear();
            listeDePointsCourbe.append(pointCourant);
        }
        else if (typePointCourant == Point::COURBE)
        {
            listeDePointsCourbe.append(pointCourant);
        }
        else if (typePointCourant == Point::COURBE_FIN)
        {
            listeDePointsCourbe.append(pointCourant);
            listeDeCourbes.append(listeDePointsCourbe);
        }
    }
    return listeDeCourbes;
}

const QList<Point> Etude::getListeDePointsManuels() const
{
    QList<Point> listeDePointsManuels;
    const QList<Point>& listeDePoints = this->getListeDePoints();
    const int nombreDePoints = listeDePoints.count();
    for (int itPoint = 0; itPoint < nombreDePoints; itPoint++)
    {
        const Point& pointCourant = listeDePoints.at(itPoint);
        const int& typePointCourant = pointCourant.getTypePoint();
        if (typePointCourant == Point::MANUEL)
        {
            listeDePointsManuels.append(pointCourant);
        }
    }
    return listeDePointsManuels;
}

const ParametresGraphique Etude::getParametresGraphiques() const
{
    ParametresGraphique parametresGraphiques;
    ParametresAxe parametresAxeHorizontal = parametresGraphiques.getParametresAxeHorizontal();
    ParametresAxe parametresAxeVertical = parametresGraphiques.getParametresAxeVertical();
    const QList<Point>& listeDePoints = this->getListeDePoints();
    const int nombreDePoints = listeDePoints.count();
    for (int itPoint = 0; itPoint < nombreDePoints; itPoint++)
    {
        const Point& pointCourant = listeDePoints.at(itPoint);
        const double& pointReelXCourant = pointCourant.getPointReelX();
        const double& pointReelYCourant = pointCourant.getPointReelY();
        if (pointReelXCourant < parametresAxeHorizontal.getBorneInferieure() || itPoint == 0)
        {
            parametresAxeHorizontal.setBorneInferieure(pointReelXCourant);
        }
        if (pointReelXCourant > parametresAxeHorizontal.getBorneSuperieure() || itPoint == 0)
        {
            parametresAxeHorizontal.setBorneSuperieure(pointReelXCourant);
        }
        if (pointReelYCourant < parametresAxeVertical.getBorneInferieure() || itPoint == 0)
        {
            parametresAxeVertical.setBorneInferieure(pointReelYCourant);
        }
        if (pointReelYCourant > parametresAxeVertical.getBorneSuperieure() || itPoint == 0)
        {
            parametresAxeVertical.setBorneSuperieure(pointReelYCourant);
        }
    }
    parametresAxeHorizontal.ajuster();
    parametresAxeVertical.ajuster();
    parametresGraphiques.setParametresAxeHorizontal(parametresAxeHorizontal);
    parametresGraphiques.setParametresAxeVertical(parametresAxeVertical);
    return parametresGraphiques;
}

bool Etude::chargerEtude(const QString& cheminFichierEtude)
{
    QFile fichierEtude(cheminFichierEtude);
    if (!fichierEtude.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    const QChar separateur = ';';
    QTextStream fluxEntree(&fichierEtude);
    while (!fluxEntree.atEnd())
    {
        QString ligneEntree = fluxEntree.readLine();
        if (ligneEntree == "[PARAMETRES]")
        {
            ligneEntree = fluxEntree.readLine();
            Parametres parametres = this->getParametres();
            parametres.fromString(ligneEntree, separateur);
            this->setParametres(parametres);
            const ParametresFichiers& parametresFichier = parametres.getParametresFichiers();
            Image image = this->getImage();
            image.setImageSource(QImage(parametresFichier.getCheminFichierImageSource()));
            this->setImage(image);
            this->restaurerImage();
            this->convertirImage();
        }
        else if (ligneEntree == "[REPERE]")
        {
            ligneEntree = fluxEntree.readLine();
            Repere repere = this->getRepere();
            repere.fromString(ligneEntree, separateur);
            this->setRepere(repere);
        }
        else if (ligneEntree == "[POINTS]")
        {
            QList<Point> listeDePoints;
            while (!fluxEntree.atEnd())
            {
                ligneEntree = fluxEntree.readLine();
                Point point;
                point.fromString(ligneEntree, separateur);
                listeDePoints.append(point);
            }
            this->setListeDePoints(listeDePoints);
        }
    }
    return true;
}

bool Etude::sauverEtude(const QString& cheminFichierEtude)
{
    Parametres parametres = this->getParametres();
    ParametresFichiers parametresFichiers = parametres.getParametresFichiers();
    parametresFichiers.setCheminFichierEtude(cheminFichierEtude);
    parametres.setParametresFichiers(parametresFichiers);
    this->setParametres(parametres);

    QFile fichierEtude(cheminFichierEtude);
    if (!fichierEtude.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    const QChar separateur = ';';
    QTextStream fluxSortie(&fichierEtude);
    const QList<Point>& listeDePoints = this->getListeDePoints();
    const int nombreDePoints = listeDePoints.count();
    fluxSortie << "[PARAMETRES]" << endl;
    fluxSortie << this->getParametres().toString(separateur) << endl;
    fluxSortie << "[REPERE]" << endl;
    fluxSortie << this->getRepere().toString(separateur) << endl;
    fluxSortie << "[POINTS]" << endl;
    for (int itPoint = 0; itPoint < nombreDePoints; itPoint++)
    {
        const Point& pointCourant = listeDePoints.at(itPoint);
        fluxSortie << pointCourant.toString(separateur) << endl;
    }
    return true;
}

bool Etude::chargerParametres(const QString& cheminFichierParametres)
{
    QFile fichierParametres(cheminFichierParametres);
    if (!fichierParametres.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    const QChar separateur = ';';
    QTextStream fluxEntree(&fichierParametres);
    while (!fluxEntree.atEnd())
    {
        QString ligneEntree = fluxEntree.readLine();
        if (ligneEntree == "[PARAMETRES_AFFICHAGE]")
        {
            ligneEntree = fluxEntree.readLine();
            Parametres parametres = this->getParametres();
            ParametresAffichage parametresAffichage = parametres.getParametresAffichage();
            parametresAffichage.fromString(ligneEntree, separateur);
            parametres.setParametresAffichage(parametresAffichage);
            this->setParametres(parametres);
        }
        else if (ligneEntree == "[PARAMETRES_CONVERSION]")
        {
            ligneEntree = fluxEntree.readLine();
            Parametres parametres = this->getParametres();
            ParametresConversion parametresConversion = parametres.getParametresConversion();
            parametresConversion.fromString(ligneEntree, separateur);
            parametres.setParametresConversion(parametresConversion);
            this->setParametres(parametres);
            this->restaurerImage();
            this->convertirImage();
        }
        else if (ligneEntree == "[PARAMETRES_RECHERCHE]")
        {
            ligneEntree = fluxEntree.readLine();
            Parametres parametres = this->getParametres();
            ParametresRecherche parametresRecherche = parametres.getParametresRecherche();
            parametresRecherche.fromString(ligneEntree, separateur);
            parametres.setParametresRecherche(parametresRecherche);
            this->setParametres(parametres);
        }
        else if (ligneEntree == "[PARAMETRES_EXPORT]")
        {
            ligneEntree = fluxEntree.readLine();
            Parametres parametres = this->getParametres();
            ParametresExport parametresExport = parametres.getParametresExport();
            parametresExport.fromString(ligneEntree, separateur);
            parametres.setParametresExport(parametresExport);
            this->setParametres(parametres);
        }
    }
    return true;
}

bool Etude::sauverParametres(const QString& cheminFichierParametres)
{
    Parametres parametres = this->getParametres();
    ParametresFichiers parametresFichiers = parametres.getParametresFichiers();
    parametresFichiers.setCheminFichierParametres(cheminFichierParametres);
    parametres.setParametresFichiers(parametresFichiers);
    this->setParametres(parametres);

    QFile fichierParametres(cheminFichierParametres);
    if (!fichierParametres.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    const QChar separateur = ';';
    QTextStream fluxSortie(&fichierParametres);
    fluxSortie << "[PARAMETRES_AFFICHAGE]" << endl;
    fluxSortie << this->getParametres().getParametresAffichage().toString(separateur) << endl;
    fluxSortie << "[PARAMETRES_CONVERSION]" << endl;
    fluxSortie << this->getParametres().getParametresConversion().toString(separateur) << endl;
    fluxSortie << "[PARAMETRES_RECHERCHE]" << endl;
    fluxSortie << this->getParametres().getParametresRecherche().toString(separateur) << endl;
    fluxSortie << "[PARAMETRES_EXPORT]" << endl;
    fluxSortie << this->getParametres().getParametresExport().toString(separateur) << endl;
    return true;
}

bool Etude::exporterImageConvertie(const QString& cheminFichierImageConvertie)
{
    Parametres parametres = this->getParametres();
    ParametresFichiers parametresFichiers = parametres.getParametresFichiers();
    parametresFichiers.setCheminFichierImageConvertie(cheminFichierImageConvertie);
    parametres.setParametresFichiers(parametresFichiers);
    this->setParametres(parametres);

    QFile fichierImageConvertie(cheminFichierImageConvertie);
    if (!fichierImageConvertie.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    this->getImage().getImageConvertie().save(cheminFichierImageConvertie);
    return true;
}

bool Etude::exporterListeDePoints(const QString& cheminFichierExport)
{
    Parametres parametres = this->getParametres();
    ParametresFichiers parametresFichiers = parametres.getParametresFichiers();
    parametresFichiers.setCheminFichierExport(cheminFichierExport);
    parametres.setParametresFichiers(parametresFichiers);
    this->setParametres(parametres);

    QFile fichierExport(cheminFichierExport);
    if (!fichierExport.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    const ParametresExport& parametresExport = parametres.getParametresExport();
    const char formatNotationNombresCaractere =
            parametresExport.getFormatNotationNombresCaractere();
    const int& nombreChiffresSignificatifs = parametresExport.getNombreChiffresSignificatifs();
    const char& caractereSeparation = parametresExport.getCaractereSeparation();
    const char& caractereSeparateurDecimal = parametresExport.getCaractereSeparateurDecimal();
    const double& seuilInterpolationNumerique = parametresExport.getSeuilInterpolationNumerique();

    QTextStream fluxSortie(&fichierExport);
    const QList<Courbe> listeDeCourbes = this->getListeDeCourbes();
    const QList<Point> listeDePointsManuels = this->getListeDePointsManuels();
    const int nombreDeCourbes = listeDeCourbes.count();
    const int nombreDePointsManuels = listeDePointsManuels.count();
    for (int itCourbe = 0; itCourbe < nombreDeCourbes; itCourbe++)
    {
        const Courbe& listeDePointsCourbe = listeDeCourbes.at(itCourbe);
        const int nombreDePointsCourbe = listeDePointsCourbe.count();
        if (seuilInterpolationNumerique == 0.0)
        {
            for (int itPointCourbe = 0; itPointCourbe < nombreDePointsCourbe; itPointCourbe++)
            {
                const Point& pointCourbe = listeDePointsCourbe.at(itPointCourbe);
                fluxSortie
                        << QString::number(pointCourbe.getPointReelX(),
                                formatNotationNombresCaractere, nombreChiffresSignificatifs).replace(
                                '.', caractereSeparateurDecimal) << caractereSeparation
                        << QString::number(pointCourbe.getPointReelY(),
                                formatNotationNombresCaractere, nombreChiffresSignificatifs).replace(
                                '.', caractereSeparateurDecimal) << endl;
            }
        }
        else
        {
            const Courbe listeDePointsCourbeInterpoles = interpolationNumerique(listeDePointsCourbe,
                    seuilInterpolationNumerique);
            const int nombreDePointsCourbeInterpoles = listeDePointsCourbeInterpoles.count();
            for (int itPointCourbeInterpole = 0;
                    itPointCourbeInterpole < nombreDePointsCourbeInterpoles;
                    itPointCourbeInterpole++)
            {
                const Point& pointCourbeInterpole = listeDePointsCourbeInterpoles.at(
                        itPointCourbeInterpole);
                fluxSortie
                        << QString::number(pointCourbeInterpole.getPointReelX(),
                                formatNotationNombresCaractere, nombreChiffresSignificatifs).replace(
                                '.', caractereSeparateurDecimal) << caractereSeparation
                        << QString::number(pointCourbeInterpole.getPointReelY(),
                                formatNotationNombresCaractere, nombreChiffresSignificatifs).replace(
                                '.', caractereSeparateurDecimal) << endl;
            }
        }
    }
    for (int itPointManuel = 0; itPointManuel < nombreDePointsManuels; itPointManuel++)
    {
        const Point& pointManuel = listeDePointsManuels.at(itPointManuel);
        fluxSortie
                << QString::number(pointManuel.getPointReelX(), formatNotationNombresCaractere,
                        nombreChiffresSignificatifs).replace('.', caractereSeparateurDecimal)
                << caractereSeparation
                << QString::number(pointManuel.getPointReelY(), formatNotationNombresCaractere,
                        nombreChiffresSignificatifs).replace('.', caractereSeparateurDecimal)
                << endl;
    }
    // TODO Interpolation des points manuels (point le plus proche) ?
    return true;
}

void Etude::restaurerImage()
{
    Image image = this->getImage();
    image.restaurerImage();
    this->setImage(image);
}

void Etude::convertirImage()
{
    const Parametres& parametres = this->getParametres();
    const ParametresConversion& parametresConversion = parametres.getParametresConversion();
    const int& methodeConversion = parametresConversion.getMethodeConversion();

    Image image = this->getImage();
    if (methodeConversion == ParametresConversion::BRUTE)
    {
        image.restaurerImage();
    }
    else if (methodeConversion == ParametresConversion::NOIR_ET_BLANC)
    {
        image.convertirImageNoirEtBlanc(parametresConversion.getSeuilNoirEtBlanc());
    }
    else if (methodeConversion == ParametresConversion::NIVEAUX_DE_GRIS)
    {
        image.convertirImageNiveauxDeGris(parametresConversion.getNombreNiveauxDeGris());
    }
    else if (methodeConversion == ParametresConversion::TEINTES_SATUREES)
    {
        image.convertirImageTeintesSaturees(parametresConversion.getNombreNiveauxDeGris(),
                parametresConversion.getNombreTeintesSaturees(),
                parametresConversion.getSeuilSaturation());
    }
    this->setImage(image);
}

const QList<Courbe> Etude::rechercherCourbes(const QPoint& pointPixelDepart,
        const QPoint& pointPixelArrivee)
{
    const QList<QPoint> listeDePointsCourbes = this->rechercherPointsCourbes(pointPixelDepart,
            pointPixelArrivee);
    const QList<Courbe> listeDeCourbes = this->construireCourbes(listeDePointsCourbes);
    return listeDeCourbes;
}

const QList<QPoint> Etude::rechercherPointsCourbes(const QPoint& pointPixelDepart,
        const QPoint& pointPixelArrivee)
{
    this->listeDePointsDeRecherche.clear();
    this->pointPixelDepart = pointPixelDepart;
    this->pointPixelArrivee = pointPixelArrivee;
    this->listeDePointsDeRecherche.append(pointPixelDepart);
    const Image& image = this->getImage();
    const QRgb couleurReference = image.recupererCouleurPixel(pointPixelDepart);
    this->rechercherPoints(pointPixelDepart, couleurReference);
    const QList<QPoint> listeDePointsCourbes = this->filtrerPointsCourbes(
            this->listeDePointsDeRecherche, this->pointPixelDepart, this->pointPixelArrivee);
    return listeDePointsCourbes;
}

void Etude::rechercherPoints(const QPoint& pointPixel, const QRgb& couleurReference)
{
    const QList<QPoint> listeDePointsProches = this->recupererPointsProches(pointPixel);
    const int nombreDePointsProches = listeDePointsProches.count();
    const Image& image = this->getImage();
    const Parametres& parametres = this->getParametres();
    const ParametresRecherche& parametresRecherche = parametres.getParametresRecherche();
    const int& seuilToleranceNiveauxDeGris = parametresRecherche.getSeuilToleranceNiveauxDeGris();
    const int& seuilToleranceTeintesSaturees = static_cast<int>(round(
            parametresRecherche.getSeuilToleranceTeintesSaturees() / 2.0));
    for (int itPointProche = 0; itPointProche < nombreDePointsProches; itPointProche++)
    {
        const QPoint& pointCourant = listeDePointsProches.at(itPointProche);
        if (this->listeDePointsDeRecherche.contains(pointCourant))
            continue;
        const QRgb couleurCourante = image.recupererCouleurPixel(pointCourant);
        if (this->verifierToleranceNiveauxDeGris(couleurCourante, couleurReference,
                seuilToleranceNiveauxDeGris) != NIVEAU_DE_GRIS_COMPATIBLE)
            continue;
        if (this->verifierToleranceTeintesSaturees(couleurCourante, couleurReference,
                seuilToleranceTeintesSaturees) != TEINTE_SATUREE_COMPATIBLE)
            continue;
        this->listeDePointsDeRecherche.append(pointCourant);
        this->rechercherPoints(pointCourant, couleurReference);
    }
}

const QList<QPoint> Etude::recupererPointsProches(const QPoint& pointPixel) const
{
    QList<QPoint> listeDePointsProches;
    const Image& image = this->getImage();
    const int xMinimal = this->pointPixelDepart.x();
    const int xMaximal = this->pointPixelArrivee.x();
    const int xReference = pointPixel.x();
    const int yReference = pointPixel.y();
    const int xPrecedent = ((xReference - 1) > xMinimal) ? (xReference - 1) : xMinimal;
    const int xSuivant = ((xReference + 1) < xMaximal) ? (xReference + 1) : xMaximal;
    const int yPrecedent = yReference - 1;
    const int ySuivant = yReference + 1;
    for (int x = xPrecedent; x <= xSuivant; x++)
    {
        for (int y = yPrecedent; y <= ySuivant; y++)
        {
            const QPoint pointCourant(x, y);
            if (x == xReference && y == yReference)
                continue;
            if (!image.verifierPresencePixel(pointCourant))
                continue;
            listeDePointsProches.append(pointCourant);
        }
    }
    return listeDePointsProches;
}

int Etude::verifierToleranceNiveauxDeGris(const QRgb& couleurCourante, const QRgb& couleurReference,
        const int& seuilToleranceNiveauxDeGris) const
{
    const int niveauDeGrisCouleurCourante = qGray(couleurCourante);
    const int niveauDeGrisCouleurReference = qGray(couleurReference);
    const int seuilMinimalNiveauDeGris = niveauDeGrisCouleurReference - seuilToleranceNiveauxDeGris;
    const int seuilMaximalNiveauDeGris = niveauDeGrisCouleurReference + seuilToleranceNiveauxDeGris;
    if (niveauDeGrisCouleurCourante < seuilMinimalNiveauDeGris)
        return NIVEAU_DE_GRIS_INFERIEUR;
    else if (niveauDeGrisCouleurCourante > seuilMaximalNiveauDeGris)
        return NIVEAU_DE_GRIS_SUPERIEUR;
    return NIVEAU_DE_GRIS_COMPATIBLE;
}

int Etude::verifierToleranceTeintesSaturees(const QRgb& couleurCourante,
        const QRgb& couleurReference, const int& seuilToleranceTeintesSaturees) const
{
    const int teinteCouleurCourante = QColor(couleurCourante).hue();
    const int teinteCouleurReference = QColor(couleurReference).hue();
    const int seuilMinimalTeinteSaturee = (teinteCouleurReference - seuilToleranceTeintesSaturees
            + 360) % 360;
    const int seuilMaximalTeinteSaturee = (teinteCouleurReference + seuilToleranceTeintesSaturees
            + 360) % 360;
    const bool seuilsInverses = (seuilMinimalTeinteSaturee > seuilMaximalTeinteSaturee);
    if ((teinteCouleurCourante == -1 && teinteCouleurReference != -1)
            || (teinteCouleurCourante != -1 && teinteCouleurReference == -1))
        return TEINTE_SATUREE_INCOMPATIBLE;
    else if (seuilToleranceTeintesSaturees >= 180)
        return TEINTE_SATUREE_COMPATIBLE;
    else if (teinteCouleurCourante < seuilMinimalTeinteSaturee
            && (!seuilsInverses || (seuilsInverses && teinteCouleurCourante >= 180)))
        return TEINTE_SATUREE_INFERIEURE;
    else if (teinteCouleurCourante > seuilMaximalTeinteSaturee
            && (!seuilsInverses || (seuilsInverses && teinteCouleurCourante <= 180)))
        return TEINTE_SATUREE_SUPERIEURE;
    return TEINTE_SATUREE_COMPATIBLE;
}

const QList<QPoint> Etude::filtrerPointsCourbes(const QList<QPoint>& listeDePoints,
        const QPoint& pointPixelDepart, const QPoint& pointPixelArrivee)
{
    if (!listeDePoints.contains(pointPixelDepart))
        return QList<QPoint>();
    if (!listeDePoints.contains(pointPixelArrivee))
        return QList<QPoint>();

    QList<QPoint> listeDePointsTries = listeDePoints;
    qSort(listeDePointsTries.begin(), listeDePointsTries.end(), lessThanQPoint);

    QMap<int, QList<int>> mapPointsRecherche;
    const int nombreDePointsDeRecherche = listeDePointsTries.count();
    for (int itPointRecherche = 0; itPointRecherche < nombreDePointsDeRecherche; itPointRecherche++)
    {
        const QPoint& pointRecherche = listeDePointsTries.at(itPointRecherche);
        mapPointsRecherche[pointRecherche.x()].append(pointRecherche.y());
    }

    const int xMinimal = pointPixelDepart.x();
    const int xMaximal = pointPixelArrivee.x();
    for (int x = (xMinimal + 1); x <= xMaximal; x++)
    {
        const QList<QList<int>> listeValeursAdjacentes = listesValeursAdjacentes(
                mapPointsRecherche[x]);
        const int nombreValeursAdjacentes = listeValeursAdjacentes.count();
        QList<int> valeursAdjacentesRetenues = listeValeursAdjacentes.at(0);
        if (listeValeursAdjacentes.count() > 1)
        {
            const double valeurMoyennePrecedente = getValeurMoyenne(mapPointsRecherche[x - 1]);
            for (int itValeursAdjacentes = 0; itValeursAdjacentes < nombreValeursAdjacentes;
                    itValeursAdjacentes++)
            {
                const QList<int>& valeursAdjacentes = listeValeursAdjacentes.at(
                        itValeursAdjacentes);
                const double valeurMoyenne = getValeurMoyenne(valeursAdjacentes);
                const double valeurMoyenneRetenue = getValeurMoyenne(valeursAdjacentesRetenues);
                if (fabs(valeurMoyenne - valeurMoyennePrecedente)
                        < fabs(valeurMoyenneRetenue - valeurMoyennePrecedente))
                {
                    valeursAdjacentesRetenues = valeursAdjacentes;
                }
            }
        }
        mapPointsRecherche[x] = valeursAdjacentesRetenues;
    }

    QList<QPoint> listeDePointsFiltres;
    const Parametres& parametres = this->getParametres();
    const ParametresRecherche& parametresRecherche = parametres.getParametresRecherche();
    if (parametresRecherche.getSelectionValeursMoyennes())
    {
        for (int x = xMinimal; x <= xMaximal; x++)
        {
            const int y = getValeurMoyenne(mapPointsRecherche[x]);
            listeDePointsFiltres.append(QPoint(x, y));
        }
    }
    if (parametresRecherche.getSelectionValeursMinimales())
    {
        for (int x = xMinimal; x <= xMaximal; x++)
        {
            const int y = getValeurMinimale(mapPointsRecherche[x]);
            listeDePointsFiltres.append(QPoint(x, y));
        }
    }
    if (parametresRecherche.getSelectionValeursMaximales())
    {
        for (int x = xMinimal; x <= xMaximal; x++)
        {
            const int y = getValeurMaximale(mapPointsRecherche[x]);
            listeDePointsFiltres.append(QPoint(x, y));
        }
    }
    return listeDePointsFiltres;
}

const QList<Courbe> Etude::construireCourbes(const QList<QPoint>& listeDePoints)
{
    const Repere& repere = this->getRepere();
    const Parametres& parametres = this->getParametres();
    const ParametresRecherche& parametresRecherche = parametres.getParametresRecherche();
    const bool& selectionValeursMoyennes = parametresRecherche.getSelectionValeursMoyennes();
    const bool& selectionValeursMinimales = parametresRecherche.getSelectionValeursMinimales();
    const bool& selectionValeursMaximales = parametresRecherche.getSelectionValeursMaximales();
    const int nombreDeCourbes = selectionValeursMoyennes + selectionValeursMinimales
            + selectionValeursMaximales;
    const int nombreDePoints = listeDePoints.count();
    const int nombreDePointsCourbe = (nombreDeCourbes > 0) ? (nombreDePoints / nombreDeCourbes) : 0;

    QList<Courbe> listeDeCourbes;
    for (int itCourbe = 0; itCourbe < nombreDeCourbes; itCourbe++)
    {
        Courbe listeDePointsCourbe;
        const int decalagePointCourbe = itCourbe * nombreDePointsCourbe;
        for (int itPointCourbe = 0; itPointCourbe < nombreDePointsCourbe; itPointCourbe++)
        {
            const QPoint& pointCourbePixel = listeDePoints.at(itPointCourbe + decalagePointCourbe);
            Point pointCourbe = Point(pointCourbePixel, QPointF(),
                    (itPointCourbe == 0) ? Point::COURBE_DEBUT :
                    (itPointCourbe == (nombreDePointsCourbe - 1)) ?
                            Point::COURBE_FIN : Point::COURBE);
            repere.pixelVersReel(pointCourbe);
            listeDePointsCourbe.append(pointCourbe);
        }
        listeDeCourbes.append(listeDePointsCourbe);
    }
    return listeDeCourbes;
}
