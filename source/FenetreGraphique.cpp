//==============================================================================
// Name        : FenetreGraphique.cpp
// Author      : Alexis Foerster (alexis.foerster@gmail.com)
// Version     : 1.2.0 (03/10/2020)
// Description : Source file of the FenetreGraphique class
//==============================================================================

#include "FenetreGraphique.h"
#include "ui_FenetreGraphique.h"
#include "ParametresAxe.h"
#include <QDialogButtonBox>
#include <QDoubleValidator>
#include <QFile>
#include <QFileDialog>
#include <QIODevice>
#include <QPushButton>
#include <QString>
#ifdef ENABLE_QWT
#include <QBrush>
#include <QColor>
#include <QFont>
#include <QPalette>
#include <QPen>
#include <QPixmap>
#include <QPointF>
#include <QRgb>
#include <QVector>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_scale_draw.h>
#include <qwt_scale_widget.h>
#include <qwt_series_data.h>
#include <qwt_symbol.h>
#endif

FenetreGraphique::FenetreGraphique(QWidget* parent) :
        QDialog(parent), ui(new Ui::FenetreGraphique)
{
    this->ui->setupUi(this);

#ifdef ENABLE_QWT
    this->ui->widgetGraphique = new QwtPlot(this);
    this->ui->gridLayoutFenetreGraphique->addWidget(this->ui->widgetGraphique, 1, 0, 1, 1);
#endif

    this->initialiserElementsGraphiques();
    this->actualiserElementsGraphiques();
}

FenetreGraphique::~FenetreGraphique()
{
    delete this->ui;
}

const QList<Courbe>& FenetreGraphique::getListeDeCourbes() const
{
    return this->listeDeCourbes;
}

const QList<Point>& FenetreGraphique::getListeDePointsManuels() const
{
    return this->listeDePointsManuels;
}

const ParametresGraphique& FenetreGraphique::getParametresGraphique() const
{
    return this->parametresGraphique;
}

const ParametresAffichage& FenetreGraphique::getParametresAffichage() const
{
    return this->parametresAffichage;
}

const ParametresFichiers& FenetreGraphique::getParametresFichiers() const
{
    return this->parametresFichiers;
}

void FenetreGraphique::setListeDeCourbes(const QList<Courbe>& listeDeCourbes)
{
    this->listeDeCourbes = listeDeCourbes;
}

void FenetreGraphique::setListeDePointsManuels(const QList<Point>& listeDePointsManuels)
{
    this->listeDePointsManuels = listeDePointsManuels;
}

void FenetreGraphique::setParametresGraphique(const ParametresGraphique& parametresGraphique)
{
    this->parametresGraphique = parametresGraphique;
}

void FenetreGraphique::setParametresAffichage(const ParametresAffichage& parametresAffichage)
{
    this->parametresAffichage = parametresAffichage;
}

void FenetreGraphique::setParametresFichiers(const ParametresFichiers& parametresFichiers)
{
    this->parametresFichiers = parametresFichiers;
}

void FenetreGraphique::initialiserElementsGraphiques()
{
    const QDoubleValidator* nombreReel = new QDoubleValidator(this);
    this->ui->lineEditAxeHorizontalBorneInferieure->setValidator(nombreReel);
    this->ui->lineEditAxeHorizontalBorneSuperieure->setValidator(nombreReel);
    this->ui->lineEditAxeHorizontalPasPrincipal->setValidator(nombreReel);
    this->ui->lineEditAxeHorizontalPasSecondaire->setValidator(nombreReel);
    this->ui->lineEditAxeVerticalBorneInferieure->setValidator(nombreReel);
    this->ui->lineEditAxeVerticalBorneSuperieure->setValidator(nombreReel);
    this->ui->lineEditAxeVerticalPasPrincipal->setValidator(nombreReel);
    this->ui->lineEditAxeVerticalPasSecondaire->setValidator(nombreReel);
    this->ui->buttonBox->button(QDialogButtonBox::Save)->setText("Enregistrer");
}

