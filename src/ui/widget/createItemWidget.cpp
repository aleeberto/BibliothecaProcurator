// src/ui/widget/createItemWidget.cpp
#include "createItemWidget.h"
#include <QScrollArea>
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QTimer>
#include <QAbstractScrollArea>
#include "../../services/styleUtils.h"

CreateItemWidget::CreateItemWidget(QWidget *parent) : QWidget(parent), editingMedia(nullptr), editMode(false), mediaService(nullptr)
{
    // No margin solo right layout + scroll area
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    QWidget *formWidget = new QWidget();
    QVBoxLayout *formLayout = new QVBoxLayout(formWidget);
    formLayout->setContentsMargins(15, 15, 15, 15);
    formLayout->setSpacing(10);

    setupTypeSelection();

    stackedFields = new QStackedWidget(formWidget);
    stackedFields->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    // Crea i form per ogni tipo di media
    QStringList mediaTypes = {"Film", "Serie Tv", "Anime", "Libro", "Manga", "Cd"};
    
    for (const QString& type : mediaTypes) {
        createFormForType(type);
        itemTypeCombo->addItem(type);
    }

    // Selezione tipo di media da inserire
    QLabel *label = new QLabel("Seleziona il tipo di oggetto:", formWidget);
    
    formLayout->addWidget(label);
    formLayout->addWidget(itemTypeCombo);
    formLayout->addWidget(stackedFields);

    // Creazione della scroll area del form
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(formWidget);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

    // Bottone creazione Item (fixed in place)
    QWidget *buttonContainer = new QWidget(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonContainer);
    buttonLayout->setContentsMargins(15, 15, 15, 15);
    buttonLayout->setSpacing(0);

    createButton = new QPushButton("✨ Crea Media", buttonContainer);
    createButton->setFixedHeight(48);
    createButton->setStyleSheet(StyleUtils::getPrimaryButtonStyle());

    buttonLayout->addStretch();
    buttonLayout->addWidget(createButton);
    buttonLayout->addStretch();

    mainLayout->addWidget(scrollArea, 1);
    mainLayout->addWidget(buttonContainer, 0);

    setLayout(mainLayout);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Connessioni
    connect(itemTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &CreateItemWidget::onItemTypeChanged);
    connect(createButton, &QPushButton::clicked,
            this, &CreateItemWidget::onCreateButtonClicked);

    onItemTypeChanged(0);
    QTimer::singleShot(0, this, &CreateItemWidget::updateScrollBarVisibility);
}

void CreateItemWidget::setupTypeSelection() {
    itemTypeCombo = new QComboBox();
    itemTypeCombo->setFixedHeight(35);
}

void CreateItemWidget::createFormForType(const QString& type) {
    QWidget* formPage = new QWidget();
    QVBoxLayout* pageLayout = new QVBoxLayout(formPage);
    pageLayout->setContentsMargins(5, 5, 5, 5);
    pageLayout->setSpacing(5);

    // Campi comuni
    addFieldWithPlaceholder(pageLayout, "Titolo:", "Inserisci il titolo");
    addImageField(pageLayout, "Immagine:", "Percorso dell'immagine");
    addFieldWithPlaceholder(pageLayout, "Anno:", "Anno di pubblicazione");

    // Campi specifici per tipo
    if (type == "Film") {
        addFieldWithPlaceholder(pageLayout, "Regista:", "Inserisci Regista");
        addFieldWithPlaceholder(pageLayout, "Attore protagonista:", "Inserisci Attore protagonista");
        addFieldWithPlaceholder(pageLayout, "Durata (min):", "Inserisci Durata (min)");
    } else if (type == "Serie Tv") {
        addFieldWithPlaceholder(pageLayout, "Numero Episodi:", "Inserisci Numero Episodi");
        addFieldWithPlaceholder(pageLayout, "Numero Stagioni:", "Inserisci Numero Stagioni");
        addFieldWithPlaceholder(pageLayout, "Durata Media Episodio (min):", "Inserisci Durata Media Episodio (min)");
        addFieldWithPlaceholder(pageLayout, "In Corso (true/false):", "Inserisci In Corso (true/false)");
        addFieldWithPlaceholder(pageLayout, "Ideatore:", "Inserisci Ideatore");
        addFieldWithPlaceholder(pageLayout, "Casa produttrice:", "Inserisci Casa produttrice");
    } else if (type == "Anime") {
        addFieldWithPlaceholder(pageLayout, "Numero Episodi:", "Inserisci Numero Episodi");
        addFieldWithPlaceholder(pageLayout, "Numero Stagioni:", "Inserisci Numero Stagioni");
        addFieldWithPlaceholder(pageLayout, "Durata Media Episodio (min):", "Inserisci Durata Media Episodio (min)");
        addFieldWithPlaceholder(pageLayout, "In Corso (true/false):", "Inserisci In Corso (true/false)");
        addFieldWithPlaceholder(pageLayout, "Disegnatore:", "Inserisci Disegnatore");
        addFieldWithPlaceholder(pageLayout, "Studio Animazione:", "Inserisci Studio Animazione");
    } else if (type == "Libro") {
        addFieldWithPlaceholder(pageLayout, "Scrittore:", "Inserisci Scrittore");
        addFieldWithPlaceholder(pageLayout, "Anno di stampa:", "Inserisci Anno di stampa");
        addFieldWithPlaceholder(pageLayout, "Casa Editrice:", "Inserisci Casa Editrice");
    } else if (type == "Manga") {
        addFieldWithPlaceholder(pageLayout, "Scrittore:", "Inserisci Scrittore");
        addFieldWithPlaceholder(pageLayout, "Illustratore:", "Inserisci Illustratore");
        addFieldWithPlaceholder(pageLayout, "Numero Libri:", "Inserisci Numero Libri");
        addFieldWithPlaceholder(pageLayout, "Concluso (true/false):", "Inserisci Concluso (true/false)");
    } else if (type == "Cd") {
        addFieldWithPlaceholder(pageLayout, "Artista:", "Inserisci Artista");
        addFieldWithPlaceholder(pageLayout, "Numero Tracce:", "Inserisci Numero Tracce");
        addFieldWithPlaceholder(pageLayout, "Durata Media Tracce (sec):", "Inserisci Durata Media Tracce (sec)");
    }

    formPage->setLayout(pageLayout);
    stackedFields->addWidget(formPage);
    typeWidgets[type] = formPage;
}

