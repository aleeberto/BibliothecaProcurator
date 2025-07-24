#include "anime.h"

using std::string;

Anime::Anime(string titolo, int anno, string immagine, int numEpisodi, int numStagioni, int durataMediaEp, bool inCorso, string disegnatore, string studioAnimazione) :
    Series(titolo, anno, immagine, numEpisodi, numStagioni, durataMediaEp, inCorso), disegnatore(disegnatore), studioAnimazione(studioAnimazione) {}

string Anime::getDisegnatore() const {
    return disegnatore;
}

string Anime::getStudioAnimazione() const {
    return studioAnimazione;
}

void Anime::setDisegnatore(const string &updDisegnatore) {
    disegnatore = updDisegnatore;
}

void Anime::setStudioAnimazione(const string &updStudioAnimazione) {
    studioAnimazione = updStudioAnimazione;
}

QJsonObject Anime::toJson() const {
    QJsonObject obj = Series::toJson(); // eredita da Series e Media
    obj["type"] = "Anime";
    obj["disegnatore"] = QString::fromStdString(disegnatore);
    obj["studioAnimazione"] = QString::fromStdString(studioAnimazione);
    return obj;
}

Anime* Anime::fromJson(const QJsonObject& obj) {
    string titolo = obj["titolo"].toString().toStdString();
    int anno = obj["anno"].toInt();
    string immagine = obj["immagine"].toString().toStdString();

    int numEpisodi = obj["numEpisodi"].toInt();
    int numStagioni = obj["numStagioni"].toInt();
    int durataMediaEp = obj["durataMediaEp"].toInt();
    bool inCorso = obj["inCorso"].toBool();

    string disegnatore = obj["disegnatore"].toString().toStdString();
    string studioAnimazione = obj["studioAnimazione"].toString().toStdString();

    return new Anime(titolo, anno, immagine, numEpisodi, numStagioni, durataMediaEp, inCorso, disegnatore, studioAnimazione);
}
