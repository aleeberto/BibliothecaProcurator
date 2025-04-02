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
#include "../logic/Media.h"
#include "../logic/Series.h"
#include "../logic/Anime.h"
#include "../logic/SerieTv.h"
#include "../logic/Film.h"
#include "../logic/Libro.h"
#include "../logic/Manga.h"
#include "../logic/Cd.h"

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