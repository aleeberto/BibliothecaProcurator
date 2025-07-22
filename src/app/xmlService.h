#ifndef XMLSERVICE_HEADER
#define XMLSERVICE_HEADER

#include <QObject>
#include <QVector>
#include "../logic/media.h"

class XmlService : public QObject
{
    Q_OBJECT

public:
    explicit XmlService(QObject *parent = nullptr);
    
    bool loadFromFile(const QString &filePath);
    bool saveToFile(const QString &filePath);
    
    QVector<Media*> getAllMedia() const;
    void addMedia(Media *media);
    bool removeMedia(const QString &title);
    Media* findMedia(const QString &title) const;
    void clearAll();

private:
    Media* xmlToMedia(const QDomElement &element) const;
    QDomElement mediaToXml(Media *media, QDomDocument &doc) const;
};

#endif // XMLSERVICE_HEADER
