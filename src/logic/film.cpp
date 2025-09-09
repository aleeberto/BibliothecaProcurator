#include "film.h"
using std::string;

Film::Film(string titolo, int anno, string immagine, string regista, string attoreProtagonista, int durata) : 
    Media(titolo, anno, immagine), regista(regista), attoreProtagonista(attoreProtagonista), durata(durata){}

string Film::getRegista() const{
    return regista;
}

string Film::getAttoreProtagonista() const{
    return attoreProtagonista;
}

int Film::getDurata() const{
    return durata;
}

void Film::setRegista(const string &updRegista){
    regista = updRegista;
}

void Film::setAttoreProtagonista(const string &updAttoreProtagonista){
    attoreProtagonista = updAttoreProtagonista;
}

void Film::setDurata(const int &updDurata){
    durata = updDurata;
}

QJsonObject Film::toJsonSpecific() const {
    QJsonObject json;
    json["type"] = "Film";
    json["regista"] = QString::fromStdString(regista);
    json["attoreProtagonista"] = QString::fromStdString(attoreProtagonista);
    json["durata"] = durata;
    return json;
}

void Film::fromJsonSpecific(const QJsonObject& json) {
    regista = json["regista"].toString().toStdString();
    attoreProtagonista = json["attoreProtagonista"].toString().toStdString();
    durata = json["durata"].toInt();
}

Media* Film::clone() const {
    return new Film(getTitolo(), getAnno(), getImmagine(), regista, attoreProtagonista, durata);
}

void Film::accept(MediaVisitor* visitor) {
    if (visitor) {
        visitor->visit(this);
    }
}

bool Film::matchesCategory(const string& category) const {
    return category == "Tutti" || category == "Film";
}