#include "series.h"
using std::string;

Series::Series(string titolo, int anno, string immagine, int numEpisodi, int numStagioni, int durataMediaEp, bool inCorso) : 
    Media(titolo, anno, immagine), numEpisodi(numEpisodi), numStagioni(numStagioni), durataMediaEp(durataMediaEp), inCorso(inCorso){}

int Series::getNumEpisodi() const{
    return numEpisodi;
}

int Series::getNumStagioni() const{
    return numStagioni;
}

int Series::getDurataMediaEp() const{
    return durataMediaEp;
}

bool Series::getInCorso() const{
    return inCorso;
}

void Series::setNumEpisodi(const int &updNumEpisodi){
    numEpisodi = updNumEpisodi;
}

void Series::setNumStagioni(const int &updNumStagioni){
    numStagioni = updNumStagioni;
}

void Series::setDurataMediaEp(const int &updDurataMediaEp){
    durataMediaEp = updDurataMediaEp;
}

void Series::setInCorso(const bool &updInCorso){
    inCorso = updInCorso;
}

// Metodi helper per le classi derivate
std::vector<std::pair<string, string>> Series::getSeriesBaseDetails() const {
    return {
        {"Stagioni", std::to_string(numStagioni)},
        {"Episodi", std::to_string(numEpisodi)},
        {"Durata episodio", std::to_string(durataMediaEp) + " min"},
        {"Stato", inCorso ? "In corso" : "Conclusa"}
    };
}

QJsonObject Series::getSeriesBaseJson() const {
    QJsonObject json;
    json["numEpisodi"] = numEpisodi;
    json["numStagioni"] = numStagioni;
    json["durataMediaEp"] = durataMediaEp;
    json["inCorso"] = inCorso;
    return json;
}

void Series::setSeriesBaseFromJson(const QJsonObject& json) {
    numEpisodi = json["numEpisodi"].toInt();
    numStagioni = json["numStagioni"].toInt();
    durataMediaEp = json["durataMediaEp"].toInt();
    inCorso = json["inCorso"].toBool();
}