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

    // Selezione tipo di media da inserire
    QLabel *label = new QLabel("Seleziona il tipo di oggetto:", formWidget);
    itemTypeCombo = new QComboBox(formWidget);
    itemTypeCombo->setFixedHeight(35);

    stackedFields = new QStackedWidget(formWidget);
    stackedFields->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    // Input label per ogni media (no common fields)
    QMap<QString, QStringList> mediaFields = {
        {"Serie Tv", {"Numero Episodi", "Numero Stagioni", "Durata Media Episodio (min)", "In Corso (true/false)", "Ideatore", "Casa produttrice"}},
        {"Anime", {"Numero Episodi", "Numero Stagioni", "Durata Media Episodio (min)", "In Corso (true/false)", "Disegnatore", "Studio Animazione"}},
        {"Film", {"Regista", "Attore protagonista", "Durata (min)"}},
        {"Libro", {"Scrittore", "Anno di stampa", "Casa Editrice"}},
        {"Manga", {"Scrittore", "Numero Libri", "Illustratore", "Concluso (true/false)"}},
        {"Cd", {"Artista", "Numero Tracce", "Durata Media Tracce (sec)"}}
    };

    // Crea il form
    for (const QString& type : mediaFields.keys()) {
        QWidget* page = new QWidget(formWidget);
        QVBoxLayout* pageLayout = new QVBoxLayout(page);
        pageLayout->setContentsMargins(5, 5, 5, 5);
        pageLayout->setSpacing(5);

        // Common fields
        addFieldWithPlaceholder(pageLayout, "Titolo:", "Inserisci il titolo");
        addFieldWithPlaceholder(pageLayout, "Immagine:", "Percorso dell'immagine");
        addFieldWithPlaceholder(pageLayout, "Anno:", "Anno di pubblicazione");

        // Specific fields
        for (const QString& field : mediaFields[type]) {
            addFieldWithPlaceholder(pageLayout, field + ":", "Inserisci " + field);
        }

        page->setLayout(pageLayout);
        stackedFields->addWidget(page);
        itemTypeCombo->addItem(type);
    }

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

    mainLayout->addWidget(scrollArea, 1); // stretch = 1 occupa tutto lo spazio
    mainLayout->addWidget(buttonContainer, 0); // stretch = 0 altezza fissa bottone

    setLayout(mainLayout);
    
    // policy di dimensionamento tutto lo spazio disponibile
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Connessioni
    connect(itemTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &CreateItemWidget::onItemTypeChanged);
    connect(createButton, &QPushButton::clicked,
            this, &CreateItemWidget::onCreateButtonClicked);

    onItemTypeChanged(0);
    
    QTimer::singleShot(0, this, &CreateItemWidget::updateScrollBarVisibility);
}

void CreateItemWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    updateScrollBarVisibility();
}

// Controlli della scrollbar(non visibile se il contenuto è minore della viewport)

