#include "formWidgetVisitor.h"
#include "../../logic/film.h"
#include "../../logic/serieTv.h"
#include "../../logic/anime.h"
#include "../../logic/libro.h"
#include "../../logic/manga.h"
#include "../../logic/cd.h"
#include "../../services/styleUtils.h"

FormWidgetVisitor::FormWidgetVisitor(QWidget* parent) 
    : parentWidget(parent), resultWidget(nullptr) {}

QWidget* FormWidgetVisitor::getResultWidget() const {
    return resultWidget;
}

QWidget* FormWidgetVisitor::createFormWidget(const QStringList& fieldLabels, const QStringList& placeholders, const QStringList& values) {
    QWidget* widget = new QWidget(parentWidget);
    QVBoxLayout* layout = new QVBoxLayout(widget);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(15);

    for (int i = 0; i < fieldLabels.size() && i < placeholders.size(); ++i) {
        QLabel* label = new QLabel(fieldLabels[i] + ":", widget);
        label->setStyleSheet(StyleUtils::getSubtitleLabelStyle());
        
        QLineEdit* lineEdit = new QLineEdit(widget);
        lineEdit->setPlaceholderText(placeholders[i]);
        lineEdit->setStyleSheet(StyleUtils::getLineEditStyle());
        lineEdit->setFixedHeight(44);
        
        // Se ci sono valori forniti, popola il campo
        if (i < values.size() && !values[i].isEmpty()) {
            lineEdit->setText(values[i]);
        }
        
        layout->addWidget(label);
        layout->addWidget(lineEdit);
    }
    
    layout->addStretch();
    return widget;
}

void FormWidgetVisitor::populateFormFields(QWidget* formWidget, const QStringList& values) {
    if (!formWidget) return;
    
    QList<QLineEdit*> fields = formWidget->findChildren<QLineEdit*>();
    for (int i = 0; i < fields.size() && i < values.size(); ++i) {
        if (fields[i] && !values[i].isEmpty()) {
            fields[i]->setText(values[i]);
        }
    }
}

void FormWidgetVisitor::visit(Film* film) {
    QStringList labels = {"Titolo", "Immagine", "Anno", "Regista", "Attore Protagonista", "Durata (min)"};
    QStringList placeholders = {"Inserisci titolo", "Inserisci percorso immagine", "Inserisci anno", 
                               "Inserisci regista", "Inserisci attore protagonista", "Inserisci durata in minuti"};
    
    QStringList values;
    if (film) {
        values << QString::fromStdString(film->getTitolo())
               << QString::fromStdString(film->getImmagine())
               << QString::number(film->getAnno())
               << QString::fromStdString(film->getRegista())
               << QString::fromStdString(film->getAttoreProtagonista())
               << QString::number(film->getDurata());
    }
    
    resultWidget = createFormWidget(labels, placeholders, values);
}

void FormWidgetVisitor::visit(SerieTv* serieTv) {
    QStringList labels = {"Titolo", "Immagine", "Anno", "Numero Episodi", "Numero Stagioni", 
                         "Durata Media Episodio (min)", "In Corso (true/false)", "Ideatore", "Casa Produttrice"};
    QStringList placeholders = {"Inserisci titolo", "Inserisci percorso immagine", "Inserisci anno",
                               "Inserisci numero episodi", "Inserisci numero stagioni", 
                               "Inserisci durata media episodio", "true o false", 
                               "Inserisci ideatore", "Inserisci casa produttrice"};
    
    QStringList values;
    if (serieTv) {
        values << QString::fromStdString(serieTv->getTitolo())
               << QString::fromStdString(serieTv->getImmagine())
               << QString::number(serieTv->getAnno())
               << QString::number(serieTv->getNumEpisodi())
               << QString::number(serieTv->getNumStagioni())
               << QString::number(serieTv->getDurataMediaEp())
               << (serieTv->getInCorso() ? "true" : "false")
               << QString::fromStdString(serieTv->getIdeatore())
               << QString::fromStdString(serieTv->getCasaProduttrice());
    }
    
    resultWidget = createFormWidget(labels, placeholders, values);
}

