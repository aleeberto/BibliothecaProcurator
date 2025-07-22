#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QMap>
#include <QPushButton>
#include <QLineEdit>
#include "topMenuWidget.h"
#include "createItemWidget.h"
#include "../app/jsonService.h"
#include "../app/mediaService.h"
#include "../logic/media.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showCreateItemWidget();
    void onMediaItemCreated(Media* newItem);
    void handleUploadRequest();
    void saveCurrentData();
    void onSearchTextChanged(const QString& text);

private:
    void clearCurrentMedia();
    void displayMediaByCategory(const QString &category);
    void setupCategoryButtons();
    void setupSearchBar();
    void addMediaCardToLayout(Media* media);
    QPixmap loadMediaImage(const std::string& imagePath);

    TopMenuWidget* topMenu;
    CreateItemWidget* createItemWidget;
    QWidget *rightWidget;
    QVBoxLayout *rightLayout;
    QVBoxLayout *leftLayout;
    MediaService *mediaService;
    QString currentJsonPath = "biblioteca.json";
    QString currentCategory = "Tutti";
    QLineEdit *searchBar;
    QMap<QString, QPushButton*> categoryButtons;
};

#endif // MAINWINDOW_H