void CreateItemWidget::updateScrollBarVisibility()
{
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

// Aggiunge un campo con etichetta e placeholder      

void CreateItemWidget::addFieldWithPlaceholder(QVBoxLayout* layout, const QString& labelText, const QString& placeholder)
{
    if (labelText == "Immagine:") {
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

        // Tasto Browse per selezionare un file immagine, apre un file dialog
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
    } else {
        QLabel* label = new QLabel(labelText);
        QLineEdit* input = new QLineEdit();
        input->setPlaceholderText(placeholder);
        input->setMinimumHeight(30);
        input->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        layout->addWidget(label);
        layout->addWidget(input);
    }
}

Media* CreateItemWidget::createMediaItem() const
{
    int index = itemTypeCombo->currentIndex();
    QWidget* currentPage = stackedFields->widget(index);
    QList<QLineEdit*> fields = currentPage->findChildren<QLineEdit*>();
    QString type = itemTypeCombo->currentText();

    if (!mediaService) {
        QMessageBox::critical(const_cast<QWidget*>(parentWidget()),
            "Errore",
            "MediaService non inizializzato");
        return nullptr;
    }

    return mediaService->createMediaFromFields(type, fields, const_cast<QWidget*>(static_cast<const QWidget*>(this)));
}

void CreateItemWidget::onCreateButtonClicked()
{
    // Troppi click consecutivi davano errore dunqeu controllati(Segmentation Fault)
    if (!createButton->isEnabled()) {
        return;
    }
    
    createButton->setEnabled(false);
    
    Media* newItem = createMediaItem();
    if (newItem) {
        if (editMode && editingMedia) {
            // Modalità modifica
            emit itemUpdated(editingMedia, newItem);
            clearEditMode();
        } else {
            // Modalità creazione
            emit itemCreated(newItem);
        }

        // Pulizia dei campi dopo la creazione
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
    
    // Riattivazione del bottone (correzzione Segmentation Fault)
    QTimer::singleShot(500, this, [this]() {
        if (createButton) {
            createButton->setEnabled(true);
        }
    });
}

void CreateItemWidget::onItemTypeChanged(int index)
{
    stackedFields->setCurrentIndex(index);
    QTimer::singleShot(0, this, &CreateItemWidget::updateScrollBarVisibility);
}

void CreateItemWidget::setEditMode(Media* media)
{
    if (!media) return;
    
    editingMedia = media;
    editMode = true;
    
    // Cambia il testo del bottone
    createButton->setText("Aggiorna Media");
    createButton->setStyleSheet(StyleUtils::getWarningButtonStyle());
    
    // Precompila i campi con i dati del media
    populateFieldsFromMedia(media);
}

void CreateItemWidget::clearEditMode()
{
    editingMedia = nullptr;
    editMode = false;
    
    // Ripristina il testo del bottone
    createButton->setText("Crea Media");
    createButton->setStyleSheet(StyleUtils::getPrimaryButtonStyle());
}

bool CreateItemWidget::isInEditMode() const
{
    return editMode;
}


void CreateItemWidget::populateFieldsFromMedia(Media* media)
{
    if (!media) return;
    
    // Determina il tipo di media e seleziona il combo box appropriato
    QString mediaType = MediaTypeUtils::getMediaTypeName(media);
    int typeIndex = itemTypeCombo->findText(mediaType);
    if (typeIndex != -1) {
        itemTypeCombo->setCurrentIndex(typeIndex);
        stackedFields->setCurrentIndex(typeIndex);
    }
    
    // Ottieni i campi della pagina corrente
    QWidget* currentPage = stackedFields->currentWidget();
    if (!currentPage) return;
    
    QList<QLineEdit*> fields = currentPage->findChildren<QLineEdit*>();
    if (fields.isEmpty()) return;
    
    // Campi comuni per tutti i media
    if (fields.size() > 0) fields[0]->setText(QString::fromStdString(media->getTitolo()));
    if (fields.size() > 1) fields[1]->setText(QString::fromStdString(media->getImmagine()));
    if (fields.size() > 2) fields[2]->setText(QString::number(media->getAnno()));
    
    // Campi specifici per tipo di media
    if (auto film = dynamic_cast<Film*>(media)) {
        if (fields.size() > 3) fields[3]->setText(QString::fromStdString(film->getRegista()));
        if (fields.size() > 4) fields[4]->setText(QString::fromStdString(film->getAttoreProtagonista()));
        if (fields.size() > 5) fields[5]->setText(QString::number(film->getDurata()));
    }
    else if (auto serie = dynamic_cast<SerieTv*>(media)) {
        if (fields.size() > 3) fields[3]->setText(QString::number(serie->getNumEpisodi()));
        if (fields.size() > 4) fields[4]->setText(QString::number(serie->getNumStagioni()));
        if (fields.size() > 5) fields[5]->setText(QString::number(serie->getDurataMediaEp()));
        if (fields.size() > 6) fields[6]->setText(serie->getInCorso() ? "true" : "false");
        if (fields.size() > 7) fields[7]->setText(QString::fromStdString(serie->getIdeatore()));
        if (fields.size() > 8) fields[8]->setText(QString::fromStdString(serie->getCasaProduttrice()));
    }
    else if (auto anime = dynamic_cast<Anime*>(media)) {
        if (fields.size() > 3) fields[3]->setText(QString::number(anime->getNumEpisodi()));
        if (fields.size() > 4) fields[4]->setText(QString::number(anime->getNumStagioni()));
        if (fields.size() > 5) fields[5]->setText(QString::number(anime->getDurataMediaEp()));
        if (fields.size() > 6) fields[6]->setText(anime->getInCorso() ? "true" : "false");
        if (fields.size() > 7) fields[7]->setText(QString::fromStdString(anime->getDisegnatore()));
        if (fields.size() > 8) fields[8]->setText(QString::fromStdString(anime->getStudioAnimazione()));
    }
    else if (auto libro = dynamic_cast<Libro*>(media)) {
        if (fields.size() > 3) fields[3]->setText(QString::fromStdString(libro->getScrittore()));
        if (fields.size() > 4) fields[4]->setText(QString::number(libro->getAnnoStampa()));
        if (fields.size() > 5) fields[5]->setText(QString::fromStdString(libro->getCasaEditrice()));
    }
    else if (auto manga = dynamic_cast<Manga*>(media)) {
        if (fields.size() > 3) fields[3]->setText(QString::fromStdString(manga->getScrittore()));
        if (fields.size() > 4) fields[4]->setText(QString::number(manga->getNumLibri()));
        if (fields.size() > 5) fields[5]->setText(QString::fromStdString(manga->getIllustratore()));
        if (fields.size() > 6) fields[6]->setText(manga->getConcluso() ? "true" : "false");
    }
    else if (auto cd = dynamic_cast<Cd*>(media)) {
        if (fields.size() > 3) fields[3]->setText(QString::fromStdString(cd->getArtista()));
        if (fields.size() > 4) fields[4]->setText(QString::number(cd->getNumTracce()));
        if (fields.size() > 5) fields[5]->setText(QString::number(cd->getDurataMedTracce()));
    }
}

void CreateItemWidget::setMediaService(MediaService* service)
{
    mediaService = service;
}
