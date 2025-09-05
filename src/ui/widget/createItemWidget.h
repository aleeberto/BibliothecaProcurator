#ifndef CREATEITEMWIDGET_HEADER
#define CREATEITEMWIDGET_HEADER

#include <QWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QStackedWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QResizeEvent>
#include <QMessageBox>
#include <vector>
#include <utility>
#include "../../logic/media.h"
#include "../../services/mediaService.h"

class CreateItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CreateItemWidget(QWidget *parent = nullptr);
    Media* createMediaItem() const;
    
    // Metodi per la modalità di modifica
    void setEditMode(Media* media);
    void clearEditMode();
    bool isInEditMode() const;
    
    // Metodo per impostare il MediaService
    void setMediaService(MediaService* service);

signals:
    void itemCreated(Media* newItem);
    void itemUpdated(Media* oldMedia, Media* newMedia);

public slots:
    void onItemTypeChanged(int index);

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void onCreateButtonClicked();

private:
    void addFieldWithPlaceholder(QVBoxLayout* layout, const QString& labelText, const QString& placeholder);
    void updateScrollBarVisibility();
    void populateFieldsFromMedia(Media* media);
    void populateSpecificFieldsFromDetails(QList<QLineEdit*>& fields, 
        const std::vector<std::pair<std::string, std::string>>& details, const QString& mediaType);

    QComboBox *itemTypeCombo;
    QStackedWidget *stackedFields;
    QPushButton *createButton;
    QScrollArea *scrollArea;
    
    Media* editingMedia;
    bool editMode;
    
    MediaService* mediaService;
};

#endif