void FenetreGraphique::actualiserElementsGraphiques()
{
    const ParametresAxe& parametresAxeHorizontal =
            this->parametresGraphique.getParametresAxeHorizontal();
    const ParametresAxe& parametresAxeVertical =
            this->parametresGraphique.getParametresAxeVertical();

    this->ui->lineEditAxeHorizontalBorneInferieure->setText(
            QString::number(parametresAxeHorizontal.getBorneInferieure()));
    this->ui->lineEditAxeHorizontalBorneSuperieure->setText(
            QString::number(parametresAxeHorizontal.getBorneSuperieure()));
    this->ui->lineEditAxeHorizontalPasPrincipal->setText(
            QString::number(parametresAxeHorizontal.getPasPrincipal()));
//    this->ui->lineEditAxeHorizontalPasSecondaire->setText(
//            QString::number(parametresAxeHorizontal.getPasSecondaire()));
    this->ui->lineEditAxeHorizontalPasSecondaire->setText(QString::number(0.0));
    this->ui->checkBoxAxeHorizontalGrillePrincipale->setChecked(
            parametresAxeHorizontal.getGrillePrincipale());
    this->ui->checkBoxAxeHorizontalGrilleSecondaire->setChecked(
            parametresAxeHorizontal.getGrilleSecondaire());
    this->ui->lineEditAxeVerticalBorneInferieure->setText(
            QString::number(parametresAxeVertical.getBorneInferieure()));
    this->ui->lineEditAxeVerticalBorneSuperieure->setText(
            QString::number(parametresAxeVertical.getBorneSuperieure()));
    this->ui->lineEditAxeVerticalPasPrincipal->setText(
            QString::number(parametresAxeVertical.getPasPrincipal()));
//    this->ui->lineEditAxeVerticalPasSecondaire->setText(
//            QString::number(parametresAxeVertical.getPasSecondaire()));
    this->ui->lineEditAxeVerticalPasSecondaire->setText(QString::number(0.0));
    this->ui->checkBoxAxeVerticalGrillePrincipale->setChecked(
            parametresAxeVertical.getGrillePrincipale());
    this->ui->checkBoxAxeVerticalGrilleSecondaire->setChecked(
            parametresAxeVertical.getGrilleSecondaire());

    this->dessinerGraphique();
}

void FenetreGraphique::effacerGraphique()
{
#ifdef ENABLE_QWT
    QwtPlot* graphique = dynamic_cast<QwtPlot*>(this->ui->widgetGraphique);

    const QColor couleurArrierePlan = QColor(Qt::white);
    const QBrush brosseArrierePlan = QBrush(couleurArrierePlan, Qt::SolidPattern);

    graphique->detachItems();
    graphique->setCanvasBackground(brosseArrierePlan);

    graphique->replot();
#endif
}

void FenetreGraphique::dessinerGraphique()
{
    const QList<Courbe>& listeDeCourbes = this->getListeDeCourbes();
    const QList<Point>& listeDePointsManuels = this->getListeDePointsManuels();
    const int nombreDeCourbes = listeDeCourbes.count();
    const int nombreDePointsManuels = listeDePointsManuels.count();

    this->effacerGraphique();
    this->dessinerRepereGraphique();
    this->dessinerGrilleGraphique();
    for (int itCourbe = 0; itCourbe < nombreDeCourbes; itCourbe++)
    {
        const Courbe& courbe = listeDeCourbes.at(itCourbe);
        this->dessinerCourbe(courbe);
    }
    for (int itPointManuel = 0; itPointManuel < nombreDePointsManuels; itPointManuel++)
    {
        const Point& pointManuel = listeDePointsManuels.at(itPointManuel);
        this->dessinerPointManuel(pointManuel);
    }
}

