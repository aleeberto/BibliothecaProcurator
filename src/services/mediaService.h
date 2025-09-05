#ifndef MEDIASERVICE_HEADER
#define MEDIASERVICE_HEADER

#include <QObject>
#include <QVector>
#include <QString>
#include <QList>
#include <QLineEdit>
#include <QWidget>
#include <QMessageBox>
#include <functional>
#include <unordered_map>
#include "../logic/media.h"
#include "jsonService.h"

class MediaService : public QObject
{
    Q_OBJECT

public:
    explicit MediaService(QObject *parent = nullptr);
    ~MediaService();

    void setMediaCollection(const QVector<Media*>& collection);
    QVector<Media*> getMediaCollection() const;
    void clearMediaCollection();

    bool addMedia(Media* media);
    bool updateMedia(Media* oldMedia, Media* newMedia);
    bool deleteMedia(Media* media);
    Media* findMediaByTitle(const QString& title) const;

    bool loadFromFile(const QString& filePath);
    bool saveToFile(const QString& filePath);
    void setJsonService(JsonService* service);

    // Nuovi metodi che usano polimorfismo invece di getType
    QVector<Media*> filterMedia(const QString& category, const QString& searchText) const;

    int getMediaCount() const;
    bool isEmpty() const;

    Media* createMediaFromFields(const QString& type, const QList<QLineEdit*>& fields, QWidget* parent);

signals:
    void mediaAdded(Media* media);
    void mediaUpdated(Media* oldMedia, Media* newMedia);
    void mediaDeleted(Media* media);
    void collectionChanged();
    void dataLoaded();
    void dataSaved();

private:
    QVector<Media*> mediaCollection;
    JsonService* jsonService;
    QString currentFilePath;
    
    // Factory map per la creazione polimorfica dei media da form
    std::unordered_map<std::string, std::function<Media*(const QList<QLineEdit*>&)>> mediaCreationFactories;

    void updateJsonService();
    void initializeMediaFactories();
    bool parseBoolFromString(const QString& text, const QString& fieldName) const;
};

#endif