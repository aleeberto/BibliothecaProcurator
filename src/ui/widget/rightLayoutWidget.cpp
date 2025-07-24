#include "rightLayoutWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QDir>
#include <QFileInfo>
#include <QCoreApplication>
#include <QDebug>
#include "../../logic/film.h"
#include "../../logic/serieTv.h"
#include "../../logic/anime.h"
#include "../../logic/libro.h"
#include "../../logic/manga.h"
#include "../../logic/cd.h"

RightLayoutWidget::RightLayoutWidget(QWidget *parent) : QWidget(parent)
{
    setStyleSheet(
        "QWidget { background-color: #f5f5f5; }"
        "QScrollArea { border: none; background: transparent; }"
    );

    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    currentCategory = "Tutti";
    currentSearchText = "";
}

RightLayoutWidget::~RightLayoutWidget()
{
    clearLayout();
}

void RightLayoutWidget::setMediaCollection(const QVector<Media*>& collection)
{
    mediaCollection = collection;
}

void RightLayoutWidget::setJsonService(JsonService* service)
{
    jsonService = service;
}

void RightLayoutWidget::displayMediaByCategory(const QString &category, const QString &searchText)
{
    currentCategory = category;
    currentSearchText = searchText.toLower();
    
    clearLayout();

    for (Media* media : mediaCollection) {
        QString mediaType = jsonService->getMediaTypeName(media);
        QString mediaTitle = QString::fromStdString(media->getTitolo()).toLower();

        if ((category == "Tutti" || mediaType == category) &&
            (currentSearchText.isEmpty() || mediaTitle.contains(currentSearchText))) {
            addMediaCardToLayout(media);
        }
    }

    mainLayout->addStretch();
}

void RightLayoutWidget::clearLayout()
{
    QLayoutItem* item;
    while ((item = mainLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            item->widget()->deleteLater();
        }
        delete item;
    }
}

void RightLayoutWidget::showCreateItemWidget(QWidget* createWidget)
{
    clearLayout();
    createWidget->show();
    mainLayout->addWidget(createWidget);
    mainLayout->addStretch();
}

