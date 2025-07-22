#ifndef CD_HEADER
#define CD_HEADER
#include "media.h"
#include <QString>
#include <QJsonObject>
using std::string;

class Cd : public Media {
private:
    string artista;
    int numTracce;
    int durataMedTracce;

public:
    Cd(string titolo, int anno, string immagine, string artista, int numTracce, int durataMedTracce);

    string getArtista() const;
    int getNumTracce() const;
    int getDurataMedTracce() const;

    void setArtista(const string &updArtista);
    void setNumTracce(const int &updNumTracce);
    void setDurataMedTracce(const int &updDurataMedTracce);

    QString getDetails() const override;
    QString getTypeName() const override;
    QString getShortDescription() const override;
    bool matchesSearch(const QString& searchTerm) const override;
    QJsonObject toJson() const override;
};

#endif
