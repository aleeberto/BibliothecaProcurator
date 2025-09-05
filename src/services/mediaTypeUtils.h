#ifndef MEDIATYPEUTILS_HEADER
#define MEDIATYPEUTILS_HEADER

#include <QString>
#include "../logic/media.h"

class MediaTypeUtils
{
public:
    static QString getMediaTypeName(Media* media);
    
    static QString getMediaTitle(Media* media);
    static QString getMediaImage(Media* media);
    static int getMediaYear(Media* media);
    
private:
    MediaTypeUtils() = default;
};

#endif
