#include "TopMenuWidget.h"
#include <QHBoxLayout>
#include <QDir>

TopMenuWidget::TopMenuWidget(QWidget* parent) : QWidget(parent) {
    QHBoxLayout* layout = new QHBoxLayout(this);

    QPushButton* btnUpload = new QPushButton( this);
    QPushButton* btnSave = new QPushButton(this);
    QPushButton* btnCreate = new QPushButton(this);

    // Imposta le icone
    btnUpload->setIcon(QIcon("./src/icon/upload.png"));
    btnSave->setIcon(QIcon("./src/icon/save.png"));
    btnCreate->setIcon(QIcon("./src/icon/add.png"));

    // Imposta dimensioni dei pulsatni
    QSize buttonSize(50, 50);  // Modifica questa dimensione se necessario
    btnUpload->setFixedSize(buttonSize);
    btnSave->setFixedSize(buttonSize);
    btnCreate->setFixedSize(buttonSize);

    //Grandezza delle icone
    QSize iconSize(40, 40);
    btnUpload->setIconSize(iconSize);
    btnSave->setIconSize(iconSize);
    btnCreate->setIconSize(iconSize);

    QString buttonStyle =
        "QPushButton { "
                       "background-color: #ffffff; "
                       "border-radius: 10px; "
                       "padding: 10px; "
                       "border: 2px solid #000000; "
                       "}"
                       "QPushButton:hover { "
                       "background-color: #a7a8a8; "
                       "}"
                       "QPushButton:pressed { "
                       "background-color: #4b4f53; "
                       "}";

    btnUpload->setStyleSheet(buttonStyle);
    btnSave->setStyleSheet(buttonStyle);
    btnCreate->setStyleSheet(buttonStyle);

    connect(btnCreate, &QPushButton::clicked, this, &TopMenuWidget::createMedia);

    // Aggiunge i pulsanti al layout
    layout->addWidget(btnUpload);
    layout->addWidget(btnSave);
    layout->addWidget(btnCreate);

    layout->addStretch(); //sposta tutto a sinistra
    setLayout(layout);
}