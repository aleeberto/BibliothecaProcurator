#include "libro.h"
using std::string;

Libro::Libro(string titolo, int anno, string immagine, string scrittore, int annoStampa, string casaEditrice) : 
    Cartaceo(titolo, anno, immagine, scrittore), annoStampa(annoStampa), casaEditrice(casaEditrice){}

int Libro::getAnnoStampa()const{
    return annoStampa;
}

string Libro::getCasaEditrice()const{
    return casaEditrice;
}

void Libro::setAnnoStampa(const int &updAnnoStampa){
    annoStampa = updAnnoStampa;
}

void Libro::setCasaEditrice(const string &updCasaEditrice){
    casaEditrice = updCasaEditrice;
}

// Implementazione metodi virtuali
string Libro::getMediaType() const {
    return "Libro";
}

std::vector<std::pair<string, string>> Libro::getSpecificDetails() const {
    auto details = getCartaceoBaseDetails(); // Eredita dettagli base cartacei
    details.insert(details.end(), {
        {"Anno di Stampa", std::to_string(annoStampa)},
        {"Casa Editrice", casaEditrice}
    });
    return details;
}

QJsonObject Libro::toJsonSpecific() const {
    auto json = getCartaceoBaseJson(); // Eredita JSON base cartacei
    json["annoStampa"] = annoStampa;
    json["casaEditrice"] = QString::fromStdString(casaEditrice);
    return json;
}

void Libro::fromJsonSpecific(const QJsonObject& json) {
    setCartaceoBaseFromJson(json); // Imposta campi base cartacei
    annoStampa = json["annoStampa"].toInt();
    casaEditrice = json["casaEditrice"].toString().toStdString();
}

Media* Libro::clone() const {
    return new Libro(getTitolo(), getAnno(), getImmagine(), getScrittore(), 
                    annoStampa, casaEditrice);
}