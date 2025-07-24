#include "cartaceo.h"

using std::string;

Cartaceo::Cartaceo(string titolo, int anno, string immagine, string scrittore) :
    Media(titolo, anno, immagine), scrittore(scrittore) {}

string Cartaceo::getScrittore() const {
    return scrittore;
}

void Cartaceo::setScrittore(const string &updScrittore) {
    scrittore = updScrittore;
}

QJsonObject Cartaceo::toJson() const {
    QJsonObject obj = Media::toJson(); // eredita i campi base
    obj["type"] = "Cartaceo";
    obj["scrittore"] = QString::fromStdString(scrittore);
    return obj;
}

Cartaceo* Cartaceo::fromJson(const QJsonObject& obj) {
    string titolo = obj["titolo"].toString().toStdString();
    int anno = obj["anno"].toInt();
    string immagine = obj["immagine"].toString().toStdString();

    string scrittore = obj["scrittore"].toString().toStdString();

    return new Cartaceo(titolo, anno, immagine, scrittore);
}
