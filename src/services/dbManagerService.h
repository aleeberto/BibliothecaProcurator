#ifndef DBMANAGER_SERVICE_H
#define DBMANAGER_SERVICE_H

#include "../core/media.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <vector>

class DbManagerService {
public:
    DbManagerService();

    bool saveToFile(const QString& filePath, const std::vector<Media*>& items) const;
    std::vector<Media*> loadFromFile(const QString& filePath) const;

private:
    Media* parseItem(const QJsonObject& obj) const;
};

#endif // DBMANAGER_SERVICE_H
