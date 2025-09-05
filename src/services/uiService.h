#ifndef UISERVICE_HEADER
#define UISERVICE_HEADER

#include <QObject>
#include <QString>
#include <QStringList>
#include <QPixmap>
#include "../logic/media.h"

class UIService : public QObject
{
    Q_OBJECT

public:
    explicit UIService(QObject *parent = nullptr);

    QString formatMediaTitle(Media* media) const;
    QString formatMediaYear(Media* media) const;
    
    QPixmap loadMediaImage(const std::string& imagePath) const;
    QPixmap createImagePlaceholder(const std::string& originalPath) const;
    
    QString formatBooleanValue(bool value, const QString& trueText = "true", const QString& falseText = "false") const;
    QString formatDuration(int minutes, const QString& unit = "min") const;
    QString formatNumber(int number) const;
    
    QString resolveImagePath(const QString& relativePath) const;
    bool isValidImagePath(const QString& path) const;

private:
    QString createDebugInfo(const QString& originalPath, const QString& resolvedPath) const;
};

#endif
