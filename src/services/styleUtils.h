#ifndef STYLEUTILS_HEADER
#define STYLEUTILS_HEADER

#include <QString>

class StyleUtils
{
public:
    static QString getPrimaryButtonStyle();
    static QString getTopButtonStyle();
    static QString getDangerButtonStyle();
    static QString getWarningButtonStyle();
    static QString getIconButtonStyle();
    static QString getItemButtonStyle();
    
    static QString getLineEditStyle();
    static QString getSearchBarStyle();
    static QString getComboBoxStyle();
    
    static QString getMainWindowStyle();
    static QString getSidebarStyle();
    static QString getContentAreaStyle();
    static QString getCardStyle();
    
    static QString getTitleLabelStyle();
    static QString getSubtitleLabelStyle();
    static QString getBodyLabelStyle();
    
    static QString getPrimaryColor();
    static QString getSecondaryColor();
    static QString getAccentColor();
    static QString getBackgroundColor();
    static QString getSurfaceColor();
    static QString getTextColor();
    static QString getTextSecondaryColor();
    static QString getBorderColor();
    
private:
    StyleUtils() = default;
};

#endif
