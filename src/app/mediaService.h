#ifndef MEDIASERVICE_HEADER
#define MEDIASERVICE_HEADER

#include <QObject>
#include <QVector>
#include <QString>
#include "../logic/media.h"
#include "jsonService.h"

class MediaService : public QObject
{
    Q_OBJECT

public:
    explicit MediaService(QObject *parent = nullptr);

    bool loadMedia(const QString &filePath);
    bool saveMedia(const QString &filePath);

    QVector<Media*> getMediaCollection() const;
    void addMedia(Media* media);
    void clearMedia();

    QVector<Media*> filterMedia(const QString &category, const QString &searchText) const;

private:
    QVector<Media*> mediaCollection;
    JsonService jsonService;
};

#endif