void FenetreGraphique::dessinerRepereGraphique()
{
#ifdef ENABLE_QWT
    QwtPlot* graphique = dynamic_cast<QwtPlot*>(this->ui->widgetGraphique);

    const ParametresAxe& parametresAxeHorizontal =
            this->parametresGraphique.getParametresAxeHorizontal();
    const ParametresAxe& parametresAxeVertical =
            this->parametresGraphique.getParametresAxeVertical();
    const ParametresTrait& parametresAxes = this->parametresAffichage.getParametresAxes();

    const int& epaisseurRepere = parametresAxes.getEpaisseurTrait();
    const QRgb& couleurRepere = parametresAxes.getCouleurTrait();
    const QBrush brosseRepere = QBrush(QColor(couleurRepere), Qt::SolidPattern);
    const QwtScaleWidget* axeRepere = new QwtScaleWidget();
    QFont policeRepere = axeRepere->font();
    QPalette paletteRepere = axeRepere->palette();
    policeRepere.setBold(epaisseurRepere > 1);
    paletteRepere.setBrush(QPalette::Text, brosseRepere);
    paletteRepere.setBrush(QPalette::WindowText, brosseRepere);

    graphique->setAxisScale(QwtPlot::xBottom, parametresAxeHorizontal.getBorneInferieure(),
            parametresAxeHorizontal.getBorneSuperieure(),
            parametresAxeHorizontal.getPasPrincipal());
    graphique->setAxisScale(QwtPlot::yLeft, parametresAxeVertical.getBorneInferieure(),
            parametresAxeVertical.getBorneSuperieure(), parametresAxeVertical.getPasPrincipal());

    QwtScaleWidget* axeHorizontalGraphique = graphique->axisWidget(QwtPlot::xBottom);
    QwtScaleDraw* dessinAxeHorizontalGraphique = graphique->axisScaleDraw(QwtPlot::xBottom);
    axeHorizontalGraphique->setFont(policeRepere);
    axeHorizontalGraphique->setPalette(paletteRepere);
    dessinAxeHorizontalGraphique->setPenWidth(epaisseurRepere);

    QwtScaleWidget* axeVerticalGraphique = graphique->axisWidget(QwtPlot::yLeft);
    QwtScaleDraw* dessinAxeVerticalGraphique = graphique->axisScaleDraw(QwtPlot::yLeft);
    axeVerticalGraphique->setFont(policeRepere);
    axeVerticalGraphique->setPalette(paletteRepere);
    dessinAxeVerticalGraphique->setPenWidth(epaisseurRepere);

    graphique->replot();
#endif
}

void FenetreGraphique::dessinerGrilleGraphique()
{
#ifdef ENABLE_QWT
    QwtPlot* graphique = dynamic_cast<QwtPlot*>(this->ui->widgetGraphique);

    const ParametresAxe& parametresAxeHorizontal =
            this->parametresGraphique.getParametresAxeHorizontal();
    const ParametresAxe& parametresAxeVertical =
            this->parametresGraphique.getParametresAxeVertical();

    const QColor couleurGrillePrincipale = QColor(Qt::black);
    const QColor couleurGrilleSecondaire = QColor(Qt::gray);
    const QBrush brosseGrillePrincipale = QBrush(couleurGrillePrincipale, Qt::SolidPattern);
    const QBrush brosseGrilleSecondaire = QBrush(couleurGrilleSecondaire, Qt::SolidPattern);
    const QPen pinceauGrillePrincipale = QPen(brosseGrillePrincipale, 1, Qt::DotLine);
    const QPen pinceauGrilleSecondaire = QPen(brosseGrilleSecondaire, 1, Qt::DotLine);

    QwtPlotGrid* grilleGraphique = new QwtPlotGrid();
    grilleGraphique->enableX(parametresAxeHorizontal.getGrillePrincipale());
    grilleGraphique->enableXMin(parametresAxeHorizontal.getGrilleSecondaire());
    grilleGraphique->enableY(parametresAxeVertical.getGrillePrincipale());
    grilleGraphique->enableYMin(parametresAxeVertical.getGrilleSecondaire());
    grilleGraphique->setMajorPen(pinceauGrillePrincipale);
    grilleGraphique->setMinorPen(pinceauGrilleSecondaire);
    grilleGraphique->attach(graphique);

    graphique->replot();
#endif
}

