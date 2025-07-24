#include "libro.h"
using std::string;

Libro::Libro(string titolo, int anno, string immagine, string scrittore, int annoStampa, string casaEditrice) :
    Cartaceo(titolo, anno, immagine, scrittore), annoStampa(annoStampa), casaEditrice(casaEditrice) {}

int Libro::getAnnoStampa() const {
    return annoStampa;
}

string Libro::getCasaEditrice() const {
    return casaEditrice;
}

void Libro::setAnnoStampa(const int &updAnnoStampa) {
    annoStampa = updAnnoStampa;
}

void Libro::setCasaEditrice(const string &updCasaEditrice) {
    casaEditrice = updCasaEditrice;
}

QJsonObject Libro::toJson() const {
    QJsonObject obj = Cartaceo::toJson();
    obj["type"] = "Libro";
    obj["annoStampa"] = annoStampa;
    obj["casaEditrice"] = QString::fromStdString(casaEditrice);
    return obj;
}

Libro* Libro::fromJson(const QJsonObject& obj) {
    string titolo = obj["titolo"].toString().toStdString();
    int anno = obj["anno"].toInt();
    string immagine = obj["immagine"].toString().toStdString();
    string scrittore = obj["scrittore"].toString().toStdString();
    int annoStampa = obj["annoStampa"].toInt();
    string casaEditrice = obj["casaEditrice"].toString().toStdString();

    return new Libro(titolo, anno, immagine, scrittore, annoStampa, casaEditrice);
}
