//==============================================================================
// Name        : Image.h
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.0.0 (20/01/2017)
// Description : Header file of the Image class
//==============================================================================

#ifndef IMAGE_H_
#define IMAGE_H_

#include <QImage>
#include <QList>
#include <QPoint>
#include <QRgb>
#include <QString>

class Image
{
public:
    // Constructeurs et destructeurs
    Image();
    Image(const QImage& imageSource, const QImage& imageConvertie);
    Image(const Image& image);
    virtual ~Image();

    // Getters
    const QImage& getImageSource() const;
    const QImage& getImageConvertie() const;

    // Setters
    void setImageSource(const QImage& imageSource);
    void setImageConvertie(const QImage& imageConvertie);

    // Méthodes génériques
    void clear();
    void set(const QImage& imageSource, const QImage& imageConvertie);
    void copy(const Image& image);
    bool equals(const Image& image) const;
    void fromString(const QString& fromString, const char& sep);
    const QString toString(const char& sep) const;

    // Méthodes spécifiques
    void restaurerImage();
    void convertirImageNoirEtBlanc(const int& seuilNoirEtBlanc);
    void convertirImageNiveauxDeGris(const int& nombreNiveauxDeGris);
    void convertirImageTeintesSaturees(const int& nombreNiveauxDeGris,
            const int& nombreTeintesSaturees, const int& seuilSaturation);
    bool verifierPresencePixel(const QPoint& pointPixel) const;
    QRgb recupererCouleurPixel(const QPoint& pointPixel) const;

protected:
    // Méthodes spécifiques
    void convertirImage(const int& methodeConversion, const int& seuilNoirEtBlanc,
            const int& nombreNiveauxDeGris, const int& nombreTeintesSaturees,
            const int& seuilSaturation);
    double getPasNiveauxDeGris(const int& nombreNiveauxDeGris) const;
    double getPasTeintesSaturees(const int& nombreTeintesSaturees) const;
    const QList<QRgb> getListeNiveauxDeGris(const int& nombreNiveauxDeGris) const;
    const QList<QRgb> getListeTeintesSaturees(const int& nombreTeintesSaturees) const;

private:
    // Attributs de classe
    QImage imageSource;
    QImage imageConvertie;
};

#endif /* IMAGE_H_ */
