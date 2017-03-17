//==============================================================================
// Name        : Image.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.3 (17/03/2017)
// Description : Source file of the Image class
//==============================================================================

#include "Image.h"
#include "ParametresConversion.h"
#include <QByteArray>
#include <QColor>

Image::Image()
{
    this->clear();
}

Image::Image(const QImage& imageSource, const QImage& imageConvertie) :
        Image()
{
    this->set(imageSource, imageConvertie);
}

Image::Image(const Image& image) :
        Image()
{
    this->copy(image);
}

Image::~Image()
{
}

const QImage& Image::getImageSource() const
{
    return this->imageSource;
}

const QImage& Image::getImageConvertie() const
{
    return this->imageConvertie;
}

void Image::setImageSource(const QImage& imageSource)
{
    this->imageSource = imageSource;
}

void Image::setImageConvertie(const QImage& imageConvertie)
{
    this->imageConvertie = imageConvertie;
}

void Image::clear()
{
    this->set(QImage(), QImage());
}

void Image::set(const QImage& imageSource, const QImage& imageConvertie)
{
    this->setImageSource(imageSource);
    this->setImageConvertie(imageConvertie);
}

void Image::copy(const Image& image)
{
    this->set(image.getImageSource(), image.getImageConvertie());
}

bool Image::equals(const Image& image) const
{
    if (this->getImageSource() != image.getImageSource())
        return false;
    if (this->getImageConvertie() != image.getImageConvertie())
        return false;
    return true;
}

void Image::fromString(const QString& fromString, const char& sep)
{
    // TODO void Image::fromString(const QString& fromString, const char& sep)
    Q_UNUSED(fromString);
    Q_UNUSED(sep);
}

const QString Image::toString(const char& sep) const
{
    QString toString;
    const QImage& imageSource = this->getImageSource();
    const QImage& imageConvertie = this->getImageConvertie();
    toString += "(" + QByteArray((char*) imageSource.bits(), imageSource.numBytes()).toHex() + ")"
            + sep;
    toString += "(" + QByteArray((char*) imageConvertie.bits(), imageConvertie.numBytes()).toHex()
            + ")";
    return toString;
}

void Image::restaurerImage()
{
    this->setImageConvertie(this->getImageSource());
}

void Image::convertirImageNoirEtBlanc(const int& seuilNoirEtBlanc)
{
    this->convertirImage(ParametresConversion::NOIR_ET_BLANC, seuilNoirEtBlanc,
            ParametresConversion::nombreNiveauxDeGrisDefaut,
            ParametresConversion::nombreTeintesSatureesDefaut,
            ParametresConversion::seuilSaturationDefaut);
}

void Image::convertirImageNiveauxDeGris(const int& nombreNiveauxDeGris)
{
    this->convertirImage(ParametresConversion::NIVEAUX_DE_GRIS,
            ParametresConversion::seuilNoirEtBlancDefaut, nombreNiveauxDeGris,
            ParametresConversion::nombreTeintesSatureesDefaut,
            ParametresConversion::seuilSaturationDefaut);
}

void Image::convertirImageTeintesSaturees(const int& nombreNiveauxDeGris,
        const int& nombreTeintesSaturees, const int& seuilSaturation)
{
    this->convertirImage(ParametresConversion::TEINTES_SATUREES,
            ParametresConversion::seuilNoirEtBlancDefaut, nombreNiveauxDeGris,
            nombreTeintesSaturees, seuilSaturation);
}

bool Image::verifierPresencePixel(const QPoint& pointPixel) const
{
    const QImage& imageConvertie = this->getImageConvertie();
    const int largeurImage = imageConvertie.width();
    const int hauteurImage = imageConvertie.height();
    const int x = pointPixel.x();
    const int y = pointPixel.y();
    return (x >= 0 && x < largeurImage && y >= 0 && y < hauteurImage);
}

QRgb Image::recupererCouleurPixel(const QPoint& pointPixel) const
{
    const QImage& imageConvertie = this->getImageConvertie();
    const int x = pointPixel.x();
    const int y = pointPixel.y();
    return imageConvertie.pixel(x, y);
}

