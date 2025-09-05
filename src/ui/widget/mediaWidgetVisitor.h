#ifndef MEDIAWIDGETVISITOR_HEADER
#define MEDIAWIDGETVISITOR_HEADER

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "../../logic/mediaVisitor.h"
#include "../../services/uiService.h"

class MediaWidgetVisitor : public MediaVisitor {
private:
    QWidget* parentWidget;
    UIService* uiService;
    QWidget* resultWidget;
    
public:
    explicit MediaWidgetVisitor(QWidget* parent, UIService* ui);
    
    void visit(Film* film) override;
    void visit(SerieTv* serieTv) override;
    void visit(Anime* anime) override;
    void visit(Libro* libro) override;
    void visit(Manga* manga) override;
    void visit(Cd* cd) override;
    
    QWidget* getResultWidget() const;
    
private:
    QWidget* createBaseWidget(Media* media);
    void addCommonInfo(QVBoxLayout* layout, Media* media);
    void addActionButtons(QHBoxLayout* layout, Media* media);
};

#endif