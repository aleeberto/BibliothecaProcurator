#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include "../logic/Media.h"

class JsonManager : public QObject
{
    Q_OBJECT
public:
    explicit JsonManager(QObject *parent = nullptr);
    
    bool loadFromFile(const QString &filePath);
    bool saveToFile(const QString &filePath);
    
    QVector<Media*> getAllMedia() const;
    void addMedia(Media *media);
    bool removeMedia(const QString &title);
    Media* findMedia(const QString &title) const;
    void clearAll();
    
    QString getMediaTypeName(Media* media) const;

private:
    QJsonArray mediaArray;
    
    Media* jsonToMedia(const QJsonObject &jsonObj) const;
    QJsonObject mediaToJson(Media *media) const;
};

#endif // JSONMANAGER_H