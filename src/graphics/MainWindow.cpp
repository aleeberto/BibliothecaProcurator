#include "MainWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollArea>
#include <QLabel>
#include <QDebug>
#include <QDir>
#include <QPixmap>
#include <QPainter>
#include <QDir>
#include <QFileInfo>
#include <QPainter>
#include <QCoreApplication> 

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // Window configuration
    this->setStyleSheet(
        "QMainWindow { background-color: #f5f5f5; } "
        "QLineEdit, QComboBox {"
        "  padding: 5px;"
        "  border: 1px solid #ccc;"
        "  border-radius: 3px;"
        "  min-height: 25px;"
        "}"
        "QLineEdit:focus, QComboBox:focus {"
        "  border: 1px solid #4CAF50;"
        "}"
        "QLabel {"
        "  font-weight: bold;"
        "  color: #333;"
        "}"
        "QScrollArea { border: none; background: transparent; }"
    );

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setStyleSheet("background: transparent;");
    setCentralWidget(centralWidget);

    // Main layout
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Left widget - Menu and categories
    QWidget *leftWidget = new QWidget();
    leftWidget->setStyleSheet("background-color: #fff; border-right: 1px solid #ddd;");
    leftWidget->setFixedWidth(220);

    leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->setContentsMargins(5, 10, 5, 10);
    leftLayout->setSpacing(5);

    // Top menu
    topMenu = new TopMenuWidget(this);
    leftLayout->addWidget(topMenu);

    // Search bar
    setupSearchBar();

    // Categories
    setupCategoryButtons();

    leftLayout->addStretch();

    // Right widget - Main content
    rightWidget = new QWidget();
    rightLayout = new QVBoxLayout(rightWidget);
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->setSpacing(0);

    // Create item widget (hidden by default)
    createItemWidget = new CreateItemWidget(this);
    createItemWidget->hide();

    // Scroll area for right content
    QScrollArea *rightScrollArea = new QScrollArea(this);
    rightScrollArea->setWidgetResizable(true);
    rightScrollArea->setWidget(rightWidget);
    rightScrollArea->setFrameShape(QFrame::NoFrame);
    rightScrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Add widgets to main layout
    mainLayout->addWidget(leftWidget);
    mainLayout->addWidget(rightScrollArea, 1);

    // Initialize JsonManager
    jsonManager = new JsonManager(this);

    // Set minimum window size
    setMinimumSize(900, 600);

    // Load initial data
    if (QFile::exists(currentJsonPath)) {
        loadMediaData(currentJsonPath);
    }

    // Connections
    connect(topMenu, &TopMenuWidget::uploadRequested, this, &MainWindow::handleUploadRequest);
    connect(topMenu, &TopMenuWidget::createRequested, this, &MainWindow::showCreateItemWidget);
    connect(topMenu, &TopMenuWidget::saveRequested, this, &MainWindow::saveCurrentData);
    connect(createItemWidget, &CreateItemWidget::itemCreated, this, &MainWindow::onMediaItemCreated);
}

MainWindow::~MainWindow()
{
    qDeleteAll(mediaCollection);
    delete jsonManager;
}

void MainWindow::setupCategoryButtons()
{
    QStringList categories = {"Tutti", "Film", "Serie Tv", "Anime", "Libri", "Manga", "Cd"};

    for (const QString &category : categories) {
        QPushButton *btn = new QPushButton(category);
        btn->setCheckable(true);
        btn->setChecked(category == "Tutti");
        btn->setStyleSheet(
            "QPushButton {"
            "  text-align: left; padding: 10px;"
            "  border: none; border-radius: 5px;"
            "  margin: 2px;"
            "}"
            "QPushButton:hover { background-color: #f0f0f0; }"
            "QPushButton:checked { "
            "  background-color: #4CAF50; "
            "  color: white;"
            "  font-weight: bold;"
            "}"
        );

        connect(btn, &QPushButton::clicked, this, [this, category]() {
            currentCategory = category;
            displayMediaByCategory(category);

            // Update button states
            for (QPushButton *button : categoryButtons) {
                button->setChecked(button->text() == category);
            }
        });

        categoryButtons[category] = btn;
        leftLayout->addWidget(btn);
    }
}

