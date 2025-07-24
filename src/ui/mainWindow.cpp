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
    rightLayoutWidget = new RightLayoutWidget(this);
    
    // Scroll area for right content
    QScrollArea *rightScrollArea = new QScrollArea(this);
    rightScrollArea->setWidgetResizable(true);
    rightScrollArea->setWidget(rightLayoutWidget);
    rightScrollArea->setFrameShape(QFrame::NoFrame);
    rightScrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Add widgets to main layout
    mainLayout->addWidget(leftWidget);
    mainLayout->addWidget(rightScrollArea, 1);

    // Initialize jsonService
    jsonService = new JsonService(this);

    // Set minimum window size
    setMinimumSize(900, 600);

    // Create item widget (hidden by default)
    createItemWidget = new CreateItemWidget(this);
    createItemWidget->hide();

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
    delete jsonService;
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
            rightLayoutWidget->displayMediaByCategory(category, searchBar->text());

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
    if (jsonService->loadFromFile(filePath)) {
        qDeleteAll(mediaCollection);
        mediaCollection.clear();

        QVector<Media*> loadedMedia = jsonService->getAllMedia();
        for (Media* media : loadedMedia) {
            mediaCollection.append(media);
        }

        currentJsonPath = filePath;
        rightLayoutWidget->setMediaCollection(mediaCollection);
        rightLayoutWidget->setJsonService(jsonService);
        rightLayoutWidget->displayMediaByCategory(currentCategory);
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
    jsonService->clearAll();
    for (Media* media : mediaCollection) {
        jsonService->addMedia(media);
    }

    if (jsonService->saveToFile(currentJsonPath)) {
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
    rightLayoutWidget->showCreateItemWidget(createItemWidget);
}

void MainWindow::onMediaItemCreated(Media* newItem)
{
    if (newItem) {
        mediaCollection.append(newItem);
        jsonService->addMedia(newItem);
        rightLayoutWidget->displayMediaByCategory(currentCategory);
    }
}

void MainWindow::onSearchTextChanged(const QString& text)
{
    rightLayoutWidget->displayMediaByCategory(currentCategory, text);
}
