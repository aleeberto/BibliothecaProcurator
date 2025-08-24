#include "manga.h"
using std::string;

Manga::Manga(string titolo, int anno, string immagine, string scrittore, string illustratore, int numLibri, bool concluso) :
    Cartaceo(titolo, anno, immagine, scrittore), illustratore(illustratore), numLibri(numLibri), concluso(concluso){}

string Manga::getIllustratore() const {
    return illustratore;
}

int Manga::getNumLibri() const {
    return numLibri;
}

bool Manga::getConcluso() const {
    return concluso;
}

void Manga::setIllustratore(const string &updIllustratore) {
    illustratore = updIllustratore;
}

void Manga::setNumLibri(const int &updNumLibri) {
    numLibri = updNumLibri;
}

void Manga::setConcluso(const bool &updConcluso) {
    concluso = updConcluso;
}

// Implementazione metodi virtuali
string Manga::getMediaType() const {
    return "Manga";
}

std::vector<std::pair<string, string>> Manga::getSpecificDetails() const {
    auto details = getCartaceoBaseDetails(); // Eredita dettagli base cartacei
    details.insert(details.end(), {
        {"Illustratore", illustratore},
        {"Volumi", std::to_string(numLibri)},
        {"Stato", concluso ? "Concluso" : "In corso"}
    });
    return details;
}

QJsonObject Manga::toJsonSpecific() const {
    auto json = getCartaceoBaseJson(); // Eredita JSON base cartacei
    json["illustratore"] = QString::fromStdString(illustratore);
    json["numLibri"] = numLibri;
    json["concluso"] = concluso;
    return json;
}

void Manga::fromJsonSpecific(const QJsonObject& json) {
    setCartaceoBaseFromJson(json); // Imposta campi base cartacei
    illustratore = json["illustratore"].toString().toStdString();
    numLibri = json["numLibri"].toInt();
    concluso = json["concluso"].toBool();
}

Media* Manga::clone() const {
    return new Manga(getTitolo(), getAnno(), getImmagine(), getScrittore(), 
                    illustratore, numLibri, concluso);
}