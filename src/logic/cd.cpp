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

QString Cd::getDetails() const {
    return QString("Cd: %1 (%2) - Artista: %3, Tracce: %4, Durata Media: %5 sec")
           .arg(QString::fromStdString(getTitolo()))
           .arg(getAnno())
           .arg(QString::fromStdString(getArtista()))
           .arg(getNumTracce())
           .arg(getDurataMedTracce());
}

QString Cd::getTypeName() const {
    return "Cd";
}

QString Cd::getShortDescription() const {
    return QString("%1 (%2) - %3")
           .arg(QString::fromStdString(getTitolo()))
           .arg(getAnno())
           .arg(QString::fromStdString(getArtista()));
}

bool Cd::matchesSearch(const QString& searchTerm) const {
    QString title = QString::fromStdString(getTitolo()).toLower();
    QString artistaStr = QString::fromStdString(getArtista()).toLower();
    return title.contains(searchTerm.toLower()) || artistaStr.contains(searchTerm.toLower());
}

QJsonObject Cd::toJson() const {
    QJsonObject jsonObj;
    jsonObj["type"] = "Cd";
    jsonObj["titolo"] = QString::fromStdString(getTitolo());
    jsonObj["anno"] = getAnno();
    jsonObj["immagine"] = QString::fromStdString(getImmagine());
    jsonObj["artista"] = QString::fromStdString(getArtista());
    jsonObj["numTracce"] = getNumTracce();
    jsonObj["durataMedTracce"] = getDurataMedTracce();
    return jsonObj;
}
