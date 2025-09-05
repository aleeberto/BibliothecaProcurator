#include "createItemWidget.h"
#include "formWidgetVisitor.h"  // Include qui nel cpp
#include <QScrollArea>
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QTimer>
#include <QAbstractScrollArea>
#include "../../services/styleUtils.h"
#include "../../logic/film.h"
#include "../../logic/serieTv.h"
#include "../../logic/anime.h"
#include "../../logic/libro.h"
#include "../../logic/manga.h"
#include "../../logic/cd.h"

CreateItemWidget::CreateItemWidget(QWidget *parent) : QWidget(parent), editingMedia(nullptr), editMode(false), mediaService(nullptr), formVisitor(nullptr)
{
    // Inizializza il visitor
    formVisitor = new FormWidgetVisitor(this);
    
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

    // Crea i form per ogni tipo di media usando il visitor
    QStringList mediaTypes = {"Film", "Serie Tv", "Anime", "Libro", "Manga", "Cd"};
    
    for (const QString& type : mediaTypes) {
        QWidget* formPage = nullptr;
        
        if (type == "Film") {
            Film* dummyFilm = nullptr;
            formVisitor->visit(dummyFilm);
            formPage = formVisitor->getResultWidget();
        } else if (type == "Serie Tv") {
            SerieTv* dummySerie = nullptr;
            formVisitor->visit(dummySerie);
            formPage = formVisitor->getResultWidget();
        } else if (type == "Anime") {
            Anime* dummyAnime = nullptr;
            formVisitor->visit(dummyAnime);
            formPage = formVisitor->getResultWidget();
        } else if (type == "Libro") {
            Libro* dummyLibro = nullptr;
            formVisitor->visit(dummyLibro);
            formPage = formVisitor->getResultWidget();
        } else if (type == "Manga") {
            Manga* dummyManga = nullptr;
            formVisitor->visit(dummyManga);
            formPage = formVisitor->getResultWidget();
        } else if (type == "Cd") {
            Cd* dummyCd = nullptr;
            formVisitor->visit(dummyCd);
            formPage = formVisitor->getResultWidget();
        }
        
        if (formPage) {
            typeWidgets[type] = formPage;
            stackedFields->addWidget(formPage);
            itemTypeCombo->addItem(type);
        }
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

void CreateItemWidget::setupTypeSelection() {
    itemTypeCombo = new QComboBox();
    itemTypeCombo->setFixedHeight(35);
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

Media* CreateItemWidget::createMediaItem() const
{
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
    
    // Usa il visitor per popolare i campi del form
    if (formVisitor) {
        media->accept(formVisitor);
        QWidget* formWidget = formVisitor->getResultWidget();
        
        if (formWidget) {
            // Trova il tipo corretto e cambia il combo box
            for (int i = 0; i < itemTypeCombo->count(); ++i) {
                QString itemType = itemTypeCombo->itemText(i);
                QWidget* typeWidget = typeWidgets.value(itemType);
                
                if (typeWidget == formWidget) {
                    itemTypeCombo->setCurrentIndex(i);
                    stackedFields->setCurrentIndex(i);
                    break;
                }
            }
        }
    }
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

void CreateItemWidget::setMediaService(MediaService* service)
{
    mediaService = service;
}