#ifndef ENHANCED_MEDIA_HEADER
#define ENHANCED_MEDIA_HEADER

#include "media.h"
#include <QString>
#include <QJsonObject>

class EnhancedMedia : public Media {
public:
    EnhancedMedia(string titolo, int anno, string immagine);
    
    // Metodi virtuali per polimorfismo non banale
    virtual QString getDetails() const = 0;
    virtual QString getTypeName() const = 0;
    virtual QString getShortDescription() const = 0;
    virtual bool matchesSearch(const QString& searchTerm) const;
    virtual QJsonObject toJson() const = 0;
    virtual void fromJson(const QJsonObject& json) = 0;
};

#endif
