#include "createItemWidget.h"
#include <QScrollArea>
#include <QDebug>

CreateItemWidget::CreateItemWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QWidget *scrollContent = new QWidget();
    QVBoxLayout *contentLayout = new QVBoxLayout(scrollContent);
    contentLayout->setContentsMargins(15, 15, 15, 15);
    contentLayout->setSpacing(15);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(scrollContent);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QLabel *label = new QLabel("Seleziona il tipo di oggetto:", scrollContent);
    itemTypeCombo = new QComboBox(scrollContent);
    itemTypeCombo->setFixedHeight(35);

    stackedFields = new QStackedWidget(scrollContent);
    stackedFields->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    QMap<QString, QStringList> mediaFields = {
        {"Serie Tv", {"Numero Episodi", "Numero Stagioni", "Durata Media Episodio (min)", "In Corso (true/false)", "Ideatore", "Casa produttrice"}},
        {"Anime", {"Numero Episodi", "Numero Stagioni", "Durata Media Episodio (min)", "In Corso (true/false)", "Disegnatore", "Studio Animazione"}},
        {"Film", {"Regista", "Attore protagonista", "Durata (min)"}},
        {"Libri", {"Scrittore", "Anno di stampa", "Casa Editrice"}},
        {"Manga", {"Scrittore", "Numero Libri", "Illustratore", "Concluso (true/false)"}},
        {"Cd", {"Artista", "Numero Tracce", "Durata Media Tracce (sec)"}}
    };

    for (const QString& type : mediaFields.keys()) {
        QWidget* page = new QWidget(scrollContent);
        QVBoxLayout* pageLayout = new QVBoxLayout(page);
        pageLayout->setContentsMargins(5, 5, 5, 5);
        pageLayout->setSpacing(8);

        addFieldWithPlaceholder(pageLayout, "Titolo:", "Inserisci il titolo");

        // Create horizontal layout for image input and browse button
        QHBoxLayout* imageLayout = new QHBoxLayout();
        QLineEdit* imageInput = new QLineEdit();
        imageInput->setPlaceholderText("Percorso dell'immagine");
        imageInput->setMinimumHeight(30);
        imageInput->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        imageLayout->addWidget(new QLabel("Immagine:"));
        imageLayout->addWidget(imageInput);
        imageLayout->addWidget(browseImageButton);
        pageLayout->addLayout(imageLayout);

        addFieldWithPlaceholder(pageLayout, "Anno:", "Anno di pubblicazione");

        for (const QString& field : mediaFields[type]) {
            addFieldWithPlaceholder(pageLayout, field + ":", "Inserisci " + field);
        }

        pageLayout->addStretch();
        page->setLayout(pageLayout);
        stackedFields->addWidget(page);
        itemTypeCombo->addItem(type);
    }

    createButton = new QPushButton("Crea Media", scrollContent);
    createButton->setFixedHeight(40);
    createButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #4CAF50;"
        "  color: white;"
        "  border: none;"
        "  border-radius: 5px;"
        "  font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #45a049; }"
        "QPushButton:pressed { background-color: #3d8b40; }"
    );

    browseImageButton = new QPushButton("Sfoglia Immagine", scrollContent);
    browseImageButton->setFixedHeight(30);
    browseImageButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #2196F3;"
        "  color: white;"
        "  border: none;"
        "  border-radius: 5px;"
        "  font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #1976D2; }"
        "QPushButton:pressed { background-color: #1565C0; }"
    );

    connect(itemTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &CreateItemWidget::onItemTypeChanged);
    connect(createButton, &QPushButton::clicked,
            this, &CreateItemWidget::onCreateButtonClicked);
    connect(browseImageButton, &QPushButton::clicked,
            this, &CreateItemWidget::onBrowseImageClicked);

    contentLayout->addWidget(label);
    contentLayout->addWidget(itemTypeCombo);
    contentLayout->addWidget(stackedFields);
    contentLayout->addWidget(browseImageButton);
    contentLayout->addWidget(createButton);

    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);
    onItemTypeChanged(0);
}

void CreateItemWidget::addFieldWithPlaceholder(QVBoxLayout* layout, const QString& labelText, const QString& placeholder)
{
    QLabel* label = new QLabel(labelText);
    QLineEdit* input = new QLineEdit();
    input->setPlaceholderText(placeholder);
    input->setMinimumHeight(30);
    input->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    layout->addWidget(label);
    layout->addWidget(input);
}

