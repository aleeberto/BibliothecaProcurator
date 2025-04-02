#include "CreateItemWidget.h"

CreateItemWidget::CreateItemWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Seleziona il tipo di oggetto:", this);
    itemTypeCombo = new QComboBox(this);
    stackedFields = new QStackedWidget(this);

    itemTypeCombo->addItems({"Serie Tv", "Anime", "Film", "Libri", "Manga", "Cd"});

    // Aggiungi il layout per ogni tipo di oggetto
    for (int i = 0; i < itemTypeCombo->count(); ++i) {
        QWidget *page = new QWidget();
        QVBoxLayout *pageLayout = new QVBoxLayout(page);
        
        // Aggiungi i campi comuni
        addCommonFields(pageLayout);

        // Aggiungi i campi specifici in base al tipo
        addTypeSpecificFields(pageLayout, itemTypeCombo->itemText(i));

        page->setLayout(pageLayout);
        stackedFields->addWidget(page);
    }

    connect(itemTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &CreateItemWidget::onItemTypeChanged);

    layout->addWidget(label);
    layout->addWidget(itemTypeCombo);
    layout->addWidget(stackedFields);

    setLayout(layout);
    onItemTypeChanged(0); // Mostra la prima scheda
}

void CreateItemWidget::onItemTypeChanged(int index) {
    stackedFields->setCurrentIndex(index);
}

void CreateItemWidget::addCommonFields(QVBoxLayout *layout) {
    layout->addWidget(new QLabel("Nome:"));
    layout->addWidget(new QLineEdit());
    layout->addWidget(new QLabel("Immagine:"));
    layout->addWidget(new QLineEdit());
    layout->addWidget(new QLabel("Anno:"));
    layout->addWidget(new QLineEdit());
}

// Aggiungi i campi comuni per Serie Tv e Anime
void CreateItemWidget::addTvAndAnimeFields(QVBoxLayout *layout) {
    layout->addWidget(new QLabel("Numero Episodi:"));
    layout->addWidget(new QLineEdit());
    layout->addWidget(new QLabel("Numero Stagioni:"));
    layout->addWidget(new QLineEdit());
    layout->addWidget(new QLabel("Durata Media Episodio:"));
    layout->addWidget(new QLineEdit());
    layout->addWidget(new QLabel("In Corso:"));
    layout->addWidget(new QLineEdit());
}

// Aggiungi i campi specifici per ogni tipo
void CreateItemWidget::addTypeSpecificFields(QVBoxLayout *layout, const QString &itemType) {
    if (itemType == "Serie Tv" || itemType == "Anime") {
        addTvAndAnimeFields(layout);  // Aggiunge i campi comuni a Serie Tv e Anime

        if (itemType == "Serie Tv") {
            layout->addWidget(new QLabel("Ideatore:"));
            layout->addWidget(new QLineEdit());
            layout->addWidget(new QLabel("Casa produttrice:"));
            layout->addWidget(new QLineEdit());
        } else if (itemType == "Anime") {
            layout->addWidget(new QLabel("Disegnatore:"));
            layout->addWidget(new QLineEdit());
            layout->addWidget(new QLabel("Studio Animazione:"));
            layout->addWidget(new QLineEdit());
        }

    } else if (itemType == "Film") {
        layout->addWidget(new QLabel("Regista:"));
        layout->addWidget(new QLineEdit());
        layout->addWidget(new QLabel("Attore protagonista:"));
        layout->addWidget(new QLineEdit());
        layout->addWidget(new QLabel("Durata:"));
        layout->addWidget(new QLineEdit());
    } else if (itemType == "Libri" || itemType == "Manga") {
        layout->addWidget(new QLabel("Scrittore:"));
        layout->addWidget(new QLineEdit());

        if (itemType == "Manga") {
            layout->addWidget(new QLabel("Numero Libri:"));
            layout->addWidget(new QLineEdit());
            layout->addWidget(new QLabel("Illustratore:"));
            layout->addWidget(new QLineEdit());
            layout->addWidget(new QLabel("Concluso:"));
            layout->addWidget(new QLineEdit());
        }
    } else if (itemType == "Cd") {
        layout->addWidget(new QLabel("Artista:"));
        layout->addWidget(new QLineEdit());
        layout->addWidget(new QLabel("Numero Tracce:"));
        layout->addWidget(new QLineEdit());
        layout->addWidget(new QLabel("Durata Media Tracce:"));
        layout->addWidget(new QLineEdit());
    }
}
