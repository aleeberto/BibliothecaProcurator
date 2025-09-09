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

QJsonObject Libro::toJsonSpecific() const {
    auto json = getCartaceoBaseJson();
    json["type"] = "Libro";
    json["annoStampa"] = annoStampa;
    json["casaEditrice"] = QString::fromStdString(casaEditrice);
    return json;
}

void Libro::fromJsonSpecific(const QJsonObject& json) {
    setCartaceoBaseFromJson(json);
    annoStampa = json["annoStampa"].toInt();
    casaEditrice = json["casaEditrice"].toString().toStdString();
}

Media* Libro::clone() const {
    return new Libro(getTitolo(), getAnno(), getImmagine(), getScrittore(), 
                    annoStampa, casaEditrice);
}

void Libro::accept(MediaVisitor* visitor) {
    if (visitor) {
        visitor->visit(this);
    }
}

bool Libro::matchesCategory(const string& category) const {
    return category == "Tutti" || category == "Libro";
}