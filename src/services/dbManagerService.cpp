#include "dbmanagerservice.h"
#include "../core/series.h"
#include "../core/serieTv.h"
#include "../core/anime.h"
#include "../core/film.h"
#include "../core/libro.h"
#include "../core/manga.h"
#include "../core/cd.h"
#include "../core/cartaceo.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

DbManagerService::DbManagerService() {}

bool DbManagerService::saveToFile(const QString& filePath, const std::vector<Media*>& items) const {
    QJsonArray jsonArray;
    for (const Media* item : items) {
        jsonArray.append(item->toJson());
    }

    QJsonDocument doc(jsonArray);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    file.write(doc.toJson());
    file.close();
    return true;
}

std::vector<Media*> DbManagerService::loadFromFile(const QString& filePath) const {
    std::vector<Media*> items;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return items;

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();

    for (const QJsonValue& val : array) {
        QJsonObject obj = val.toObject();
        Media* item = parseItem(obj);
        if (item)
            items.push_back(item);
    }

    return items;
}

Media* DbManagerService::parseItem(const QJsonObject& obj) const {
    const QString type = obj["type"].toString();

    if (type == "SerieTv") return SerieTv::fromJson(obj);
    if (type == "Anime") return Anime::fromJson(obj);
    if (type == "Film") return Film::fromJson(obj);
    if (type == "Libro") return Libro::fromJson(obj);
    if (type == "Manga") return Manga::fromJson(obj);
    if (type == "Cd") return Cd::fromJson(obj);

    return nullptr;
}
