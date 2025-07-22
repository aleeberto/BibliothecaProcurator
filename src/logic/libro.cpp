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

QString Libro::getDetails() const {
    return QString("Libro: %1 (%2) - Scrittore: %3, Anno Stampa: %4, Casa Editrice: %5")
           .arg(QString::fromStdString(getTitolo()))
           .arg(getAnno())
           .arg(QString::fromStdString(getScrittore()))
           .arg(getAnnoStampa())
           .arg(QString::fromStdString(getCasaEditrice()));
}

QString Libro::getTypeName() const {
    return "Libri";
}

QString Libro::getShortDescription() const {
    return QString("%1 (%2) - %3")
           .arg(QString::fromStdString(getTitolo()))
           .arg(getAnno())
           .arg(QString::fromStdString(getScrittore()));
}

bool Libro::matchesSearch(const QString& searchTerm) const {
    QString title = QString::fromStdString(getTitolo()).toLower();
    QString scrittore = QString::fromStdString(getScrittore()).toLower();
    return title.contains(searchTerm.toLower()) || scrittore.contains(searchTerm.toLower());
}

QJsonObject Libro::toJson() const {
    QJsonObject jsonObj;
    jsonObj["type"] = "Libri";
    jsonObj["titolo"] = QString::fromStdString(getTitolo());
    jsonObj["anno"] = getAnno();
    jsonObj["immagine"] = QString::fromStdString(getImmagine());
    jsonObj["scrittore"] = QString::fromStdString(getScrittore());
    jsonObj["annoStampa"] = getAnnoStampa();
    jsonObj["casaEditrice"] = QString::fromStdString(getCasaEditrice());
    return jsonObj;
}
