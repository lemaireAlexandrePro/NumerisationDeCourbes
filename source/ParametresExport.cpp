//==============================================================================
// Name        : ParametresExport.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Source file of the ParametresExport class
//==============================================================================

#include "ParametresExport.h"
#include "Outils.h"
#include <QStringList>

const int ParametresExport::formatNotationNombresDefaut = STANDARD;
const int ParametresExport::nombreChiffresSignificatifsDefaut = 6;
const char ParametresExport::caractereSeparationDefaut = '\t';
const char ParametresExport::caractereSeparateurDecimalDefaut = '.';
const double ParametresExport::seuilInterpolationNumeriqueDefaut = 0.0;

const QMap<int, char> ParametresExport::formatsNotationNombresCaractere = QMap<int, char>(
        std::map<int, char> { { STANDARD, 'f' }, { SCIENTIFIQUE, 'e' } });
const QMap<int, QString> ParametresExport::formatsNotationNombresTexte = QMap<int, QString>(
        std::map<int, QString> { { STANDARD, QString::fromUtf8("Standard") }, { SCIENTIFIQUE,
                QString::fromUtf8("Scientifique") } });
const QMap<char, int> ParametresExport::caracteresSeparationIndice = QMap<char, int>(
        std::map<char, int> { { ' ', ESPACE }, { '\t', TABULATION }, { ';', POINT_VIRGULE } });
const QMap<char, QString> ParametresExport::caracteresSeparationTexte = QMap<char, QString>(
        std::map<char, QString> { { ' ', QString::fromUtf8("Espace") }, { '\t', QString::fromUtf8(
                "Tabulation") }, { ';', QString::fromUtf8("Point-virgule") } });
const QMap<char, int> ParametresExport::caracteresSeparateurDecimalIndice = QMap<char, int>(
        std::map<char, int> { { '.', POINT }, { ',', VIRGULE } });
const QMap<char, QString> ParametresExport::caracteresSeparateurDecimalTexte = QMap<char, QString>(
        std::map<char, QString> { { '.', QString::fromUtf8("Point") }, { ',', QString::fromUtf8(
                "Virgule") } });

ParametresExport::ParametresExport() :
        formatNotationNombres(formatNotationNombresDefaut),
                nombreChiffresSignificatifs(nombreChiffresSignificatifsDefaut),
                caractereSeparation(caractereSeparationDefaut),
                caractereSeparateurDecimal(caractereSeparateurDecimalDefaut),
                seuilInterpolationNumerique(seuilInterpolationNumeriqueDefaut)
{
    this->clear();
}

ParametresExport::ParametresExport(const int& formatNotationNombres,
        const int& nombreChiffresSignificatifs, const char& caractereSeparation,
        const char& caractereSeparateurDecimal, const double& seuilInterpolationNumerique) :
        ParametresExport()
{
    this->set(formatNotationNombres, nombreChiffresSignificatifs, caractereSeparation,
            caractereSeparateurDecimal, seuilInterpolationNumerique);
}

ParametresExport::ParametresExport(const ParametresExport& parametresExport) :
        ParametresExport()
{
    this->copy(parametresExport);
}

ParametresExport::~ParametresExport()
{
}

ParametresExport& ParametresExport::operator=(const ParametresExport& parametresExport)
{
    this->copy(parametresExport);
    return *this;
}

bool ParametresExport::operator==(const ParametresExport& parametresExport) const
{
    return this->equals(parametresExport);
}

bool ParametresExport::operator!=(const ParametresExport& parametresExport) const
{
    return !this->equals(parametresExport);
}

const int& ParametresExport::getFormatNotationNombres() const
{
    return this->formatNotationNombres;
}

const int& ParametresExport::getNombreChiffresSignificatifs() const
{
    return this->nombreChiffresSignificatifs;
}

const char& ParametresExport::getCaractereSeparation() const
{
    return this->caractereSeparation;
}

const char& ParametresExport::getCaractereSeparateurDecimal() const
{
    return this->caractereSeparateurDecimal;
}

const double& ParametresExport::getSeuilInterpolationNumerique() const
{
    return this->seuilInterpolationNumerique;
}

void ParametresExport::setFormatNotationNombres(const int& formatNotationNombres)
{
    this->formatNotationNombres = formatNotationNombres;
}

void ParametresExport::setNombreChiffresSignificatifs(const int& nombreChiffresSignificatifs)
{
    this->nombreChiffresSignificatifs = nombreChiffresSignificatifs;
}

void ParametresExport::setCaractereSeparation(const char& caractereSeparation)
{
    this->caractereSeparation = caractereSeparation;
}

void ParametresExport::setCaractereSeparateurDecimal(const char& caractereSeparateurDecimal)
{
    this->caractereSeparateurDecimal = caractereSeparateurDecimal;
}

void ParametresExport::setSeuilInterpolationNumerique(const double& seuilInterpolationNumerique)
{
    this->seuilInterpolationNumerique = seuilInterpolationNumerique;
}

void ParametresExport::clear()
{
    this->set(formatNotationNombresDefaut, nombreChiffresSignificatifsDefaut,
            caractereSeparationDefaut, caractereSeparateurDecimalDefaut,
            seuilInterpolationNumeriqueDefaut);
}

