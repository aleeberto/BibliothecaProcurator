#include "anime.h"
using std::string;

Anime::Anime(string titolo, int anno, string immagine, int numEpisodi, int numStagioni, int durataMediaEp, bool inCorso, string disegnatore, string studioAnimazione) :
    Series(titolo, anno, immagine, numEpisodi, numStagioni, durataMediaEp, inCorso), disegnatore(disegnatore), studioAnimazione(studioAnimazione){}

string Anime::getDisegnatore() const{
    return disegnatore;
}

string Anime::getStudioAnimazione() const{
    return studioAnimazione;
}

void Anime::setDisegnatore(const string &updDisegnatore){
    disegnatore = updDisegnatore;
}

void Anime::setStudioAnimazione(const string &updStudioAnimazione){
    studioAnimazione = updStudioAnimazione;
}

// Implementazione metodi virtuali
string Anime::getMediaType() const {
    return "Anime";
}

std::vector<std::pair<string, string>> Anime::getSpecificDetails() const {
    auto details = getSeriesBaseDetails(); // Eredita dettagli base delle serie
    details.insert(details.end(), {
        {"Disegnatore", disegnatore},
        {"Studio", studioAnimazione}
    });
    return details;
}

QJsonObject Anime::toJsonSpecific() const {
    auto json = getSeriesBaseJson(); // Eredita JSON base delle serie
    json["disegnatore"] = QString::fromStdString(disegnatore);
    json["studioAnimazione"] = QString::fromStdString(studioAnimazione);
    return json;
}

void Anime::fromJsonSpecific(const QJsonObject& json) {
    setSeriesBaseFromJson(json); // Imposta campi base delle serie
    disegnatore = json["disegnatore"].toString().toStdString();
    studioAnimazione = json["studioAnimazione"].toString().toStdString();
}

Media* Anime::clone() const {
    return new Anime(getTitolo(), getAnno(), getImmagine(), getNumEpisodi(), 
                    getNumStagioni(), getDurataMediaEp(), getInCorso(), 
                    disegnatore, studioAnimazione);
}