#include "film.h"
#include <QJsonObject>
using std::string;

Film::Film(string titolo, int anno, string immagine, string regista, string attoreProtagonista, int durata) :
    Media(titolo, anno, immagine), regista(regista), attoreProtagonista(attoreProtagonista), durata(durata) {}

string Film::getRegista() const {
    return regista;
}

string Film::getAttoreProtagonista() const {
    return attoreProtagonista;
}

int Film::getDurata() const {
    return durata;
}

void Film::setRegista(const string &updRegista) {
    regista = updRegista;
}

void Film::setAttoreProtagonista(const string &updAttoreProtagonista) {
    attoreProtagonista = updAttoreProtagonista;
}

void Film::setDurata(const int &updDurata) {
    durata = updDurata;
}

QJsonObject Film::toJson() const {
    QJsonObject obj = Media::toJson();
    obj["type"] = "Film";  // sovrascrive il tipo
    obj["regista"] = QString::fromStdString(regista);
    obj["attoreProtagonista"] = QString::fromStdString(attoreProtagonista);
    obj["durata"] = durata;
    return obj;
}

Film* Film::fromJson(const QJsonObject& obj) {
    string titolo = obj["titolo"].toString().toStdString();
    int anno = obj["anno"].toInt();
    string immagine = obj["immagine"].toString().toStdString();
    string regista = obj["regista"].toString().toStdString();
    string attoreProtagonista = obj["attoreProtagonista"].toString().toStdString();
    int durata = obj["durata"].toInt();

    return new Film(titolo, anno, immagine, regista, attoreProtagonista, durata);
}
