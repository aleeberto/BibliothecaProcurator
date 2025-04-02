#ifndef CREATEITEMWIDGET_H
#define CREATEITEMWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QStackedWidget>

class CreateItemWidget : public QWidget {
    Q_OBJECT

public:
    explicit CreateItemWidget(QWidget *parent = nullptr);

private slots:
    void onItemTypeChanged(int index);

private:
    QComboBox *itemTypeCombo;
    QStackedWidget *stackedFields;
};

#endif
