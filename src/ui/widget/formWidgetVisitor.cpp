#include "mediaWidgetVisitor.h"
#include "../../logic/film.h"
#include "../../logic/serieTv.h"
#include "../../logic/anime.h"
#include "../../logic/libro.h"
#include "../../logic/manga.h"
#include "../../logic/cd.h"
#include "../../services/styleUtils.h"

MediaWidgetVisitor::MediaWidgetVisitor(QWidget* parent, UIService* ui) 
    : parentWidget(parent), uiService(ui), resultWidget(nullptr) {}

QWidget* MediaWidgetVisitor::getResultWidget() const {
    return resultWidget;
}

QWidget* MediaWidgetVisitor::createBaseWidget() {  // Rimosso parametro inutilizzato
    QWidget* widget = new QWidget(parentWidget);
    widget->setStyleSheet(
        "QWidget {"
        "  border: 1px solid #ddd;"
        "  border-radius: 5px;"
        "  margin: 5px;"
        "  background: white;"
        "}"
    );
    return widget;
}

void MediaWidgetVisitor::addCommonInfo(QVBoxLayout* layout, Media* media) {
    QLabel* titleLabel = new QLabel(uiService->formatMediaTitle(media));
    titleLabel->setStyleSheet(StyleUtils::getTitleLabelStyle());
    
    QLabel* yearLabel = new QLabel(uiService->formatMediaYear(media));
    yearLabel->setStyleSheet(StyleUtils::getBodyLabelStyle());
    
    layout->addWidget(titleLabel);
    layout->addWidget(yearLabel);
}

void MediaWidgetVisitor::addActionButtons(QVBoxLayout* layout, Media* media) {  // Corretto: QVBoxLayout
    QPushButton* editButton = new QPushButton();
    editButton->setFixedHeight(44);
    editButton->setToolTip("Modifica questo elemento");
    editButton->setIcon(QIcon("../resources/icon/edit.png"));
    editButton->setStyleSheet(StyleUtils::getItemButtonStyle());

    QPushButton* deleteButton = new QPushButton();
    deleteButton->setFixedHeight(44);
    deleteButton->setToolTip("Elimina questo elemento");
    deleteButton->setIcon(QIcon("../resources/icon/delete.png"));
    deleteButton->setStyleSheet(StyleUtils::getItemButtonStyle());

    // I segnali verranno connessi nel widget principale
    editButton->setProperty("media", QVariant::fromValue(static_cast<void*>(media)));
    deleteButton->setProperty("media", QVariant::fromValue(static_cast<void*>(media)));
    editButton->setObjectName("editButton");
    deleteButton->setObjectName("deleteButton");

    layout->addWidget(editButton);
    layout->addWidget(deleteButton);
}

