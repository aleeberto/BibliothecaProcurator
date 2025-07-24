#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../services/dbmanagerservice.h"
#include "../widgets/topMenuWidget.h"
#include "../widgets/createItemWidget.h"
#include "../core/media.h"

#include <vector>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onUploadRequested();
    void onSaveRequested();
    void onCreateRequested();
    void onItemCreated(Media* newItem);

private:
    DbManagerService dbService;
    std::vector<Media*> mediaItems;

    TopMenuWidget* topMenu;
    CreateItemWidget* createWidget;

    void setupUI();
    void clearItems();
};

#endif // MAINWINDOW_H
