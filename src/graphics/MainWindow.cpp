#include "MainWindow.h"
#include "TopMenuWidget.h"
#include "CreateItemWidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // **Creazione del widget sinistro (menu e categorie)**
    QWidget *leftWidget = new QWidget();
    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);

    // **Creazione del menu superiore**
    topMenu = new TopMenuWidget(this);

    // **Pulsanti di categoria**
    QStringList categories = {"Serie Tv", "Anime", "Film", "Libri", "Manga", "Cd"};
    for (const QString &category : categories) {
        QPushButton *btn = new QPushButton(category);
        btn->setIcon(QIcon("default.png"));
        btn->setIconSize(QSize(60, 60));
        btn->setFixedSize(150, 60);
        btn->setStyleSheet("text-align: left; padding: 10px;");
        leftLayout->addWidget(btn);
    }

    leftLayout->insertWidget(0, topMenu);
    leftWidget->setLayout(leftLayout);

    // **Creazione della parte destra**
    rightWidget = new QWidget();
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);

    // **Inizializzazione del widget per creare oggetti (inizialmente nascosto)**
    createItemWidget = new CreateItemWidget(this);
    createItemWidget->hide();
    
    rightLayout->addWidget(createItemWidget);
    rightLayout->addStretch(); // Per mantenere il widget in alto

    rightWidget->setLayout(rightLayout);
    rightWidget->setStyleSheet("background-color: #f0f0f0; padding: 10px;");

    // **Aggiunta di tutto al layout principale**
    mainLayout->addWidget(leftWidget);
    mainLayout->addWidget(rightWidget, 1); // La parte destra si espande

    setMinimumSize(600, 500);

    // **Collega il pulsante "Crea" al metodo per mostrare il widget nella parte destra**
    connect(topMenu, &TopMenuWidget::createMedia, this, &MainWindow::showCreateItemWidget);
}

// **Mostra il widget per creare un nuovo oggetto nella parte destra**
void MainWindow::showCreateItemWidget() {
    createItemWidget->show();
}
 