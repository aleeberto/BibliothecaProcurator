#ifndef FORMWIDGETVISITOR_HEADER
#define FORMWIDGETVISITOR_HEADER

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "../../logic/mediaVisitor.h"

class FormWidgetVisitor : public MediaVisitor {
private:
    QWidget* parentWidget;
    QWidget* resultWidget;
    
public:
    explicit FormWidgetVisitor(QWidget* parent);
    
    void visit(Film* film) override;
    void visit(SerieTv* serieTv) override;
    void visit(Anime* anime) override;
    void visit(Libro* libro) override;
    void visit(Manga* manga) override;
    void visit(Cd* cd) override;
    
    QWidget* getResultWidget() const;
    
private:
    QWidget* createFormWidget(const QStringList& fieldLabels, const QStringList& placeholders, const QStringList& values = QStringList());
    void populateFormFields(QWidget* formWidget, const QStringList& values);
};

#endif