void MediaWidgetVisitor::visit(Film* film) {
    resultWidget = createBaseWidget();
    
    QHBoxLayout* mainLayout = new QHBoxLayout(resultWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Immagine
    QLabel* imgLabel = new QLabel();
    imgLabel->setPixmap(uiService->loadMediaImage(film->getImmagine()));
    imgLabel->setAlignment(Qt::AlignTop);

    // Dettagli specifici per Film
    QWidget* detailsWidget = new QWidget();
    QVBoxLayout* detailsLayout = new QVBoxLayout(detailsWidget);
    detailsLayout->setAlignment(Qt::AlignTop);

    addCommonInfo(detailsLayout, film);
    
    QLabel* typeLabel = new QLabel("Tipo: Film");
    typeLabel->setStyleSheet(StyleUtils::getSubtitleLabelStyle());
    detailsLayout->addWidget(typeLabel);
    
    QLabel* registaLabel = new QLabel("Regista: " + QString::fromStdString(film->getRegista()));
    QLabel* protagonistaLabel = new QLabel("Protagonista: " + QString::fromStdString(film->getAttoreProtagonista()));
    QLabel* durataLabel = new QLabel("Durata: " + QString::number(film->getDurata()) + " min");
    
    detailsLayout->addWidget(registaLabel);
    detailsLayout->addWidget(protagonistaLabel);
    detailsLayout->addWidget(durataLabel);
    detailsLayout->addStretch();

    // Bottoni
    QWidget* buttonsWidget = new QWidget();
    QVBoxLayout* buttonsLayout = new QVBoxLayout(buttonsWidget);
    buttonsLayout->setAlignment(Qt::AlignTop);
    buttonsLayout->setSpacing(10);

    addActionButtons(buttonsLayout, film);
    buttonsLayout->addStretch();

    mainLayout->addWidget(imgLabel);
    mainLayout->addWidget(detailsWidget, 1);
    mainLayout->addWidget(buttonsWidget);
}

void MediaWidgetVisitor::visit(SerieTv* serieTv) {
    resultWidget = createBaseWidget();
    
    QHBoxLayout* mainLayout = new QHBoxLayout(resultWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Immagine
    QLabel* imgLabel = new QLabel();
    imgLabel->setPixmap(uiService->loadMediaImage(serieTv->getImmagine()));
    imgLabel->setAlignment(Qt::AlignTop);

    // Dettagli specifici per Serie TV
    QWidget* detailsWidget = new QWidget();
    QVBoxLayout* detailsLayout = new QVBoxLayout(detailsWidget);
    detailsLayout->setAlignment(Qt::AlignTop);

    addCommonInfo(detailsLayout, serieTv);
    
    QLabel* typeLabel = new QLabel("Tipo: Serie TV");
    typeLabel->setStyleSheet(StyleUtils::getSubtitleLabelStyle());
    detailsLayout->addWidget(typeLabel);
    
    // Layout orizzontale per stagioni ed episodi
    QWidget* seriesInfoWidget = new QWidget();
    QHBoxLayout* seriesInfoLayout = new QHBoxLayout(seriesInfoWidget);
    seriesInfoLayout->setContentsMargins(0, 0, 0, 0);
    
    QLabel* stagioniLabel = new QLabel("Stagioni: " + QString::number(serieTv->getNumStagioni()));
    QLabel* episodiLabel = new QLabel("Episodi: " + QString::number(serieTv->getNumEpisodi()));
    
    seriesInfoLayout->addWidget(stagioniLabel);
    seriesInfoLayout->addWidget(episodiLabel);
    seriesInfoLayout->addStretch();
    
    detailsLayout->addWidget(seriesInfoWidget);
    
    QLabel* durataEpLabel = new QLabel("Durata episodio: " + QString::number(serieTv->getDurataMediaEp()) + " min");
    QLabel* statoLabel = new QLabel("Stato: " + QString(serieTv->getInCorso() ? "In corso" : "Conclusa"));
    QLabel* ideatoreLabel = new QLabel("Ideatore: " + QString::fromStdString(serieTv->getIdeatore()));
    QLabel* casaProduttriceLabel = new QLabel("Casa produttrice: " + QString::fromStdString(serieTv->getCasaProduttrice()));
    
    detailsLayout->addWidget(durataEpLabel);
    detailsLayout->addWidget(statoLabel);
    detailsLayout->addWidget(ideatoreLabel);
    detailsLayout->addWidget(casaProduttriceLabel);
    detailsLayout->addStretch();

    // Bottoni
    QWidget* buttonsWidget = new QWidget();
    QVBoxLayout* buttonsLayout = new QVBoxLayout(buttonsWidget);
    buttonsLayout->setAlignment(Qt::AlignTop);
    buttonsLayout->setSpacing(10);

    addActionButtons(buttonsLayout, serieTv);
    buttonsLayout->addStretch();

    mainLayout->addWidget(imgLabel);
    mainLayout->addWidget(detailsWidget, 1);
    mainLayout->addWidget(buttonsWidget);
}

void MediaWidgetVisitor::visit(Anime* anime) {
    resultWidget = createBaseWidget();
    
    QHBoxLayout* mainLayout = new QHBoxLayout(resultWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Immagine
    QLabel* imgLabel = new QLabel();
    imgLabel->setPixmap(uiService->loadMediaImage(anime->getImmagine()));
    imgLabel->setAlignment(Qt::AlignTop);

    // Dettagli specifici per Anime
    QWidget* detailsWidget = new QWidget();
    QVBoxLayout* detailsLayout = new QVBoxLayout(detailsWidget);
    detailsLayout->setAlignment(Qt::AlignTop);

    addCommonInfo(detailsLayout, anime);
    
    QLabel* typeLabel = new QLabel("Tipo: Anime");
    typeLabel->setStyleSheet(StyleUtils::getSubtitleLabelStyle());
    detailsLayout->addWidget(typeLabel);
    
    // Layout orizzontale per stagioni ed episodi
    QWidget* seriesInfoWidget = new QWidget();
    QHBoxLayout* seriesInfoLayout = new QHBoxLayout(seriesInfoWidget);
    seriesInfoLayout->setContentsMargins(0, 0, 0, 0);
    
    QLabel* stagioniLabel = new QLabel("Stagioni: " + QString::number(anime->getNumStagioni()));
    QLabel* episodiLabel = new QLabel("Episodi: " + QString::number(anime->getNumEpisodi()));
    
    seriesInfoLayout->addWidget(stagioniLabel);
    seriesInfoLayout->addWidget(episodiLabel);
    seriesInfoLayout->addStretch();
    
    detailsLayout->addWidget(seriesInfoWidget);
    
    QLabel* durataEpLabel = new QLabel("Durata episodio: " + QString::number(anime->getDurataMediaEp()) + " min");
    QLabel* statoLabel = new QLabel("Stato: " + QString(anime->getInCorso() ? "In corso" : "Concluso"));
    QLabel* disegnatoreLabel = new QLabel("Disegnatore: " + QString::fromStdString(anime->getDisegnatore()));
    QLabel* studioLabel = new QLabel("Studio: " + QString::fromStdString(anime->getStudioAnimazione()));
    
    detailsLayout->addWidget(durataEpLabel);
    detailsLayout->addWidget(statoLabel);
    detailsLayout->addWidget(disegnatoreLabel);
    detailsLayout->addWidget(studioLabel);
    detailsLayout->addStretch();

    // Bottoni
    QWidget* buttonsWidget = new QWidget();
    QVBoxLayout* buttonsLayout = new QVBoxLayout(buttonsWidget);
    buttonsLayout->setAlignment(Qt::AlignTop);
    buttonsLayout->setSpacing(10);

    addActionButtons(buttonsLayout, anime);
    buttonsLayout->addStretch();

    mainLayout->addWidget(imgLabel);
    mainLayout->addWidget(detailsWidget, 1);
    mainLayout->addWidget(buttonsWidget);
}

void MediaWidgetVisitor::visit(Libro* libro) {
    resultWidget = createBaseWidget();
    
    QHBoxLayout* mainLayout = new QHBoxLayout(resultWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Immagine
    QLabel* imgLabel = new QLabel();
    imgLabel->setPixmap(uiService->loadMediaImage(libro->getImmagine()));
    imgLabel->setAlignment(Qt::AlignTop);

    // Dettagli specifici per Libro
    QWidget* detailsWidget = new QWidget();
    QVBoxLayout* detailsLayout = new QVBoxLayout(detailsWidget);
    detailsLayout->setAlignment(Qt::AlignTop);

    addCommonInfo(detailsLayout, libro);
    
    QLabel* typeLabel = new QLabel("Tipo: Libro");
    typeLabel->setStyleSheet(StyleUtils::getSubtitleLabelStyle());
    detailsLayout->addWidget(typeLabel);
    
    QLabel* scrittoreLabel = new QLabel("Scrittore: " + QString::fromStdString(libro->getScrittore()));
    QLabel* annoStampaLabel = new QLabel("Anno di stampa: " + QString::number(libro->getAnnoStampa()));
    QLabel* casaEditriceLabel = new QLabel("Casa Editrice: " + QString::fromStdString(libro->getCasaEditrice()));
    
    detailsLayout->addWidget(scrittoreLabel);
    detailsLayout->addWidget(annoStampaLabel);
    detailsLayout->addWidget(casaEditriceLabel);
    detailsLayout->addStretch();

    // Bottoni
    QWidget* buttonsWidget = new QWidget();
    QVBoxLayout* buttonsLayout = new QVBoxLayout(buttonsWidget);
    buttonsLayout->setAlignment(Qt::AlignTop);
    buttonsLayout->setSpacing(10);

    addActionButtons(buttonsLayout, libro);
    buttonsLayout->addStretch();

    mainLayout->addWidget(imgLabel);
    mainLayout->addWidget(detailsWidget, 1);
    mainLayout->addWidget(buttonsWidget);
}

void MediaWidgetVisitor::visit(Manga* manga) {
    resultWidget = createBaseWidget();
    
    QHBoxLayout* mainLayout = new QHBoxLayout(resultWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Immagine
    QLabel* imgLabel = new QLabel();
    imgLabel->setPixmap(uiService->loadMediaImage(manga->getImmagine()));
    imgLabel->setAlignment(Qt::AlignTop);

    // Dettagli specifici per Manga
    QWidget* detailsWidget = new QWidget();
    QVBoxLayout* detailsLayout = new QVBoxLayout(detailsWidget);
    detailsLayout->setAlignment(Qt::AlignTop);

    addCommonInfo(detailsLayout, manga);
    
    QLabel* typeLabel = new QLabel("Tipo: Manga");
    typeLabel->setStyleSheet(StyleUtils::getSubtitleLabelStyle());
    detailsLayout->addWidget(typeLabel);
    
    QLabel* scrittoreLabel = new QLabel("Scrittore: " + QString::fromStdString(manga->getScrittore()));
    QLabel* illustratoreLabel = new QLabel("Illustratore: " + QString::fromStdString(manga->getIllustratore()));
    QLabel* volumiLabel = new QLabel("Volumi: " + QString::number(manga->getNumLibri()));
    QLabel* statoLabel = new QLabel("Stato: " + QString(manga->getConcluso() ? "Concluso" : "In corso"));
    
    detailsLayout->addWidget(scrittoreLabel);
    detailsLayout->addWidget(illustratoreLabel);
    detailsLayout->addWidget(volumiLabel);
    detailsLayout->addWidget(statoLabel);
    detailsLayout->addStretch();

    // Bottoni
    QWidget* buttonsWidget = new QWidget();
    QVBoxLayout* buttonsLayout = new QVBoxLayout(buttonsWidget);
    buttonsLayout->setAlignment(Qt::AlignTop);
    buttonsLayout->setSpacing(10);

    addActionButtons(buttonsLayout, manga);
    buttonsLayout->addStretch();

    mainLayout->addWidget(imgLabel);
    mainLayout->addWidget(detailsWidget, 1);
    mainLayout->addWidget(buttonsWidget);
}

void MediaWidgetVisitor::visit(Cd* cd) {
    resultWidget = createBaseWidget();
    
    QHBoxLayout* mainLayout = new QHBoxLayout(resultWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Immagine
    QLabel* imgLabel = new QLabel();
    imgLabel->setPixmap(uiService->loadMediaImage(cd->getImmagine()));
    imgLabel->setAlignment(Qt::AlignTop);

    // Dettagli specifici per CD
    QWidget* detailsWidget = new QWidget();
    QVBoxLayout* detailsLayout = new QVBoxLayout(detailsWidget);
    detailsLayout->setAlignment(Qt::AlignTop);

    addCommonInfo(detailsLayout, cd);
    
    QLabel* typeLabel = new QLabel("Tipo: CD");
    typeLabel->setStyleSheet(StyleUtils::getSubtitleLabelStyle());
    detailsLayout->addWidget(typeLabel);
    
    QLabel* artistaLabel = new QLabel("Artista: " + QString::fromStdString(cd->getArtista()));
    QLabel* tracceLabel = new QLabel("Tracce: " + QString::number(cd->getNumTracce()));
    QLabel* durataMediaLabel = new QLabel("Durata media: " + QString::number(cd->getDurataMedTracce()) + " sec");
    
    detailsLayout->addWidget(artistaLabel);
    detailsLayout->addWidget(tracceLabel);
    detailsLayout->addWidget(durataMediaLabel);
    detailsLayout->addStretch();

    // Bottoni
    QWidget* buttonsWidget = new QWidget();
    QVBoxLayout* buttonsLayout = new QVBoxLayout(buttonsWidget);
    buttonsLayout->setAlignment(Qt::AlignTop);
    buttonsLayout->setSpacing(10);

    addActionButtons(buttonsLayout, cd);
    buttonsLayout->addStretch();

    mainLayout->addWidget(imgLabel);
    mainLayout->addWidget(detailsWidget, 1);
    mainLayout->addWidget(buttonsWidget);
}