void ParametresExport::set(const int& formatNotationNombres, const int& nombreChiffresSignificatifs,
        const char& caractereSeparation, const char& caractereSeparateurDecimal,
        const double& seuilInterpolationNumerique)
{
    this->setFormatNotationNombres(formatNotationNombres);
    this->setNombreChiffresSignificatifs(nombreChiffresSignificatifs);
    this->setCaractereSeparation(caractereSeparation);
    this->setCaractereSeparateurDecimal(caractereSeparateurDecimal);
    this->setSeuilInterpolationNumerique(seuilInterpolationNumerique);
}

void ParametresExport::copy(const ParametresExport& parametresExport)
{
    this->set(parametresExport.getFormatNotationNombres(),
            parametresExport.getNombreChiffresSignificatifs(),
            parametresExport.getCaractereSeparation(),
            parametresExport.getCaractereSeparateurDecimal(),
            parametresExport.getSeuilInterpolationNumerique());
}

bool ParametresExport::equals(const ParametresExport& parametresExport) const
{
    if (this->getFormatNotationNombres() != parametresExport.getFormatNotationNombres())
        return false;
    if (this->getNombreChiffresSignificatifs() != parametresExport.getNombreChiffresSignificatifs())
        return false;
    if (this->getCaractereSeparation() != parametresExport.getCaractereSeparation())
        return false;
    if (this->getCaractereSeparateurDecimal() != parametresExport.getCaractereSeparateurDecimal())
        return false;
    if (this->getSeuilInterpolationNumerique() != parametresExport.getSeuilInterpolationNumerique())
        return false;
    return true;
}

void ParametresExport::fromString(const QString& fromString, const QChar& sep)
{
    const QStringList fromStringList = listeSousElements(fromString, sep);
    this->setFormatNotationNombres(fromStringList.at(0).toInt());
    this->setNombreChiffresSignificatifs(fromStringList.at(1).toInt());
    this->setCaractereSeparation(fromStringList.at(2).at(1).toLatin1());
    this->setCaractereSeparateurDecimal(fromStringList.at(3).at(1).toLatin1());
    this->setSeuilInterpolationNumerique(fromStringList.at(4).toDouble());
}

const QString ParametresExport::toString(const QChar& sep) const
{
    QString toString;
    toString += QString::number(this->getFormatNotationNombres()) + sep;
    toString += QString::number(this->getNombreChiffresSignificatifs()) + sep;
    toString += "'" + QString(this->getCaractereSeparation()) + "'" + sep;
    toString += "'" + QString(this->getCaractereSeparateurDecimal()) + "'" + sep;
    toString += QString::number(this->getSeuilInterpolationNumerique());
    return toString;
}

char ParametresExport::getFormatNotationNombresCaractere() const
{
    return formatsNotationNombresCaractere.value(this->getFormatNotationNombres());
}

const QString ParametresExport::getFormatNotationNombresTexte() const
{
    return formatsNotationNombresTexte.value(this->getFormatNotationNombres());
}

int ParametresExport::getCaractereSeparationIndice() const
{
    return caracteresSeparationIndice.value(this->getCaractereSeparation());
}

const QString ParametresExport::getCaractereSeparationTexte() const
{
    return caracteresSeparationTexte.value(this->getCaractereSeparation());
}

int ParametresExport::getCaractereSeparateurDecimalIndice() const
{
    return caracteresSeparateurDecimalIndice.value(this->getCaractereSeparateurDecimal());
}

const QString ParametresExport::getCaractereSeparateurDecimalTexte() const
{
    return caracteresSeparateurDecimalTexte.value(this->getCaractereSeparateurDecimal());
}

void ParametresExport::setFormatNotationNombresCaractere(const char& formatNotationNombresCaractere)
{
    this->setFormatNotationNombres(
            formatsNotationNombresCaractere.key(formatNotationNombresCaractere));
}

void ParametresExport::setFormatNotationNombresTexte(const QString& formatNotationNombresTexte)
{
    this->setFormatNotationNombres(formatsNotationNombresTexte.key(formatNotationNombresTexte));
}

void ParametresExport::setCaractereSeparationIndice(const int& caractereSeparationIndice)
{
    this->setCaractereSeparation(caracteresSeparationIndice.key(caractereSeparationIndice));
}

void ParametresExport::setCaractereSeparationTexte(const QString& caractereSeparationTexte)
{
    this->setCaractereSeparation(caracteresSeparationTexte.key(caractereSeparationTexte));
}

void ParametresExport::setCaractereSeparateurDecimalIndice(
        const int& caractereSeparateurDecimalIndice)
{
    this->setCaractereSeparateurDecimal(
            caracteresSeparateurDecimalIndice.key(caractereSeparateurDecimalIndice));
}

void ParametresExport::setCaractereSeparateurDecimalTexte(
        const QString& caractereSeparateurDecimalTexte)
{
    this->setCaractereSeparateurDecimal(
            caracteresSeparateurDecimalTexte.key(caractereSeparateurDecimalTexte));
}
