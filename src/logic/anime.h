#ifndef ANIME_HEADER
#define ANIME_HEADER
#include "series.h"
#include <QString>
#include <QJsonObject>
using std::string;

class Anime : public Series {
private:
    string disegnatore;
    string studioAnimazione;

public:
    Anime(string titolo, int anno, string immagine, int numEpisodi, int numStagioni, int durataMediaEp, bool inCorso, string disegnatore, string studioAnimazione);

    string getDisegnatore() const;
    string getStudioAnimazione() const;

    void setDisegnatore(const string &updDisegnatore);
    void setStudioAnimazione(const string &updStudioAnimazione);

    QString getDetails() const override;
    QString getTypeName() const override;
    QString getShortDescription() const override;
    bool matchesSearch(const QString& searchTerm) const override;
    QJsonObject toJson() const override;
};

#endif
