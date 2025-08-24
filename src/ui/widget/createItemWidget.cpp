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
    
    createButton->setText("Aggiorna Media");
    createButton->setStyleSheet(StyleUtils::getWarningButtonStyle());
    
    populateFieldsFromMedia(media);
}

void CreateItemWidget::clearEditMode()
{
    editingMedia = nullptr;
    editMode = false;
    
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

    // Polimorfismo per definire il tipo di media
    QString mediaType = QString::fromStdString(media->getMediaType());
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
    
    // Polimorfismo per campi specifici
    auto specificDetails = media->getSpecificDetails();
    
    populateSpecificFieldsFromDetails(fields, specificDetails, mediaType);
}

void CreateItemWidget::populateSpecificFieldsFromDetails(QList<QLineEdit*>& fields, 
    const std::vector<std::pair<std::string, std::string>>& details, const QString& mediaType)
{

    if (mediaType == "Film" && fields.size() >= 6) {
        for (const auto& detail : details) {
            QString key = QString::fromStdString(detail.first);
            QString value = QString::fromStdString(detail.second);
            
            if (key == "Regista" && fields.size() > 3) {
                fields[3]->setText(value);
            } else if (key == "Protagonista" && fields.size() > 4) {
                fields[4]->setText(value);
            } else if (key == "Durata" && fields.size() > 5) {
                // Rimuove " min" dal valore se presente
                QString duration = value;
                duration.replace(" min", "");
                fields[5]->setText(duration);
            }
        }
    } else if ((mediaType == "Serie Tv" || mediaType == "Anime") && fields.size() >= 9) {
        for (const auto& detail : details) {
            QString key = QString::fromStdString(detail.first);
            QString value = QString::fromStdString(detail.second);
            
            if (key == "Episodi" && fields.size() > 3) {
                fields[3]->setText(value);
            } else if (key == "Stagioni" && fields.size() > 4) {
                fields[4]->setText(value);
            } else if (key == "Durata episodio" && fields.size() > 5) {
                QString duration = value;
                duration.replace(" min", "");
                fields[5]->setText(duration);
            } else if (key == "Stato" && fields.size() > 6) {
                fields[6]->setText(value == "In corso" ? "true" : "false");
            } else if ((key == "Ideatore" || key == "Disegnatore") && fields.size() > 7) {
                fields[7]->setText(value);
            } else if ((key == "Casa produttrice" || key == "Studio") && fields.size() > 8) {
                fields[8]->setText(value);
            }
        }
    } else if ((mediaType == "Libro" || mediaType == "Manga") && fields.size() >= 6) {
        for (const auto& detail : details) {
            QString key = QString::fromStdString(detail.first);
            QString value = QString::fromStdString(detail.second);

            if (key == "Scrittore" && fields.size() > 3) {
                fields[3]->setText(value);
            } else if ((key == "Anno di Stampa" || key == "Volumi") && fields.size() > 4) {
                fields[4]->setText(value);
            } else if ((key == "Casa Editrice" || key == "Illustratore") && fields.size() > 5) {
                fields[5]->setText(value);
            } else if (key == "Stato" && fields.size() > 6) {
                fields[6]->setText(value == "Concluso" ? "true" : "false");
            }
        }
    } else if (mediaType == "Cd" && fields.size() >= 6) {
        for (const auto& detail : details) {
            QString key = QString::fromStdString(detail.first);
            QString value = QString::fromStdString(detail.second);

            if (key == "Artista" && fields.size() > 3) {
                fields[3]->setText(value);
            } else if (key == "Tracce" && fields.size() > 4) {
                fields[4]->setText(value);
            } else if (key == "Durata media" && fields.size() > 5) {
                // Rimuove " sec" dal valore se presente
                QString duration = value;
                duration.replace(" sec", "");
                fields[5]->setText(duration);
            }
        }
    }
}

void CreateItemWidget::setMediaService(MediaService* service)
{
    mediaService = service;
}