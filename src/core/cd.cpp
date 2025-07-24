#include "cd.h"

using std::string;

Cd::Cd(string titolo, int anno, string immagine, string artista, int numTracce, int durataMedTracce)
    : Media(titolo, anno, immagine), artista(artista), numTracce(numTracce), durataMedTracce(durataMedTracce) {}

string Cd::getArtista() const {
    return artista;
}

int Cd::getNumTracce() const {
    return numTracce;
}

int Cd::getDurataMedTracce() const {
    return durataMedTracce;
}

void Cd::setArtista(const string& updArtista) {
    artista = updArtista;
}

void Cd::setNumTracce(const int& updNumTracce) {
    numTracce = updNumTracce;
}

void Cd::setDurataMedTracce(const int& updDurataMedTracce) {
    durataMedTracce = updDurataMedTracce;
}

// JSON serialization

QJsonObject Cd::toJson() const {
    QJsonObject jsonObj = Media::toJson();
    jsonObj["type"] = "Cd";
    jsonObj["artista"] = QString::fromStdString(artista);
    jsonObj["numTracce"] = numTracce;
    jsonObj["durataMedTracce"] = durataMedTracce;
    return jsonObj;
}

Cd* Cd::fromJson(const QJsonObject& obj) {
    string titolo = obj["titolo"].toString().toStdString();
    int anno = obj["anno"].toInt();
    string immagine = obj["immagine"].toString().toStdString();
    string artista = obj["artista"].toString().toStdString();
    int numTracce = obj["numTracce"].toInt();
    int durataMedTracce = obj["durataMedTracce"].toInt();

    return new Cd(titolo, anno, immagine, artista, numTracce, durataMedTracce);
}
