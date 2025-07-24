#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QVector>
#include <QMessageBox>
#include "../core/media.h"
#include "../services/dbManagerService.h"
#include "../ui/topMenuWidget.h"
#include "../ui/createItemWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onUploadRequested();
    void onSaveRequested();
    void onCreateRequested();
    void onItemCreated(Media* item);
    void onMediaSelected(Media* item);

private:
    void setupUi();
    void showHomePage();
    void showCreatePage();
    void showDetailPage(Media* item);

    DbManagerService dbManager;
    QVector<Media*> mediaItems;

    QWidget *central;
    QVBoxLayout *mainLayout;
    TopMenuWidget *topMenu;
    QStackedWidget *stackedPages;
    CreateItemWidget *createWidget;
};

#endif // MAINWINDOW_H