void FenetreGraphique::dessinerCourbe(const Courbe& courbe)
{
    const int nombreDePointsCourbe = courbe.count();
    const Point& premierPoint = courbe.at(0);
    const Point& dernierPoint = courbe.at(nombreDePointsCourbe - 1);
    const ParametresTrait& parametresCourbes = this->parametresAffichage.getParametresCourbes();
    const ParametresPoint& parametresPointsCourbes =
            this->parametresAffichage.getParametresPointsCourbes();

    this->dessinerCourbeGraphique(courbe, parametresCourbes);
    this->dessinerPointGraphique(premierPoint, parametresPointsCourbes);
    this->dessinerPointGraphique(dernierPoint, parametresPointsCourbes);
}

void FenetreGraphique::dessinerPointManuel(const Point& pointManuel)
{
    const ParametresPoint& parametresPointManuels =
            this->parametresAffichage.getParametresPointsManuels();

    this->dessinerPointGraphique(pointManuel, parametresPointManuels);
}

void FenetreGraphique::dessinerCourbeGraphique(const Courbe& courbe,
        const ParametresTrait& parametresCourbe)
{
#ifdef ENABLE_QWT
    QwtPlot* graphique = dynamic_cast<QwtPlot*>(this->ui->widgetGraphique);

    const int& styleCourbe = parametresCourbe.getStyleTrait();
    const int& epaisseurCourbe = parametresCourbe.getEpaisseurTrait();
    const QRgb& couleurCourbe = parametresCourbe.getCouleurTrait();
    const QBrush brosseCourbe = QBrush(QColor(couleurCourbe), Qt::SolidPattern);
    const QPen pinceauCourbe = QPen(brosseCourbe, epaisseurCourbe,
            static_cast<Qt::PenStyle>(styleCourbe + 1), Qt::RoundCap, Qt::RoundJoin);

    QwtPlotCurve* courbeGraphique = new QwtPlotCurve();
    QwtPointSeriesData* donneesCourbe = new QwtPointSeriesData();
    QVector<QPointF>* donneesPointsCourbe = new QVector<QPointF>();
    const int nombreDePointsCourbe = courbe.count();
    for (int itPointCourbe = 0; itPointCourbe < nombreDePointsCourbe; itPointCourbe++)
    {
        const Point& pointCourbe = courbe.at(itPointCourbe);
        donneesPointsCourbe->push_back(pointCourbe.getPointReel());
    }
    donneesCourbe->setSamples(*donneesPointsCourbe);
    courbeGraphique->setData(donneesCourbe);
    courbeGraphique->setPen(pinceauCourbe);
    courbeGraphique->attach(graphique);

    graphique->replot();
#else
    Q_UNUSED(courbe);
    Q_UNUSED(parametresCourbe);
#endif
}

