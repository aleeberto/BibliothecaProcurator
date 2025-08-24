#ifndef JSONSERVICE_HEADER
#define JSONSERVICE_HEADER

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>
#include <memory>
#include <functional>
#include <unordered_map>
#include "../logic/media.h"

class JsonService : public QObject
{
    Q_OBJECT
public:
    explicit JsonService(QObject *parent = nullptr);
    
    bool loadFromFile(const QString &filePath);
    bool saveToFile(const QString &filePath);
    
    QVector<Media*> getAllMedia() const;
    void addMedia(Media *media);
    bool removeMedia(const QString &title);
    Media* findMedia(const QString &title) const;
    void clearAll();
    
    // Metodo per registrare factory di creazione media
    template<typename T>
    void registerMediaType(const QString& typeName);
    
private:
    QJsonArray mediaArray;
    
    // Factory map per la creazione
    std::unordered_map<std::string, std::function<std::unique_ptr<Media>(const QJsonObject&)>> mediaFactories;
    
    // Metodi helper 
    std::unique_ptr<Media> createMediaFromJson(const QJsonObject &jsonObj) const;
    QJsonObject mediaToJson(Media *media) const;
    
    // Inizializzazione delle factory
    void initializeFactories();
};

// Implementazione template nel header
template<typename T>
void JsonService::registerMediaType(const QString& typeName) {
    mediaFactories[typeName.toStdString()] = [](const QJsonObject& json) -> std::unique_ptr<Media> {
        auto media = std::make_unique<T>("", 0, ""); // = altri metdi default
        media->fromJsonSpecific(json);
        return std::move(media);
    };
}

#endif