void FormWidgetVisitor::visit(Anime* anime) {
    QStringList labels = {"Titolo", "Immagine", "Anno", "Numero Episodi", "Numero Stagioni", 
                         "Durata Media Episodio (min)", "In Corso (true/false)", "Disegnatore", "Studio Animazione"};
    QStringList placeholders = {"Inserisci titolo", "Inserisci percorso immagine", "Inserisci anno",
                               "Inserisci numero episodi", "Inserisci numero stagioni", 
                               "Inserisci durata media episodio", "true o false", 
                               "Inserisci disegnatore", "Inserisci studio animazione"};
    
    QStringList values;
    if (anime) {
        values << QString::fromStdString(anime->getTitolo())
               << QString::fromStdString(anime->getImmagine())
               << QString::number(anime->getAnno())
               << QString::number(anime->getNumEpisodi())
               << QString::number(anime->getNumStagioni())
               << QString::number(anime->getDurataMediaEp())
               << (anime->getInCorso() ? "true" : "false")
               << QString::fromStdString(anime->getDisegnatore())
               << QString::fromStdString(anime->getStudioAnimazione());
    }
    
    resultWidget = createFormWidget(labels, placeholders, values);
}

void FormWidgetVisitor::visit(Libro* libro) {
    QStringList labels = {"Titolo", "Immagine", "Anno", "Scrittore", "Anno Stampa", "Casa Editrice"};
    QStringList placeholders = {"Inserisci titolo", "Inserisci percorso immagine", "Inserisci anno",
                               "Inserisci scrittore", "Inserisci anno stampa", "Inserisci casa editrice"};
    
    QStringList values;
    if (libro) {
        values << QString::fromStdString(libro->getTitolo())
               << QString::fromStdString(libro->getImmagine())
               << QString::number(libro->getAnno())
               << QString::fromStdString(libro->getScrittore())
               << QString::number(libro->getAnnoStampa())
               << QString::fromStdString(libro->getCasaEditrice());
    }
    
    resultWidget = createFormWidget(labels, placeholders, values);
}

void FormWidgetVisitor::visit(Manga* manga) {
    QStringList labels = {"Titolo", "Immagine", "Anno", "Scrittore", "Illustratore", 
                         "Numero Libri", "Concluso (true/false)"};
    QStringList placeholders = {"Inserisci titolo", "Inserisci percorso immagine", "Inserisci anno",
                               "Inserisci scrittore", "Inserisci illustratore", 
                               "Inserisci numero libri", "true o false"};
    
    QStringList values;
    if (manga) {
        values << QString::fromStdString(manga->getTitolo())
               << QString::fromStdString(manga->getImmagine())
               << QString::number(manga->getAnno())
               << QString::fromStdString(manga->getScrittore())
               << QString::fromStdString(manga->getIllustratore())
               << QString::number(manga->getNumLibri())
               << (manga->getConcluso() ? "true" : "false");
    }
    
    resultWidget = createFormWidget(labels, placeholders, values);
}

void FormWidgetVisitor::visit(Cd* cd) {
    QStringList labels = {"Titolo", "Immagine", "Anno", "Artista", "Numero Tracce", "Durata Media Tracce (sec)"};
    QStringList placeholders = {"Inserisci titolo", "Inserisci percorso immagine", "Inserisci anno",
                               "Inserisci artista", "Inserisci numero tracce", "Inserisci durata media tracce"};
    
    QStringList values;
    if (cd) {
        values << QString::fromStdString(cd->getTitolo())
               << QString::fromStdString(cd->getImmagine())
               << QString::number(cd->getAnno())
               << QString::fromStdString(cd->getArtista())
               << QString::number(cd->getNumTracce())
               << QString::number(cd->getDurataMedTracce());
    }
    
    resultWidget = createFormWidget(labels, placeholders, values);
}