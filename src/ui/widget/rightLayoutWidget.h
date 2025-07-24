#ifndef RIGHTLAYOUTWIDGET_H
#define RIGHTLAYOUTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QVector>
#include "../../logic/media.h"
#include "../../services/jsonService.h"

class RightLayoutWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RightLayoutWidget(QWidget *parent = nullptr);
    ~RightLayoutWidget();

    void setMediaCollection(const QVector<Media*>& collection);
    void setJsonService(JsonService* service);
    void displayMediaByCategory(const QString &category, const QString &searchText = "");
    void clearLayout();
    void showCreateItemWidget(QWidget* createWidget);

private:
    void addMediaCardToLayout(Media* media);
    QPixmap loadMediaImage(const std::string& imagePath);

    QVBoxLayout *mainLayout;
    QVector<Media*> mediaCollection;
    JsonService *jsonService;
    QString currentCategory;
    QString currentSearchText;
};

#endif // RIGHTLAYOUTWIDGET_H
