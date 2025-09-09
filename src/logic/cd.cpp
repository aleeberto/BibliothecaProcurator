#include "cd.h"
using std::string;

Cd::Cd(string titolo, int anno, string immagine, string artista, int numTracce, int durataMedTracce) : 
    Media(titolo, anno, immagine), artista(artista), numTracce(numTracce), durataMedTracce(durataMedTracce){}

string Cd::getArtista() const{
    return artista;
}

int Cd::getNumTracce() const{
    return numTracce;
}

int Cd::getDurataMedTracce() const{
    return durataMedTracce;
}

void Cd::setArtista(const string &updArtista){
    artista = updArtista;
}

void Cd::setNumTracce(const int &updNumTracce){
    numTracce = updNumTracce;
}

void Cd::setDurataMedTracce(const int &updDurataMedTracce){
    durataMedTracce = updDurataMedTracce;
}

QJsonObject Cd::toJsonSpecific() const {
    QJsonObject json;
    json["type"] = "Cd";
    json["artista"] = QString::fromStdString(artista);
    json["numTracce"] = numTracce;
    json["durataMedTracce"] = durataMedTracce;
    return json;
}

void Cd::fromJsonSpecific(const QJsonObject& json) {
    artista = json["artista"].toString().toStdString();
    numTracce = json["numTracce"].toInt();
    durataMedTracce = json["durataMedTracce"].toInt();
}

Media* Cd::clone() const {
    return new Cd(getTitolo(), getAnno(), getImmagine(), artista, numTracce, durataMedTracce);
}

void Cd::accept(MediaVisitor* visitor) {
    if (visitor) {
        visitor->visit(this);
    }
}

bool Cd::matchesCategory(const string& category) const {
    return category == "Tutti" || category == "Cd";
}