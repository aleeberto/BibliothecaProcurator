#include "topMenuWidget.h"
#include <QHBoxLayout>

TopMenuWidget::TopMenuWidget(QWidget* parent) : QWidget(parent) {
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(10);

    QPushButton* btnUpload = new QPushButton(this);
    QPushButton* btnSave = new QPushButton(this);
    QPushButton* btnCreate = new QPushButton(this);

    // Imposta le icone
    btnUpload->setIcon(QIcon("../resources/icon/upload.png"));
    btnSave->setIcon(QIcon("../resources/icon/save.png"));
    btnCreate->setIcon(QIcon("../resources/icon/add.png"));

    // Imposta dimensioni e stili
    QSize buttonSize(40, 40);
    btnUpload->setFixedSize(buttonSize);
    btnSave->setFixedSize(buttonSize);
    btnCreate->setFixedSize(buttonSize);

    QSize iconSize(25, 25);
    btnUpload->setIconSize(iconSize);
    btnSave->setIconSize(iconSize);
    btnCreate->setIconSize(iconSize);

    QString buttonStyle =
    "QPushButton {"
    "background-color: #fff;"
    "border-radius: 5px;"
    "border: 1px solid #ddd;"
    "}"
    "QPushButton:hover {"
    "background-color: #f0f0f0;"
    "}"
    "QPushButton:pressed {"
    "background-color: #e0e0e0;"
    "}";

    btnUpload->setStyleSheet(buttonStyle);
    btnSave->setStyleSheet(buttonStyle);
    btnCreate->setStyleSheet(buttonStyle);

    // Connessioni dei pulsanti
    connect(btnUpload, &QPushButton::clicked, this, &TopMenuWidget::uploadRequested);
    connect(btnSave, &QPushButton::clicked, this, &TopMenuWidget::saveRequested);
    connect(btnCreate, &QPushButton::clicked, this, &TopMenuWidget::createRequested);

    layout->addWidget(btnUpload);
    layout->addWidget(btnSave);
    layout->addWidget(btnCreate);
    layout->addStretch();

    this->setLayout(layout);
}