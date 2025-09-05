#include "mediaTypeUtils.h"

QString MediaTypeUtils::getMediaTypeName(Media* media)
{
    if (!media) return "";
    
    return QString::fromStdString(media->getMediaType());
}

QString MediaTypeUtils::getMediaTitle(Media* media)
{
    if (!media) return "";
    return QString::fromStdString(media->getTitolo());
}

QString MediaTypeUtils::getMediaImage(Media* media)
{
    if (!media) return "";
    return QString::fromStdString(media->getImmagine());
}

int MediaTypeUtils::getMediaYear(Media* media)
{
    if (!media) return 0;
    return media->getAnno();
}