void CreateItemWidget::addFieldWithPlaceholder(QVBoxLayout* layout, const QString& labelText, const QString& placeholder) {
    QLabel* label = new QLabel(labelText);
    QLineEdit* input = new QLineEdit();
    input->setPlaceholderText(placeholder);
    input->setMinimumHeight(30);
    input->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    layout->addWidget(label);
    layout->addWidget(input);
}

void CreateItemWidget::addImageField(QVBoxLayout* layout, const QString& labelText, const QString& placeholder) {
    QLabel* label = new QLabel(labelText);
    QHBoxLayout* hLayout = new QHBoxLayout();
    QLineEdit* input = new QLineEdit();
    input->setPlaceholderText(placeholder);
    input->setMinimumHeight(30);
    input->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QPushButton* browseButton = new QPushButton("Browse");
    browseButton->setFixedHeight(30);
    browseButton->setFixedWidth(70);

    hLayout->addWidget(input);
    hLayout->addWidget(browseButton);

    layout->addWidget(label);
    layout->addLayout(hLayout);

    connect(browseButton, &QPushButton::clicked, this, [input, this]() {
        QString filePath = QFileDialog::getOpenFileName(
            this,
            tr("Seleziona immagine"),
            QDir::homePath(),
            tr("Immagini (*.png *.jpg *.jpeg *.bmp *.gif)")
        );
        if (!filePath.isEmpty()) {
            input->setText(filePath);
        }
    });
}

void CreateItemWidget::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    updateScrollBarVisibility();
}

void CreateItemWidget::updateScrollBarVisibility() {
    if (!scrollArea || !scrollArea->widget()) {
        return;
    }
    
    int contentHeight = scrollArea->widget()->sizeHint().height();
    int viewportHeight = scrollArea->viewport()->height();
    
    if (contentHeight <= viewportHeight) {
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    } else {
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    }
}

Media* CreateItemWidget::createMediaItem() const {
    QString type = itemTypeCombo->currentText();
    QWidget* currentPage = stackedFields->currentWidget();
    if (!currentPage) return nullptr;
    
    QList<QLineEdit*> fields = currentPage->findChildren<QLineEdit*>();

    if (!mediaService) {
        QMessageBox::critical(const_cast<QWidget*>(parentWidget()),
            "Errore",
            "MediaService non inizializzato");
        return nullptr;
    }

    return mediaService->createMediaFromFields(type, fields, const_cast<QWidget*>(static_cast<const QWidget*>(this)));
}

void CreateItemWidget::onCreateButtonClicked() {
    if (!createButton->isEnabled()) {
        return;
    }
    
    createButton->setEnabled(false);
    
    Media* newItem = createMediaItem();
    if (newItem) {
        if (editMode && editingMedia) {
            emit itemUpdated(editingMedia, newItem);
            clearEditMode();
        } else {
            emit itemCreated(newItem);
        }

        // Pulisci i campi del form corrente
        QWidget* currentPage = stackedFields->currentWidget();
        if (currentPage) {
            QList<QLineEdit*> fields = currentPage->findChildren<QLineEdit*>();
            for (QLineEdit* field : fields) {
                if (field) {
                    field->clear();
                }
            }
        }
    }
    
    QTimer::singleShot(500, this, [this]() {
        if (createButton) {
            createButton->setEnabled(true);
        }
    });
}

void CreateItemWidget::onItemTypeChanged(int index) {
    stackedFields->setCurrentIndex(index);
    QTimer::singleShot(0, this, &CreateItemWidget::updateScrollBarVisibility);
}

void CreateItemWidget::setEditMode(Media* media) {
    if (!media) return;
    
    editingMedia = media;
    editMode = true;
    
    createButton->setText("Aggiorna Media");
    createButton->setStyleSheet(StyleUtils::getWarningButtonStyle());
    
    // Implementazione semplificata per popolare i campi
    // In questa versione semplificata, gestiamo manualmente i tipi
    populateFieldsFromMedia(media);
}

