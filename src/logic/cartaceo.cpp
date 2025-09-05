#include "cartaceo.h"
using std::string;

Cartaceo::Cartaceo(string titolo, int anno, string immagine, string scrittore) : 
    Media(titolo, anno, immagine), scrittore(scrittore){}

string Cartaceo::getScrittore() const{
    return scrittore;
}

void Cartaceo::setScrittore(const string &updScrittore){
    scrittore = updScrittore;
}

QJsonObject Cartaceo::getCartaceoBaseJson() const {
    QJsonObject json;
    json["scrittore"] = QString::fromStdString(scrittore);
    return json;
}

void Cartaceo::setCartaceoBaseFromJson(const QJsonObject& json) {
    scrittore = json["scrittore"].toString().toStdString();
}