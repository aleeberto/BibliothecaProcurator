#include "mediaService.h"

MediaService::MediaService(QObject *parent) : QObject(parent) {}

bool MediaService::loadMedia(const QString &filePath) {
    if (jsonService.loadFromFile(filePath)) {
        clearMedia();
        mediaCollection = jsonService.getAllMedia();
        return true;
    }
    return false;
}

bool MediaService::saveMedia(const QString &filePath) {
    jsonService.clearAll();
    for (Media* media : mediaCollection) {
        jsonService.addMedia(media);
    }
    return jsonService.saveToFile(filePath);
}

QVector<Media*> MediaService::getMediaCollection() const {
    return mediaCollection;
}

void MediaService::addMedia(Media* media) {
    if (media) {
        mediaCollection.append(media);
        jsonService.addMedia(media);
    }
}

void MediaService::clearMedia() {
    qDeleteAll(mediaCollection);
    mediaCollection.clear();
    jsonService.clearAll();
}

QVector<Media*> MediaService::filterMedia(const QString &category, const QString &searchText) const {
    QVector<Media*> filtered;
    QString searchLower = searchText.toLower();

    for (Media* media : mediaCollection) {
        QString mediaType = jsonService.getMediaTypeName(media);
        QString mediaTitle = QString::fromStdString(media->getTitolo()).toLower();

        if ((category == "Tutti" || mediaType == category) &&
            (searchLower.isEmpty() || mediaTitle.contains(searchLower))) {
            filtered.append(media);
        }
    }
    return filtered;
}