void MainWindow::setupSearchBar()
{
    searchBar = new QLineEdit();
    searchBar->setPlaceholderText("Cerca per titolo...");
    searchBar->setClearButtonEnabled(true);
    searchBar->setStyleSheet(
        "QLineEdit {"
        "  padding: 5px 10px;"
        "  border: 1px solid #ccc;"
        "  border-radius: 15px;"
        "  min-height: 25px;"
        "  margin: 5px;"
        "}"
    );

    connect(searchBar, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);
    leftLayout->addWidget(searchBar);
}

void MainWindow::loadMediaData(const QString &filePath)
{
    if (jsonManager->loadFromFile(filePath)) {
        clearCurrentMedia();
        qDeleteAll(mediaCollection);
        mediaCollection.clear();

        QVector<Media*> loadedMedia = jsonManager->getAllMedia();
        for (Media* media : loadedMedia) {
            mediaCollection.append(media);
        }

        currentJsonPath = filePath;
        displayMediaByCategory(currentCategory);
    }
}

void MainWindow::displayMediaByCategory(const QString &category)
{
    clearCurrentMedia();

    QString searchText = searchBar->text().toLower();
    
    for (Media* media : mediaCollection) {
        QString mediaType = jsonManager->getMediaTypeName(media);
        QString mediaTitle = QString::fromStdString(media->getTitolo()).toLower();

        if ((category == "Tutti" || mediaType == category) &&
            (searchText.isEmpty() || mediaTitle.contains(searchText))) {
            addMediaCardToLayout(media);
        }
    }

    rightLayout->addStretch();
}

void MainWindow::addMediaCardToLayout(Media* media)
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
    QLabel *typeLabel = new QLabel("Tipo: " + jsonManager->getMediaTypeName(media));

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

    rightLayout->addWidget(mediaCard);
}

QPixmap MainWindow::loadMediaImage(const std::string& imagePath)
{
    QString imageQPath = QString::fromStdString(imagePath);
    QPixmap pixmap;
    
    // 1. Converti il percorso in assoluto se è relativo
    QFileInfo fileInfo(imageQPath);
    if (fileInfo.isRelative()) {
        // Costruisci il percorso assoluto basato sulla directory dell'applicazione
        QString appDir = QCoreApplication::applicationDirPath();
        imageQPath = QDir::cleanPath(appDir + QDir::separator() + imageQPath);
    }
    
    // 2. Prova a caricare l'immagine
    if (!pixmap.load(imageQPath)) {
        // Creazione di un'immagine placeholder con informazioni di debug
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

void MainWindow::clearCurrentMedia()
{
    QLayoutItem* item;
    while ((item = rightLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            item->widget()->deleteLater();
        }
        delete item;
    }
}

void MainWindow::handleUploadRequest()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Seleziona file JSON"),
        QDir::homePath(),
        tr("File JSON (*.json)")
    );
    
    if (!filePath.isEmpty()) {
        loadMediaData(filePath);
        QMessageBox::information(this, "Successo", "File caricato correttamente!");
    }
}

void MainWindow::saveCurrentData()
{
    jsonManager->clearAll();
    for (Media* media : mediaCollection) {
        jsonManager->addMedia(media);
    }

    if (jsonManager->saveToFile(currentJsonPath)) {
        QMessageBox::information(this, "Successo", 
            "Dati salvati correttamente in:\n" + QDir::toNativeSeparators(currentJsonPath));
    } else {
        QMessageBox::critical(this, "Errore",
            "Impossibile salvare i dati.\n"
            "Assicurati di avere i permessi di scrittura per:\n" +
            QDir::toNativeSeparators(currentJsonPath));
    }
}

void MainWindow::showCreateItemWidget()
{
    clearCurrentMedia();
    createItemWidget->show();
    rightLayout->addWidget(createItemWidget);
    rightLayout->addStretch();
}

void MainWindow::onMediaItemCreated(Media* newItem)
{
    if (newItem) {
        mediaCollection.append(newItem);
        jsonManager->addMedia(newItem);
        displayMediaByCategory(currentCategory);
        createItemWidget->hide();
    }
}

void MainWindow::onSearchTextChanged(const QString& text)
{
    Q_UNUSED(text);  // Silenzia l'avviso del parametro non utilizzato
    displayMediaByCategory(currentCategory);
}