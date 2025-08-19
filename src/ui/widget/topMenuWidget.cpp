#include "topMenuWidget.h"
#include <QHBoxLayout>
#include "../../services/styleUtils.h"

TopMenuWidget::TopMenuWidget(QWidget* parent) : QWidget(parent) {
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(8);

    // Pulsante Upload
    QPushButton* btnUpload = new QPushButton(this);
    btnUpload->setIcon(QIcon("../resources/icon/open.png"));
    btnUpload->setIconSize(QSize(30, 30));
    btnUpload->setToolTip("Carica una biblioteca esistente");
    btnUpload->setStyleSheet(StyleUtils::getTopButtonStyle());
    btnUpload->setFixedHeight(44);

    // Pulsante Export 
    QPushButton* btnNewExport = new QPushButton(this);
    btnNewExport->setIcon(QIcon("../resources/icon/create.png"));
    btnNewExport->setIconSize(QSize(30, 30));
    btnNewExport->setToolTip("Crea una nuova biblioteca");
    btnNewExport->setStyleSheet(StyleUtils::getTopButtonStyle());
    btnNewExport->setFixedHeight(44);

    // Pulsante Close
    QPushButton* btnClose = new QPushButton(this);
    btnClose->setIcon(QIcon("../resources/icon/close.png"));
    btnClose->setIconSize(QSize(30, 30));
    btnClose->setToolTip("Chiude la biblioteca corrente");
    btnClose->setStyleSheet(StyleUtils::getTopButtonStyle());
    btnClose->setFixedHeight(44);

    //Pulsante Create
    QPushButton* btnCreate = new QPushButton(this);
    btnCreate->setIcon(QIcon("../resources/icon/add.png"));
    btnCreate->setIconSize(QSize(30, 30));
    btnCreate->setToolTip("Crea un nuovo elemento");
    btnCreate->setStyleSheet(StyleUtils::getTopButtonStyle());
    btnCreate->setFixedHeight(44);

    

    // Connessioni dei pulsanti
    connect(btnUpload, &QPushButton::clicked, this, &TopMenuWidget::uploadRequested);
    connect(btnNewExport, &QPushButton::clicked, this, &TopMenuWidget::newexportRequested);
    connect(btnClose, &QPushButton::clicked, this, &TopMenuWidget::closeRequested);
    connect(btnCreate, &QPushButton::clicked, this, &TopMenuWidget::createRequested);

    layout->addWidget(btnUpload);
    layout->addWidget(btnNewExport);
    layout->addWidget(btnClose);
    layout->addWidget(btnCreate);
    layout->addStretch();

    this->setLayout(layout);
}
