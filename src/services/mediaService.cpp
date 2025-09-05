#include "mediaService.h"
#include <QDebug>
#include <QFile>
#include <QList>
#include <QLineEdit>
#include <stdexcept>
#include "../logic/film.h"
#include "../logic/serieTv.h"
#include "../logic/anime.h"
#include "../logic/libro.h"
#include "../logic/manga.h"
#include "../logic/cd.h"

MediaService::MediaService(QObject *parent) : QObject(parent), jsonService(nullptr)
{
    initializeMediaFactories();
}

MediaService::~MediaService()
{
    clearMediaCollection();
}

void MediaService::initializeMediaFactories() {
    // Factory per la creazione dei media con parametri da form
    mediaCreationFactories["Serie Tv"] = [this](const QList<QLineEdit*>& fields) -> Media* {
        if (fields.size() < 9) return nullptr;
        
        bool inCorso = parseBoolFromString(fields[6]->text(), "In Corso");
        return new SerieTv(
            fields[0]->text().toStdString(),  // titolo
            fields[2]->text().toInt(),        // anno
            fields[1]->text().toStdString(),  // immagine
            fields[3]->text().toInt(),        // numEpisodi
            fields[4]->text().toInt(),        // numStagioni
            fields[5]->text().toInt(),        // durataMediaEp
            inCorso,                          // inCorso
            fields[7]->text().toStdString(),  // ideatore
            fields[8]->text().toStdString()   // casaProduttrice
        );
    };
    
    mediaCreationFactories["Anime"] = [this](const QList<QLineEdit*>& fields) -> Media* {
        if (fields.size() < 9) return nullptr;
        
        bool inCorso = parseBoolFromString(fields[6]->text(), "In Corso");
        return new Anime(
            fields[0]->text().toStdString(),  // titolo
            fields[2]->text().toInt(),        // anno
            fields[1]->text().toStdString(),  // immagine
            fields[3]->text().toInt(),        // numEpisodi
            fields[4]->text().toInt(),        // numStagioni
            fields[5]->text().toInt(),        // durataMediaEp
            inCorso,                          // inCorso
            fields[7]->text().toStdString(),  // disegnatore
            fields[8]->text().toStdString()   // studioAnimazione
        );
    };
    
    mediaCreationFactories["Film"] = [this](const QList<QLineEdit*>& fields) -> Media* {
        if (fields.size() < 6) return nullptr;
        
        return new Film(
            fields[0]->text().toStdString(),  // titolo
            fields[2]->text().toInt(),        // anno
            fields[1]->text().toStdString(),  // immagine
            fields[3]->text().toStdString(),  // regista
            fields[4]->text().toStdString(),  // attoreProtagonista
            fields[5]->text().toInt()         // durata
        );
    };
    
    mediaCreationFactories["Libro"] = [this](const QList<QLineEdit*>& fields) -> Media* {
        if (fields.size() < 6) return nullptr;
        
        return new Libro(
            fields[0]->text().toStdString(),  // titolo
            fields[2]->text().toInt(),        // anno
            fields[1]->text().toStdString(),  // immagine
            fields[3]->text().toStdString(),  // scrittore
            fields[4]->text().toInt(),        // annoStampa
            fields[5]->text().toStdString()   // casaEditrice
        );
    };
    
    mediaCreationFactories["Manga"] = [this](const QList<QLineEdit*>& fields) -> Media* {
        if (fields.size() < 7) return nullptr;
        
        bool concluso = parseBoolFromString(fields[6]->text(), "Concluso");
        return new Manga(
            fields[0]->text().toStdString(),  // titolo
            fields[2]->text().toInt(),        // anno
            fields[1]->text().toStdString(),  // immagine
            fields[3]->text().toStdString(),  // scrittore
            fields[4]->text().toStdString(),  // illustratore
            fields[5]->text().toInt(),        // numLibri
            concluso                          // concluso
        );
    };
    
    mediaCreationFactories["Cd"] = [this](const QList<QLineEdit*>& fields) -> Media* {
        if (fields.size() < 6) return nullptr;
        
        return new Cd(
            fields[0]->text().toStdString(),  // titolo
            fields[2]->text().toInt(),        // anno
            fields[1]->text().toStdString(),  // immagine
            fields[3]->text().toStdString(),  // artista
            fields[4]->text().toInt(),        // numTracce
            fields[5]->text().toInt()         // durataMedTracce
        );
    };
}

void MediaService::setMediaCollection(const QVector<Media*>& collection)
{
    clearMediaCollection();
    mediaCollection = collection;
    updateJsonService();
    emit collectionChanged();
}

