#ifndef TOPMENU_HEADER
#define TOPMENU_HEADER

#include <QWidget>
#include <QPushButton>
#include <QMenu>
#include <QAction>

class TopMenuWidget : public QWidget {
    Q_OBJECT
private:
    
public:
    TopMenuWidget(QWidget* parent = nullptr);

    signals:
    void uploadJson();
    void saveJson();
    void createMedia();

};

#endif