Media* CreateItemWidget::createMediaItem() const
{
    int index = itemTypeCombo->currentIndex();
    QWidget* currentPage = stackedFields->widget(index);
    QList<QLineEdit*> fields = currentPage->findChildren<QLineEdit*>();
    QString type = itemTypeCombo->currentText();

    // Validate all fields are filled
    for (QLineEdit* field : fields) {
        if (field->text().isEmpty()) {
            QMessageBox::warning(const_cast<QWidget*>(parentWidget()),
                "Attenzione",
                QString("Il campo '%1' è obbligatorio!").arg(field->placeholderText()));
            field->setFocus();
            return nullptr;
        }
    }

    try {
        if (type == "Serie Tv") {
            bool inCorso;
            QString inCorsoStr = fields[6]->text().toLower();
            if (inCorsoStr == "true" || inCorsoStr == "1") inCorso = true;
            else if (inCorsoStr == "false" || inCorsoStr == "0") inCorso = false;
            else throw std::invalid_argument("Valore non valido per 'In Corso'");

            return new SerieTv(
                fields[0]->text().toStdString(),
                fields[2]->text().toInt(),
                fields[1]->text().toStdString(),
                fields[3]->text().toInt(),
                fields[4]->text().toInt(),
                fields[5]->text().toInt(),
                inCorso,
                fields[7]->text().toStdString(),
                fields[8]->text().toStdString()
            );
        }
        else if (type == "Anime") {
            bool inCorso;
            QString inCorsoStr = fields[6]->text().toLower();
            if (inCorsoStr == "true" || inCorsoStr == "1") inCorso = true;
            else if (inCorsoStr == "false" || inCorsoStr == "0") inCorso = false;
            else throw std::invalid_argument("Valore non valido per 'In Corso'");

            return new Anime(
                fields[0]->text().toStdString(),
                fields[2]->text().toInt(),
                fields[1]->text().toStdString(),
                fields[3]->text().toInt(),
                fields[4]->text().toInt(),
                fields[5]->text().toInt(),
                inCorso,
                fields[7]->text().toStdString(),
                fields[8]->text().toStdString()
            );
        }
        else if (type == "Film") {
            return new Film(
                fields[0]->text().toStdString(),
                fields[2]->text().toInt(),
                fields[1]->text().toStdString(),
                fields[3]->text().toStdString(),
                fields[4]->text().toStdString(),
                fields[5]->text().toInt()
            );
        }
        else if (type == "Libri") {
            return new Libro(
                fields[0]->text().toStdString(),
                fields[2]->text().toInt(),
                fields[1]->text().toStdString(),
                fields[3]->text().toStdString(),
                fields[4]->text().toInt(),
                fields[5]->text().toStdString()
            );
        }
        else if (type == "Manga") {
            bool concluso;
            QString conclusoStr = fields[6]->text().toLower();
            if (conclusoStr == "true" || conclusoStr == "1") concluso = true;
            else if (conclusoStr == "false" || conclusoStr == "0") concluso = false;
            else throw std::invalid_argument("Valore non valido per 'Concluso'");

            return new Manga(
                fields[0]->text().toStdString(),
                fields[2]->text().toInt(),
                fields[1]->text().toStdString(),
                fields[3]->text().toStdString(),
                fields[4]->text().toStdString(),
                fields[5]->text().toInt(),
                concluso
            );
        }
        else if (type == "Cd") {
            return new Cd(
                fields[0]->text().toStdString(),
                fields[2]->text().toInt(),
                fields[1]->text().toStdString(),
                fields[3]->text().toStdString(),
                fields[4]->text().toInt(),
                fields[5]->text().toInt()
            );
        }
    }
    catch (const std::exception& e) {
        QMessageBox::critical(const_cast<QWidget*>(parentWidget()),
            "Errore",
            QString("Dati non validi: %1").arg(e.what()));
        return nullptr;
    }
    catch (...) {
        QMessageBox::critical(const_cast<QWidget*>(parentWidget()),
            "Errore",
            "Si è verificato un errore sconosciuto durante la creazione del media");
        return nullptr;
    }

    return nullptr;
}

void CreateItemWidget::onCreateButtonClicked()
{
    Media* newItem = createMediaItem();
    if (newItem) {
        emit itemCreated(newItem);

        // Clear all fields
        QWidget* currentPage = stackedFields->currentWidget();
        QList<QLineEdit*> fields = currentPage->findChildren<QLineEdit*>();
        for (QLineEdit* field : fields) {
            field->clear();
        }
    }
}

void CreateItemWidget::onItemTypeChanged(int index)
{
    stackedFields->setCurrentIndex(index);
}

void CreateItemWidget::onBrowseImageClicked()
{
    QWidget* currentPage = stackedFields->currentWidget();
    QList<QLineEdit*> fields = currentPage->findChildren<QLineEdit*>();

    if (fields.size() < 2) {
        return; // No image field found
    }

    QLineEdit* imageField = fields[1]; // Assuming second field is "Immagine"

    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Seleziona immagine"),
        QDir::homePath(),
        tr("Immagini (*.png *.jpg *.jpeg *.bmp *.gif)")
    );

    if (!filePath.isEmpty()) {
        imageField->setText(filePath);
    }
}
