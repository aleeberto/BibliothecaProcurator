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

QJsonObject Manga::toJsonSpecific() const {
    auto json = getCartaceoBaseJson();
    json["type"] = "Manga";
    json["illustratore"] = QString::fromStdString(illustratore);
    json["numLibri"] = numLibri;
    json["concluso"] = concluso;
    return json;
}

void Manga::fromJsonSpecific(const QJsonObject& json) {
    setCartaceoBaseFromJson(json);
    illustratore = json["illustratore"].toString().toStdString();
    numLibri = json["numLibri"].toInt();
    concluso = json["concluso"].toBool();
}

Media* Manga::clone() const {
    return new Manga(getTitolo(), getAnno(), getImmagine(), getScrittore(), 
                    illustratore, numLibri, concluso);
}

void Manga::accept(MediaVisitor* visitor) {
    if (visitor) {
        visitor->visit(this);
    }
}

bool Manga::matchesCategory(const string& category) const {
    return category == "Tutti" || category == "Manga";
}