void FenetreGraphique::dessinerPointGraphique(const Point& point,
        const ParametresPoint& parametresPoint)
{
#ifdef ENABLE_QWT
    QwtPlot* graphique = dynamic_cast<QwtPlot*>(this->ui->widgetGraphique);

    const int& stylePoint = parametresPoint.getStylePoint();
    const int& epaisseurPoint = parametresPoint.getEpaisseurPoint();
    const QRgb& couleurPoint = parametresPoint.getCouleurPoint();
    const QBrush brossePoint = QBrush(QColor(couleurPoint), Qt::SolidPattern);
    const QPen pinceauPoint = QPen(brossePoint, epaisseurPoint / 2, Qt::SolidLine);
    const QwtSymbol::Style symbolePoint =
            (stylePoint == ParametresPoint::CARRE) ? QwtSymbol::Rect :
            (stylePoint == ParametresPoint::CERCLE) ? QwtSymbol::Ellipse : QwtSymbol::NoSymbol;

    QwtPlotMarker* pointGraphique = new QwtPlotMarker();
    QwtSymbol* symbolePointGraphique = new QwtSymbol();
    symbolePointGraphique->setStyle(symbolePoint);
    symbolePointGraphique->setSize(epaisseurPoint);
    symbolePointGraphique->setPen(pinceauPoint);
    pointGraphique->setSymbol(symbolePointGraphique);
    pointGraphique->setValue(point.getPointReelX(), point.getPointReelY());
    pointGraphique->attach(graphique);

    graphique->replot();
#else
    Q_UNUSED(point);
    Q_UNUSED(parametresPoint);
#endif
}