void RightLayoutWidget::addMediaCardToLayout(Media* media)
{
    QWidget *mediaCard = new QWidget();
    mediaCard->setStyleSheet(
        "QWidget {"
        "  border: 1px solid #ddd;"
        "  border-radius: 5px;"
        "  margin: 5px;"
        "  background: white;"
        "}"
    );

    QHBoxLayout *cardLayout = new QHBoxLayout(mediaCard);
    cardLayout->setContentsMargins(10, 10, 10, 10);

    // Image
    QLabel *imgLabel = new QLabel();
    imgLabel->setPixmap(loadMediaImage(media->getImmagine()));
    imgLabel->setAlignment(Qt::AlignTop);

    // Details
    QWidget *detailsWidget = new QWidget();
    QVBoxLayout *detailsLayout = new QVBoxLayout(detailsWidget);
    detailsLayout->setAlignment(Qt::AlignTop);

    QLabel *titleLabel = new QLabel("<b>" + QString::fromStdString(media->getTitolo()) + "</b>");
    titleLabel->setStyleSheet("font-size: 14px;");

    QLabel *yearLabel = new QLabel("Anno: " + QString::number(media->getAnno()));
    QLabel *typeLabel = new QLabel("Tipo: " + jsonService->getMediaTypeName(media));

    detailsLayout->addWidget(titleLabel);
    detailsLayout->addWidget(yearLabel);
    detailsLayout->addWidget(typeLabel);

    // Add type-specific fields
    if (auto film = dynamic_cast<Film*>(media)) {
        detailsLayout->addWidget(new QLabel("Regista: " + QString::fromStdString(film->getRegista())));
        detailsLayout->addWidget(new QLabel("Protagonista: " + QString::fromStdString(film->getAttoreProtagonista())));
        detailsLayout->addWidget(new QLabel("Durata: " + QString::number(film->getDurata()) + " min"));
    }
    else if (auto serie = dynamic_cast<SerieTv*>(media)) {
        detailsLayout->addWidget(new QLabel("Stagioni: " + QString::number(serie->getNumStagioni())));
        detailsLayout->addWidget(new QLabel("Episodi: " + QString::number(serie->getNumEpisodi())));
        detailsLayout->addWidget(new QLabel("Durata episodio: " + QString::number(serie->getDurataMediaEp()) + " min"));
        detailsLayout->addWidget(new QLabel("Ideatore: " + QString::fromStdString(serie->getIdeatore())));
        detailsLayout->addWidget(new QLabel("Casa produttrice: " + QString::fromStdString(serie->getCasaProduttrice())));
        detailsLayout->addWidget(new QLabel("Stato: " + QString(serie->getInCorso() ? "In corso" : "Conclusa")));
    }
    else if (auto anime = dynamic_cast<Anime*>(media)) {
        detailsLayout->addWidget(new QLabel("Stagioni: " + QString::number(anime->getNumStagioni())));
        detailsLayout->addWidget(new QLabel("Episodi: " + QString::number(anime->getNumEpisodi())));
        detailsLayout->addWidget(new QLabel("Durata episodio: " + QString::number(anime->getDurataMediaEp()) + " min"));
        detailsLayout->addWidget(new QLabel("Disegnatore: " + QString::fromStdString(anime->getDisegnatore())));
        detailsLayout->addWidget(new QLabel("Studio: " + QString::fromStdString(anime->getStudioAnimazione())));
        detailsLayout->addWidget(new QLabel("Stato: " + QString(anime->getInCorso() ? "In corso" : "Conclusa")));
    }
    else if (auto libro = dynamic_cast<Libro*>(media)) {
        detailsLayout->addWidget(new QLabel("Scrittore: " + QString::fromStdString(libro->getScrittore())));
        detailsLayout->addWidget(new QLabel("Anno di Stampa: " + QString::number(libro->getAnnoStampa())));
        detailsLayout->addWidget(new QLabel("Casa Editrice: " + QString::fromStdString(libro->getCasaEditrice())));
    }
    else if (auto manga = dynamic_cast<Manga*>(media)) {
        detailsLayout->addWidget(new QLabel("Scrittore: " + QString::fromStdString(manga->getScrittore())));
        detailsLayout->addWidget(new QLabel("Illustratore: " + QString::fromStdString(manga->getIllustratore())));
        detailsLayout->addWidget(new QLabel("Volumi: " + QString::number(manga->getNumLibri())));
        detailsLayout->addWidget(new QLabel("Stato: " + QString(manga->getConcluso() ? "Concluso" : "In corso")));
    }
    else if (auto cd = dynamic_cast<Cd*>(media)) {
        detailsLayout->addWidget(new QLabel("Artista: " + QString::fromStdString(cd->getArtista())));
        detailsLayout->addWidget(new QLabel("Tracce: " + QString::number(cd->getNumTracce())));
        detailsLayout->addWidget(new QLabel("Durata media: " + QString::number(cd->getDurataMedTracce()) + " sec"));
    }

    detailsLayout->addStretch();

    cardLayout->addWidget(imgLabel);
    cardLayout->addWidget(detailsWidget, 1);

    mainLayout->addWidget(mediaCard);
}

QPixmap RightLayoutWidget::loadMediaImage(const std::string& imagePath)
{
    QString imageQPath = QString::fromStdString(imagePath);
    QPixmap pixmap;
    
    // Convert relative path to absolute
    QFileInfo fileInfo(imageQPath);
    if (fileInfo.isRelative()) {
        QString appDir = QCoreApplication::applicationDirPath();
        imageQPath = QDir::cleanPath(appDir + QDir::separator() + imageQPath);
    }
    
    // Try to load image
    if (!pixmap.load(imageQPath)) {
        // Create placeholder with debug info
        pixmap = QPixmap(120, 180);
        pixmap.fill(QColor(240, 240, 240));
        
        QPainter painter(&pixmap);
        painter.setPen(Qt::darkGray);
        painter.setFont(QFont("Arial", 8));
        
        QString debugInfo = QString("Impossibile caricare:\n%1\nPercorso risolto:\n%2")
                           .arg(QString::fromStdString(imagePath))
                           .arg(imageQPath);
        
        painter.drawText(pixmap.rect().adjusted(5, 5, -5, -5), 
                        Qt::AlignCenter | Qt::TextWordWrap, 
                        debugInfo);
        
        qDebug() << "Errore caricamento immagine:" << debugInfo;
    }
    
    return pixmap.scaled(120, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}
