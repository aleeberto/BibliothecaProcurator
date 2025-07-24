#ifndef JSONSERVICE_HEADER
#define JSONSERVICE_HEADER

#include <QObject>
#include <QJsonObject>
#include "../core/media.h"

class JsonService : public QObject
{
    Q_OBJECT
public:
    explicit JsonService(QObject *parent = nullptr);

    // Conversioni JSON <-> Media
    Media* jsonToMedia(const QJsonObject &jsonObj) const;
    QJsonObject mediaToJson(Media *media) const;
};

#endif
