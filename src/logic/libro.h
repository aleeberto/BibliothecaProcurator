#ifndef LIBRO_HEADER
#define LIBRO_HEADER
#include "cartaceo.h"
#include <QString>
#include <QJsonObject>
using std::string;

class Libro : public Cartaceo {
private:
    int annoStampa;
    string casaEditrice;

public:
    Libro(string titolo, int anno, string immagine, string scrittore, int annoStampa, string casaEditrice);

    int getAnnoStampa() const;
    string getCasaEditrice() const;

    void setAnnoStampa(const int &updAnnoStampa);
    void setCasaEditrice(const string &updCasaEditrice);

    QString getDetails() const override;
    QString getTypeName() const override;
    QString getShortDescription() const override;
    bool matchesSearch(const QString& searchTerm) const override;
    QJsonObject toJson() const override;
};

#endif
