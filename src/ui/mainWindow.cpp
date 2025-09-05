#include "mainWindow.h"
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
#include <QCoreApplication>
#include "../services/styleUtils.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setStyleSheet(StyleUtils::getMainWindowStyle());
    setWindowTitle("Bibliotheca Procurator");

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setStyleSheet(StyleUtils::getContentAreaStyle());
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Left widget - Menu (4 bottoni del top menu) e categorie
    QWidget *leftWidget = new QWidget();
    leftWidget->setStyleSheet(StyleUtils::getSidebarStyle());
    leftWidget->setFixedWidth(280);

    leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->setContentsMargins(5, 10, 5, 10);
    leftLayout->setSpacing(5);

    topMenu = new TopMenuWidget(this);
    leftLayout->addWidget(topMenu);

    setupSearchBar();

    setupCategoryButtons();

    leftLayout->addStretch();

    // Right widget - Main content
    rightLayoutWidget = new RightLayoutWidget(this);
    
    QScrollArea *rightScrollArea = new QScrollArea(this);
    rightScrollArea->setWidgetResizable(true);
    rightScrollArea->setWidget(rightLayoutWidget);
    rightScrollArea->setFrameShape(QFrame::NoFrame);
    rightScrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout->addWidget(leftWidget);
    mainLayout->addWidget(rightScrollArea, 1);

    // Inizializzazione dei servizi
    jsonService = new JsonService(this);
    mediaService = new MediaService(this);
    mediaService->setJsonService(jsonService);
    
    uiService = new UIService(this);
    rightLayoutWidget->setUIService(uiService);

    // Grandezza minima della finestra principale
    setMinimumSize(1150, 600);

    // Creazione dell Item per la creazione degli item :) (nascosto di base)
    createItemWidget = new CreateItemWidget(this);
    createItemWidget->setObjectName("CreateItemWidget");
    createItemWidget->setMediaService(mediaService);
    createItemWidget->hide();

    // Carica il db di default (vedere se tenerlo o caricare app pulita in first start)
    if (QFile::exists(currentJsonPath)) {
        loadMediaData(currentJsonPath);
    }

    // Connections
    connect(topMenu, &TopMenuWidget::uploadRequested, this, &MainWindow::handleUploadRequest);
    connect(topMenu, &TopMenuWidget::createRequested, this, &MainWindow::showCreateItemWidget);
    connect(topMenu, &TopMenuWidget::newexportRequested, this, &MainWindow::handleExportRequest);
    connect(topMenu, &TopMenuWidget::closeRequested, this, &MainWindow::handleCloseRequest);
    connect(createItemWidget, &CreateItemWidget::itemCreated, this, &MainWindow::onMediaItemCreated);
    connect(createItemWidget, &CreateItemWidget::itemUpdated, this, &MainWindow::onMediaItemUpdated);
    connect(rightLayoutWidget, &RightLayoutWidget::mediaEditRequested, this, &MainWindow::onMediaEditRequested);
    connect(rightLayoutWidget, &RightLayoutWidget::mediaDeleteRequested, this, &MainWindow::onMediaDeleteRequested);
}

MainWindow::~MainWindow()
{
    // MediaService gestisce automaticamente la pulizia della collezione
    delete mediaService;
    delete jsonService;
}

