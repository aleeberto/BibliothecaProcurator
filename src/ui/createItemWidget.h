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
#include "../core/media.h"
#include "../core/series.h"
#include "../core/anime.h"
#include "../core/serieTv.h"
#include "../core/film.h"
#include "../core/libro.h"
#include "../core/manga.h"
#include "../core/cd.h"
#include "../core/cartaceo.h"

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