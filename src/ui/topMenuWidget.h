#ifndef TOPMENU_HEADER
#define TOPMENU_HEADER

#include <QWidget>
#include <QPushButton>

class TopMenuWidget : public QWidget {
    Q_OBJECT
public:
    TopMenuWidget(QWidget* parent = nullptr);
    
signals:
    void uploadRequested();  // Modificato da uploadJson
    void saveRequested();    // Modificato da saveJson
    void createRequested();  // Modificato da createMedia
};

#endif