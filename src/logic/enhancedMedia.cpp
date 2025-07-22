#include "enhancedMedia.h"

EnhancedMedia::EnhancedMedia(string titolo, int anno, string immagine)
    : Media(titolo, anno, immagine) {}

bool EnhancedMedia::matchesSearch(const QString& searchTerm) const {
    QString title = QString::fromStdString(getTitolo()).toLower();
    return title.contains(searchTerm.toLower());
}