void MainWindow::setupCategoryButtons()
{
    QStringList categories = {"Tutti", "Film", "Serie Tv", "Anime", "Libro", "Manga", "Cd"};

    for (const QString &category : categories) {
        QPushButton *btn = new QPushButton(category);
        btn->setCheckable(true);
        btn->setChecked(category == "Tutti");
        QString categoryButtonStyle = QString(
            "QPushButton {"
            "  text-align: left;"
            "  padding: 12px 16px;"
            "  border: none;"
            "  border-radius: 8px;"
            "  margin: 2px 0px;"
            "  font-size: 14px;"
            "  font-weight: 500;"
            "  color: %1;"
            "  background-color: transparent;"
            "}"
            "QPushButton:hover {"
            "  background-color: %2;"
            "  color: %3;"
            "}"
            "QPushButton:checked {"
            "  background-color: %4;"
            "  color: white;"
            "  font-weight: 600;"
            "}"
        ).arg(StyleUtils::getTextSecondaryColor(), 
              StyleUtils::getSurfaceColor(), 
              StyleUtils::getTextColor(),
              StyleUtils::getPrimaryColor());
        
        btn->setStyleSheet(categoryButtonStyle);

        connect(btn, &QPushButton::clicked, this, [this, category]() {
            currentCategory = category;
            
            // Usa MediaService per filtrare i media con polimorfismo
            QVector<Media*> filteredMedia = mediaService->filterMedia(category, searchBar->text());
            rightLayoutWidget->setMediaCollection(filteredMedia);
            rightLayoutWidget->setJsonService(jsonService);
            rightLayoutWidget->displayMediaCollection();

            // Modifiche ai bottoni delle categorie
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
    searchBar->setStyleSheet(StyleUtils::getSearchBarStyle());
    searchBar->setFixedHeight(44);

    connect(searchBar, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);
    leftLayout->addWidget(searchBar);
}

void MainWindow::loadMediaData(const QString &filePath)
{
    if (mediaService->loadFromFile(filePath)) {
        currentJsonPath = filePath;
        
        // Aggiorna la visualizzazione con i media filtrati usando polimorfismo
        QVector<Media*> filteredMedia = mediaService->filterMedia(currentCategory, searchBar->text());
        rightLayoutWidget->setMediaCollection(filteredMedia);
        rightLayoutWidget->setJsonService(jsonService);
        rightLayoutWidget->displayMediaCollection();
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

void MainWindow::handleExportRequest()
{
    QString filePath = QFileDialog::getSaveFileName(
        this,
        tr("Esporta biblioteca in JSON"),
        QDir::homePath() + "/biblioteca_export.json",
        tr("File JSON (*.json)")
    );
    
    if (!filePath.isEmpty()) {
        // Check se il file è json
        if (!filePath.endsWith(".json", Qt::CaseInsensitive)) {
            filePath += ".json";
        }
        
        if (mediaService->saveToFile(filePath)) {
            QMessageBox::information(this, "Successo", 
                "Biblioteca esportata correttamente in:\n" + QDir::toNativeSeparators(filePath));
            
            // Finestra di dialogo per chiedere se aprire il file esportato
            QMessageBox::StandardButton reply = QMessageBox::question(
                this,
                "Apri file esportato",
                "Vuoi aprire il file appena esportato come biblioteca corrente?",
                QMessageBox::Yes | QMessageBox::No,
                QMessageBox::No
            );
            
            if (reply == QMessageBox::Yes) {
                loadMediaData(filePath);
                QMessageBox::information(this, "Successo", "File caricato come biblioteca corrente!");
            }
        } else {
            QMessageBox::critical(this, "Errore",
                "Impossibile esportare i dati in:\n" + QDir::toNativeSeparators(filePath) +
                "\n\nAssicurati di avere i permessi di scrittura per questa posizione.");
        }
    }
}

void MainWindow::showCreateItemWidget()
{
    // check widget sia in modalità creazione
    createItemWidget->clearEditMode();
    rightLayoutWidget->showCreateItemWidget(createItemWidget);
}

void MainWindow::onMediaItemCreated(Media* newItem)
{
    if (newItem) {
        // Aggiungo il media tramite MediaService
        if (mediaService->addMedia(newItem)) {
            // Salva i dati nel file JSON
            if (mediaService->saveToFile(currentJsonPath)) {
                qDebug() << "Media salvato automaticamente in:" << currentJsonPath;
                
                // Finestra di dialogo per confermare la creazione
                QMessageBox::information(this, "Successo", 
                    "Media creato e salvato correttamente!\n" + 
                    QString::fromStdString(newItem->getTitolo()) + " è stato aggiunto alla biblioteca.");
            } else {
                QMessageBox::warning(this, "Attenzione",
                    "Media creato ma non è stato possibile salvarlo automaticamente.\n"
                    "Usa il pulsante 'Salva' per salvare manualmente i dati.");
            }
            
            QVector<Media*> filteredMedia = mediaService->filterMedia(currentCategory, searchBar->text());
            rightLayoutWidget->setMediaCollection(filteredMedia);
            rightLayoutWidget->displayMediaCollection();
        }
    }
}

void MainWindow::onSearchTextChanged(const QString& text)
{
    QVector<Media*> filteredMedia = mediaService->filterMedia(currentCategory, text);
    rightLayoutWidget->setMediaCollection(filteredMedia);
    rightLayoutWidget->displayMediaCollection();
}

void MainWindow::onMediaEditRequested(Media* media)
{
    if (!media) return;
    
    // Mostra il widget in modalità modifica
    rightLayoutWidget->showCreateItemWidget(createItemWidget);
    
    // Imposta la modalità di modifica con i dati del media
    createItemWidget->setEditMode(media);
}

void MainWindow::onMediaDeleteRequested(Media* media)
{
    if (!media) return;
    
    // Chiedi conferma all'utente
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Conferma Eliminazione",
        QString("Sei sicuro di voler eliminare '%1'?\n\nQuesta operazione non può essere annullata.")
            .arg(QString::fromStdString(media->getTitolo())),
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        QString mediaTitle = QString::fromStdString(media->getTitolo());
        
        // Elimina il media tramite MediaService
        if (mediaService->deleteMedia(media)) {
            if (mediaService->saveToFile(currentJsonPath)) {
                qDebug() << "Media eliminato" << currentJsonPath;
                
                QMessageBox::information(this, "Successo", 
                    QString("'%1' è stato eliminato correttamente dalla biblioteca.")
                        .arg(mediaTitle));
                
                // Aggiorna la visualizzazione con i media filtrati
                QVector<Media*> filteredMedia = mediaService->filterMedia(currentCategory, searchBar->text());
                rightLayoutWidget->setMediaCollection(filteredMedia);
                rightLayoutWidget->displayMediaCollection();
                
            } else {
                QMessageBox::critical(this, "Errore",
                    "Impossibile salvare le modifiche.\n"
                    "Il media è stato rimosso dalla visualizzazione ma la biblioteca non potrebbe essere aggiornata.");
            }
        }
    }
}

void MainWindow::onMediaItemUpdated(Media* oldMedia, Media* newMedia)
{
    if (!oldMedia || !newMedia) return;
    
    // Aggiorna il media tramite MediaService
    if (mediaService->updateMedia(oldMedia, newMedia)) {
        if (mediaService->saveToFile(currentJsonPath)) {
            qDebug() << "Media aggiornato e salvato:" << currentJsonPath;
            
            QMessageBox::information(this, "Successo", 
                QString("'%1' è stato aggiornato")
                    .arg(QString::fromStdString(newMedia->getTitolo())));
            
            // Aggiorna la visualizzazione con i media filtrati
            QVector<Media*> filteredMedia = mediaService->filterMedia(currentCategory, searchBar->text());
            rightLayoutWidget->setMediaCollection(filteredMedia);
            rightLayoutWidget->displayMediaCollection();
            
        } else {
            QMessageBox::critical(this, "Errore",
                "Impossibile salvare le modifiche.\n"
                "Il media è stato aggiornato nella visualizzazione ma la biblioteca non potrebbe essere aggiornata.");
        }
    }
}

void MainWindow::handleCloseRequest()
{
    // Finestra di dialogo per confermare la chiusura della biblioteca
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Chiudi Biblioteca",
        "Sei sicuro di voler chiudere la biblioteca corrente?\n",
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        // Pulisci tutti i dati
        mediaService->clearMediaCollection();
        
        // Resetta il percorso del file corrente
        currentJsonPath = "";
        
        // Resetta la categoria corrente
        currentCategory = "Tutti";
        
        // Pulisci la barra di ricerca
        searchBar->clear();
        
        // Resetta i pulsanti delle categorie
        for (auto it = categoryButtons.begin(); it != categoryButtons.end(); ++it) {
            it.value()->setChecked(it.key() == "Tutti");
        }
        
        // Pulisci la visualizzazione
        rightLayoutWidget->setMediaCollection(QVector<Media*>());
        rightLayoutWidget->displayMediaCollection();
        
        QMessageBox::information(this, "Biblioteca Chiusa", "La biblioteca è stata chiusa correttamente.");
    }
}