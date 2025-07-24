#include "series.h"
using std::string;

Series::Series(string titolo, int anno, string immagine, int numEpisodi, int numStagioni, int durataMediaEp, bool inCorso) : 
    Media(titolo, anno, immagine), numEpisodi(numEpisodi), numStagioni(numStagioni), durataMediaEp(durataMediaEp), inCorso(inCorso) {}

int Series::getNumEpisodi() const {
    return numEpisodi;
}

int Series::getNumStagioni() const {
    return numStagioni;
}

int Series::getDurataMediaEp() const {
    return durataMediaEp;
}

bool Series::getInCorso() const {
    return inCorso;
}

void Series::setNumEpisodi(const int &updNumEpisodi) {
    numEpisodi = updNumEpisodi;
}

void Series::setNumStagioni(const int &updNumStagioni) {
    numStagioni = updNumStagioni;
}

void Series::setDurataMediaEp(const int &updDurataMediaEp) {
    durataMediaEp = updDurataMediaEp;
}

void Series::setInCorso(const bool &updInCorso) {
    inCorso = updInCorso;
}

QJsonObject Series::toJson() const {
    QJsonObject obj = Media::toJson();  // chiama la serializzazione base di Media
    obj["type"] = "Series";
    obj["numEpisodi"] = numEpisodi;
    obj["numStagioni"] = numStagioni;
    obj["durataMediaEp"] = durataMediaEp;
    obj["inCorso"] = inCorso;
    return obj;
}

Series* Series::fromJson(const QJsonObject& obj) {
    string titolo = obj["titolo"].toString().toStdString();
    int anno = obj["anno"].toInt();
    string immagine = obj["immagine"].toString().toStdString();
    int numEpisodi = obj["numEpisodi"].toInt();
    int numStagioni = obj["numStagioni"].toInt();
    int durataMediaEp = obj["durataMediaEp"].toInt();
    bool inCorso = obj["inCorso"].toBool();

    return new Series(titolo, anno, immagine, numEpisodi, numStagioni, durataMediaEp, inCorso);
}
