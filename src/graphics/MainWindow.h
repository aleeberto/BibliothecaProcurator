#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QMap>
#include <QPushButton>
#include <QLineEdit>
#include "TopMenuWidget.h"
#include "CreateItemWidget.h"
#include "../json/JsonManager.h"
#include "../logic/Media.h"

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
    void loadMediaData(const QString &filePath);
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
    JsonManager *jsonManager;
    QVector<Media*> mediaCollection;
    QMap<QString, QPushButton*> categoryButtons;
    QString currentJsonPath = "biblioteca.json";
    QString currentCategory = "Tutti";
    QLineEdit *searchBar;
};

#endif // MAINWINDOW_H