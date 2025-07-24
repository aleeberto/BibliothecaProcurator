#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QMap>
#include <QPushButton>
#include <QLineEdit>
#include "widget/topMenuWidget.h"
#include "widget/createItemWidget.h"
#include "widget/rightLayoutWidget.h"
#include "../services/jsonService.h"
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
    void loadMediaData(const QString &filePath);
    void setupCategoryButtons();
    void setupSearchBar();

    TopMenuWidget* topMenu;
    CreateItemWidget* createItemWidget;
    RightLayoutWidget* rightLayoutWidget;
    QVBoxLayout *leftLayout;
    JsonService *jsonService;
    QVector<Media*> mediaCollection;
    QMap<QString, QPushButton*> categoryButtons;
    QString currentJsonPath = "biblioteca.json";
    QString currentCategory = "Tutti";
    QLineEdit *searchBar;
};

#endif // MAINWINDOW_H