void CreateItemWidget::populateFieldsFromMedia(Media* media) {
    if (!media) return;

    // Determina il tipo usando dynamic_cast
    QString mediaType;
    if (dynamic_cast<Film*>(media)) {
        mediaType = "Film";
    } else if (dynamic_cast<SerieTv*>(media)) {
        mediaType = "Serie Tv";
    } else if (dynamic_cast<Anime*>(media)) {
        mediaType = "Anime";
    } else if (dynamic_cast<Libro*>(media)) {
        mediaType = "Libro";
    } else if (dynamic_cast<Manga*>(media)) {
        mediaType = "Manga";
    } else if (dynamic_cast<Cd*>(media)) {
        mediaType = "Cd";
    }
    
    int typeIndex = itemTypeCombo->findText(mediaType);
    if (typeIndex != -1) {
        itemTypeCombo->setCurrentIndex(typeIndex);
        stackedFields->setCurrentIndex(typeIndex);
    }
    
    QWidget* currentPage = stackedFields->currentWidget();
    if (!currentPage) return;
    
    QList<QLineEdit*> fields = currentPage->findChildren<QLineEdit*>();
    if (fields.isEmpty()) return;
    
    // Campi comuni
    if (fields.size() > 0) fields[0]->setText(QString::fromStdString(media->getTitolo()));
    if (fields.size() > 1) fields[1]->setText(QString::fromStdString(media->getImmagine()));
    if (fields.size() > 2) fields[2]->setText(QString::number(media->getAnno()));
    
    // Campi specifici usando dynamic_cast
    if (Film* film = dynamic_cast<Film*>(media)) {
        if (fields.size() > 3) fields[3]->setText(QString::fromStdString(film->getRegista()));
        if (fields.size() > 4) fields[4]->setText(QString::fromStdString(film->getAttoreProtagonista()));
        if (fields.size() > 5) fields[5]->setText(QString::number(film->getDurata()));
    } else if (SerieTv* serie = dynamic_cast<SerieTv*>(media)) {
        if (fields.size() > 3) fields[3]->setText(QString::number(serie->getNumEpisodi()));
        if (fields.size() > 4) fields[4]->setText(QString::number(serie->getNumStagioni()));
        if (fields.size() > 5) fields[5]->setText(QString::number(serie->getDurataMediaEp()));
        if (fields.size() > 6) fields[6]->setText(serie->getInCorso() ? "true" : "false");
        if (fields.size() > 7) fields[7]->setText(QString::fromStdString(serie->getIdeatore()));
        if (fields.size() > 8) fields[8]->setText(QString::fromStdString(serie->getCasaProduttrice()));
    } else if (Anime* anime = dynamic_cast<Anime*>(media)) {
        if (fields.size() > 3) fields[3]->setText(QString::number(anime->getNumEpisodi()));
        if (fields.size() > 4) fields[4]->setText(QString::number(anime->getNumStagioni()));
        if (fields.size() > 5) fields[5]->setText(QString::number(anime->getDurataMediaEp()));
        if (fields.size() > 6) fields[6]->setText(anime->getInCorso() ? "true" : "false");
        if (fields.size() > 7) fields[7]->setText(QString::fromStdString(anime->getDisegnatore()));
        if (fields.size() > 8) fields[8]->setText(QString::fromStdString(anime->getStudioAnimazione()));
    } else if (Libro* libro = dynamic_cast<Libro*>(media)) {
        if (fields.size() > 3) fields[3]->setText(QString::fromStdString(libro->getScrittore()));
        if (fields.size() > 4) fields[4]->setText(QString::number(libro->getAnnoStampa()));
        if (fields.size() > 5) fields[5]->setText(QString::fromStdString(libro->getCasaEditrice()));
    } else if (Manga* manga = dynamic_cast<Manga*>(media)) {
        if (fields.size() > 3) fields[3]->setText(QString::fromStdString(manga->getScrittore()));
        if (fields.size() > 4) fields[4]->setText(QString::fromStdString(manga->getIllustratore()));
        if (fields.size() > 5) fields[5]->setText(QString::number(manga->getNumLibri()));
        if (fields.size() > 6) fields[6]->setText(manga->getConcluso() ? "true" : "false");
    } else if (Cd* cd = dynamic_cast<Cd*>(media)) {
        if (fields.size() > 3) fields[3]->setText(QString::fromStdString(cd->getArtista()));
        if (fields.size() > 4) fields[4]->setText(QString::number(cd->getNumTracce()));
        if (fields.size() > 5) fields[5]->setText(QString::number(cd->getDurataMedTracce()));
    }
}

void CreateItemWidget::clearEditMode() {
    editingMedia = nullptr;
    editMode = false;
    
    createButton->setText("Crea Media");
    createButton->setStyleSheet(StyleUtils::getPrimaryButtonStyle());
}

bool CreateItemWidget::isInEditMode() const {
    return editMode;
}

void CreateItemWidget::setMediaService(MediaService* service) {
    mediaService = service;
}