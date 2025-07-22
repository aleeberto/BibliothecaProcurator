#ifndef MANGA_HEADER
#define MANGA_HEADER
#include "cartaceo.h"
#include <QString>
#include <QJsonObject>
using std::string;

class Manga : public Cartaceo {
private:
    string illustratore;
    int numLibri;
    bool concluso;

public:
    Manga(string titolo, int anno, string immagine, string scrittore, string illustratore, int numLibri, bool concluso);

    string getIllustratore() const;
    int getNumLibri() const;
    bool getConcluso() const;

    void setIllustratore(const string &updIllustratore);
    void setNumLibri(const int &updNumLibri);
    void setConcluso(const bool &updConcluso);

    QString getDetails() const override;
    QString getTypeName() const override;
    QString getShortDescription() const override;
    bool matchesSearch(const QString& searchTerm) const override;
    QJsonObject toJson() const override;
};

#endif