void Image::convertirImage(const int& methodeConversion, const int& seuilNoirEtBlanc,
        const int& nombreNiveauxDeGris, const int& nombreTeintesSaturees,
        const int& seuilSaturation)
{
    this->restaurerImage();
    QImage imageConvertie = this->getImageConvertie();
    const int largeurImage = imageConvertie.width();
    const int hauteurImage = imageConvertie.height();
    const double pasNiveauxDeGris = this->getPasNiveauxDeGris(nombreNiveauxDeGris);
    const double pasTeintesSaturees = this->getPasTeintesSaturees(nombreTeintesSaturees);
    const QList<QRgb> listeNiveauxDeGris = this->getListeNiveauxDeGris(nombreNiveauxDeGris);
    const QList<QRgb> listeTeintesSaturees = this->getListeTeintesSaturees(nombreTeintesSaturees);
    for (int x = 0; x < largeurImage; x++)
    {
        for (int y = 0; y < hauteurImage; y++)
        {
            QRgb couleurConvertie = imageConvertie.pixel(x, y);
            if (methodeConversion == ParametresConversion::NOIR_ET_BLANC)
            {
                couleurConvertie =
                        (qGray(couleurConvertie) <= seuilNoirEtBlanc) ?
                                QColor(Qt::black).rgb() : QColor(Qt::white).rgb();
            }
            else if (methodeConversion == ParametresConversion::NIVEAUX_DE_GRIS)
            {
                couleurConvertie = listeNiveauxDeGris.at(
                        (int) round((double) qGray(couleurConvertie) / pasNiveauxDeGris));
            }
            else if (methodeConversion == ParametresConversion::TEINTES_SATUREES)
            {
                const int teinteCouleurConvertie = QColor(couleurConvertie).hue();
                const int saturationCouleurConvertie = QColor(couleurConvertie).saturation();
                if (teinteCouleurConvertie == -1 || saturationCouleurConvertie <= seuilSaturation)
                {
                    couleurConvertie = listeNiveauxDeGris.at(
                            (int) round((double) qGray(couleurConvertie) / pasNiveauxDeGris));
                }
                else
                {
                    couleurConvertie = listeTeintesSaturees.at(
                            (int) round((double) teinteCouleurConvertie / pasTeintesSaturees)
                                    % nombreTeintesSaturees);
                }
            }
            imageConvertie.setPixel(x, y, couleurConvertie);
        }
    }
    this->setImageConvertie(imageConvertie);
}

double Image::getPasNiveauxDeGris(const int& nombreNiveauxDeGris) const
{
    return 255.0 / (double) (nombreNiveauxDeGris - 1);
}

double Image::getPasTeintesSaturees(const int& nombreTeintesSaturees) const
{
    return 360.0 / (double) nombreTeintesSaturees;
}

const QList<QRgb> Image::getListeNiveauxDeGris(const int& nombreNiveauxDeGris) const
{
    QList<QRgb> listeNiveauxDeGris;
    const double pasNiveauxDeGris = this->getPasNiveauxDeGris(nombreNiveauxDeGris);
    for (int itNiveauDeGris = 0; itNiveauDeGris < nombreNiveauxDeGris; itNiveauDeGris++)
    {
        const int valeurGris = (int) round((double) itNiveauDeGris * pasNiveauxDeGris);
        const QRgb niveauDeGris = QColor::fromRgb(valeurGris, valeurGris, valeurGris).rgb();
        listeNiveauxDeGris.append(niveauDeGris);
    }
    return listeNiveauxDeGris;
}

const QList<QRgb> Image::getListeTeintesSaturees(const int& nombreTeintesSaturees) const
{
    QList<QRgb> listeTeintesSaturees;
    const double pasTeintesSaturees = this->getPasTeintesSaturees(nombreTeintesSaturees);
    for (int itTeinteSaturee = 0; itTeinteSaturee < nombreTeintesSaturees; itTeinteSaturee++)
    {
        const int valeurTeinte = (int) round((double) itTeinteSaturee * pasTeintesSaturees);
        const QRgb teinteSaturee = QColor::fromHsv(valeurTeinte, 255, 255).rgb();
        listeTeintesSaturees.append(teinteSaturee);
    }
    return listeTeintesSaturees;
}