void FenetreGraphique::exporterGraphique()
{
    const QString cheminFichierGraphique = QFileDialog::getSaveFileName(this,
            QString::fromUtf8("Sélection d'un fichier image"),
            this->parametresFichiers.getCheminFichierGraphique(),
            QString::fromUtf8("Fichier image Windows Bitmap (*.bmp);;"
                    "Fichier image JPEG (*.jpg *.jpeg);;"
                    "Fichier image PNG (*.png)"));
    if (cheminFichierGraphique.isEmpty())
        return;

    QFile fichierGraphique(cheminFichierGraphique);
    if (!fichierGraphique.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

#ifdef ENABLE_QWT
    QwtPlot* graphique = dynamic_cast<QwtPlot*>(this->ui->widgetGraphique);

    QPixmap pixmap = QPixmap::grabWidget(graphique);
    pixmap.save(cheminFichierGraphique);
#endif
}

void FenetreGraphique::on_lineEditAxeHorizontalBorneInferieure_textChanged()
{
    ParametresAxe parametresAxeHorizontal = this->parametresGraphique.getParametresAxeHorizontal();
    parametresAxeHorizontal.setBorneInferieure(
            this->ui->lineEditAxeHorizontalBorneInferieure->text().toDouble());
    this->parametresGraphique.setParametresAxeHorizontal(parametresAxeHorizontal);
    this->dessinerGraphique();
}

void FenetreGraphique::on_lineEditAxeHorizontalBorneSuperieure_textChanged()
{
    ParametresAxe parametresAxeHorizontal = this->parametresGraphique.getParametresAxeHorizontal();
    parametresAxeHorizontal.setBorneSuperieure(
            this->ui->lineEditAxeHorizontalBorneSuperieure->text().toDouble());
    this->parametresGraphique.setParametresAxeHorizontal(parametresAxeHorizontal);
    this->dessinerGraphique();
}

void FenetreGraphique::on_lineEditAxeHorizontalPasPrincipal_textChanged()
{
    ParametresAxe parametresAxeHorizontal = this->parametresGraphique.getParametresAxeHorizontal();
    parametresAxeHorizontal.setPasPrincipal(
            this->ui->lineEditAxeHorizontalPasPrincipal->text().toDouble());
    this->parametresGraphique.setParametresAxeHorizontal(parametresAxeHorizontal);
    this->dessinerGraphique();
}

void FenetreGraphique::on_lineEditAxeHorizontalPasSecondaire_textChanged()
{
    ParametresAxe parametresAxeHorizontal = this->parametresGraphique.getParametresAxeHorizontal();
    parametresAxeHorizontal.setPasSecondaire(
            this->ui->lineEditAxeHorizontalPasSecondaire->text().toDouble());
    this->parametresGraphique.setParametresAxeHorizontal(parametresAxeHorizontal);
    this->dessinerGraphique();
}

void FenetreGraphique::on_checkBoxAxeHorizontalGrillePrincipale_stateChanged()
{
    ParametresAxe parametresAxeHorizontal = this->parametresGraphique.getParametresAxeHorizontal();
    parametresAxeHorizontal.setGrillePrincipale(
            this->ui->checkBoxAxeHorizontalGrillePrincipale->isChecked());
    this->parametresGraphique.setParametresAxeHorizontal(parametresAxeHorizontal);
    this->dessinerGraphique();
}

void FenetreGraphique::on_checkBoxAxeHorizontalGrilleSecondaire_stateChanged()
{
    ParametresAxe parametresAxeHorizontal = this->parametresGraphique.getParametresAxeHorizontal();
    parametresAxeHorizontal.setGrilleSecondaire(
            this->ui->checkBoxAxeHorizontalGrilleSecondaire->isChecked());
    this->parametresGraphique.setParametresAxeHorizontal(parametresAxeHorizontal);
    this->dessinerGraphique();
}

void FenetreGraphique::on_lineEditAxeVerticalBorneInferieure_textChanged()
{
    ParametresAxe parametresAxeVertical = this->parametresGraphique.getParametresAxeVertical();
    parametresAxeVertical.setBorneInferieure(
            this->ui->lineEditAxeVerticalBorneInferieure->text().toDouble());
    this->parametresGraphique.setParametresAxeVertical(parametresAxeVertical);
    this->dessinerGraphique();
}

void FenetreGraphique::on_lineEditAxeVerticalBorneSuperieure_textChanged()
{
    ParametresAxe parametresAxeVertical = this->parametresGraphique.getParametresAxeVertical();
    parametresAxeVertical.setBorneSuperieure(
            this->ui->lineEditAxeVerticalBorneSuperieure->text().toDouble());
    this->parametresGraphique.setParametresAxeVertical(parametresAxeVertical);
    this->dessinerGraphique();
}

void FenetreGraphique::on_lineEditAxeVerticalPasPrincipal_textChanged()
{
    ParametresAxe parametresAxeVertical = this->parametresGraphique.getParametresAxeVertical();
    parametresAxeVertical.setPasPrincipal(
            this->ui->lineEditAxeVerticalPasPrincipal->text().toDouble());
    this->parametresGraphique.setParametresAxeVertical(parametresAxeVertical);
    this->dessinerGraphique();
}

void FenetreGraphique::on_lineEditAxeVerticalPasSecondaire_textChanged()
{
    ParametresAxe parametresAxeVertical = this->parametresGraphique.getParametresAxeVertical();
    parametresAxeVertical.setPasSecondaire(
            this->ui->lineEditAxeVerticalPasSecondaire->text().toDouble());
    this->parametresGraphique.setParametresAxeVertical(parametresAxeVertical);
    this->dessinerGraphique();
}

void FenetreGraphique::on_checkBoxAxeVerticalGrillePrincipale_stateChanged()
{
    ParametresAxe parametresAxeVertical = this->parametresGraphique.getParametresAxeVertical();
    parametresAxeVertical.setGrillePrincipale(
            this->ui->checkBoxAxeVerticalGrillePrincipale->isChecked());
    this->parametresGraphique.setParametresAxeVertical(parametresAxeVertical);
    this->dessinerGraphique();
}

void FenetreGraphique::on_checkBoxAxeVerticalGrilleSecondaire_stateChanged()
{
    ParametresAxe parametresAxeVertical = this->parametresGraphique.getParametresAxeVertical();
    parametresAxeVertical.setGrilleSecondaire(
            this->ui->checkBoxAxeVerticalGrilleSecondaire->isChecked());
    this->parametresGraphique.setParametresAxeVertical(parametresAxeVertical);
    this->dessinerGraphique();
}

void FenetreGraphique::on_buttonBox_clicked(QAbstractButton* button)
{
    if (button == this->ui->buttonBox->button(QDialogButtonBox::Save))
    {
        this->exporterGraphique();
    }
}
