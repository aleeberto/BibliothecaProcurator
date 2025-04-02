#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "TopMenuWidget.h"
#include "CreateItemWidget.h"

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    TopMenuWidget* topMenu;           // Puntatore al TopMenuWidget
    CreateItemWidget* createItemWidget;  // Puntatore al CreateItemWidget
    QWidget *rightWidget;             // Parte destra della finestra

private slots:
    void showCreateItemWidget();      // Slot per mostrare il widget di creazione

public:
    MainWindow(QWidget *parent = nullptr);  // Costruttore
};

#endif
