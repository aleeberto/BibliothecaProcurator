#ifndef CREATEITEMWIDGET_H
#define CREATEITEMWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QStackedWidget>
#include <QPushButton>
#include <QMessageBox>
#include "../../logic/media.h"
#include "../../logic/series.h"
#include "../../logic/anime.h"
#include "../../logic/serieTv.h"
#include "../../logic/film.h"
#include "../../logic/libro.h"
#include "../../logic/manga.h"
#include "../../logic/cd.h"
#include "../../logic/cartaceo.h"

class CreateItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CreateItemWidget(QWidget *parent = nullptr);
    Media* createMediaItem() const;

signals:
    void itemCreated(Media* newItem);

public slots:
    void onItemTypeChanged(int index);

private slots:
    void onCreateButtonClicked();

private:
    void addFieldWithPlaceholder(QVBoxLayout* layout, const QString& labelText, const QString& placeholder);

    QComboBox *itemTypeCombo;
    QStackedWidget *stackedFields;
    QPushButton *createButton;
};

#endif // CREATEITEMWIDGET_H