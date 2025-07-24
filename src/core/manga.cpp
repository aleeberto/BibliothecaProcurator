#include "manga.h"
using std::string;

Manga::Manga(string titolo, int anno, string immagine, string scrittore, string illustratore, int numLibri, bool concluso) :
    Cartaceo(titolo, anno, immagine, scrittore), illustratore(illustratore), numLibri(numLibri), concluso(concluso) {}

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

QJsonObject Manga::toJson() const {
    QJsonObject obj = Cartaceo::toJson();
    obj["type"] = "Manga";
    obj["illustratore"] = QString::fromStdString(illustratore);
    obj["numLibri"] = numLibri;
    obj["concluso"] = concluso;
    return obj;
}

Manga* Manga::fromJson(const QJsonObject& obj) {
    string titolo = obj["titolo"].toString().toStdString();
    int anno = obj["anno"].toInt();
    string immagine = obj["immagine"].toString().toStdString();
    string scrittore = obj["scrittore"].toString().toStdString();
    string illustratore = obj["illustratore"].toString().toStdString();
    int numLibri = obj["numLibri"].toInt();
    bool concluso = obj["concluso"].toBool();

    return new Manga(titolo, anno, immagine, scrittore, illustratore, numLibri, concluso);
}