QVector<Media*> MediaService::getMediaCollection() const
{
    return mediaCollection;
}

void MediaService::clearMediaCollection()
{
    for (Media* media : mediaCollection) {
        delete media;
    }
    mediaCollection.clear();
    updateJsonService();
    emit collectionChanged();
}

bool MediaService::addMedia(Media* media)
{
    if (!media) return false;
    
    mediaCollection.append(media);
    updateJsonService();
    emit mediaAdded(media);
    emit collectionChanged();
    return true;
}

bool MediaService::updateMedia(Media* oldMedia, Media* newMedia)
{
    if (!oldMedia || !newMedia) return false;
    
    int index = mediaCollection.indexOf(oldMedia);
    if (index == -1) return false;
    
    mediaCollection[index] = newMedia;
    delete oldMedia;
    updateJsonService();
    emit mediaUpdated(oldMedia, newMedia);
    emit collectionChanged();
    return true;
}

bool MediaService::deleteMedia(Media* media)
{
    if (!media) return false;
    
    int index = mediaCollection.indexOf(media);
    if (index == -1) return false;
    
    mediaCollection.removeAt(index);
    delete media;
    updateJsonService();
    emit mediaDeleted(media);
    emit collectionChanged();
    return true;
}

Media* MediaService::findMediaByTitle(const QString& title) const
{
    for (Media* media : mediaCollection) {
        if (QString::fromStdString(media->getTitolo()) == title) {
            return media;
        }
    }
    return nullptr;
}

bool MediaService::loadFromFile(const QString& filePath)
{
    if (!jsonService) return false;
    
    currentFilePath = filePath;
    bool success = jsonService->loadFromFile(filePath);
    if (success) {
        setMediaCollection(jsonService->getAllMedia());
        emit dataLoaded();
    }
    return success;
}

bool MediaService::saveToFile(const QString& filePath)
{
    if (!jsonService) return false;
    
    currentFilePath = filePath;
    bool success = jsonService->saveToFile(filePath);
    if (success) {
        emit dataSaved();
    }
    return success;
}

void MediaService::setJsonService(JsonService* service)
{
    jsonService = service;
}

// Nuovo metodo che usa polimorfismo invece di getType
QVector<Media*> MediaService::filterMedia(const QString& category, const QString& searchText) const
{
    QVector<Media*> filtered;
    std::string categoryStd = category.toStdString();
    std::string searchStd = searchText.toStdString();
    
    for (Media* media : mediaCollection) {
        // Usa il polimorfismo per il matching di categoria e ricerca
        if (media->matchesCategory(categoryStd) && media->matchesSearch(searchStd)) {
            filtered.append(media);
        }
    }
    return filtered;
}

int MediaService::getMediaCount() const
{
    return mediaCollection.size();
}

bool MediaService::isEmpty() const
{
    return mediaCollection.isEmpty();
}

void MediaService::updateJsonService()
{
    if (jsonService) {
        jsonService->clearAll();
        for (Media* media : mediaCollection) {
            jsonService->addMedia(media);
        }
    }
}

bool MediaService::parseBoolFromString(const QString& text, const QString& fieldName) const
{
    QString lowered = text.trimmed().toLower();

    if (lowered == "true" || lowered == "1") return true;
    if (lowered == "false" || lowered == "0") return false;

    throw std::invalid_argument(
        QString("Valore non valido per '%1'").arg(fieldName).toStdString()
    );
}

Media* MediaService::createMediaFromFields(const QString& type, const QList<QLineEdit*>& fields, QWidget* parent)
{
    // Validazione campi obbligatori
    for (QLineEdit* field : fields) {
        if (field->text().isEmpty()) {
            QMessageBox::warning(parent,
                "Attenzione",
                QString("Il campo '%1' è obbligatorio!").arg(field->placeholderText()));
            field->setFocus();
            return nullptr;
        }
    }

    try {
        // Usa la factory per creare il media
        auto factoryIt = mediaCreationFactories.find(type.toStdString());
        if (factoryIt != mediaCreationFactories.end()) {
            return factoryIt->second(fields);
        }
        
        QMessageBox::critical(parent,
            "Errore",
            QString("Tipo di media non supportato: %1").arg(type));
        return nullptr;
    }
    catch (const std::exception& e) {
        QMessageBox::critical(parent,
            "Errore",
            QString("Dati non validi: %1").arg(e.what()));
        return nullptr;
    }
    catch (...) {
        QMessageBox::critical(parent,
            "Errore",
            "Si è verificato un errore sconosciuto durante la creazione del media");
        return nullptr;
    }
}