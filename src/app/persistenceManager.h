#ifndef PERSISTENCE_MANAGER_HEADER
#define PERSISTENCE_MANAGER_HEADER

#include <QObject>
#include <QVector>
#include <QString>
#include "../logic/media.h"

class PersistenceManager : public QObject
{
    Q_OBJECT

public:
    explicit PersistenceManager(QObject *parent = nullptr);
    
    bool loadFromJson(const QString &filePath);
    bool saveToJson(const QString &filePath);
    bool loadFromXml(const QString &filePath);
    bool saveToXml(const QString &filePath);
    
    QVector<Media*> getAllMedia() const;
    void addMedia(Media *media);
    bool removeMedia(const QString &title);
    Media* findMedia(const QString &title) const;
    void clearAll();
    
    QString getMediaTypeName(Media* media) const;

private:
    QVector<Media*> mediaCollection;
};

#endif
