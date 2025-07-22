#include "film.h"
#include <QJsonObject>

Film::Film(string titolo, int anno, string immagine, string regista, string attoreProtagonista, int durata)
    : Media(titolo, anno, immagine), regista(regista), attoreProtagonista(attoreProtagonista), durata(durata) {}

string Film::getRegista() const { return regista; }
string Film::getAttoreProtagonista() const { return attoreProtagonista; }
int Film::getDurata() const { return durata; }

void Film::setRegista(const string &updRegista) { regista = updRegista; }
void Film::setAttoreProtagonista(const string &updAttoreProtagonista) { attoreProtagonista = updAttoreProtagonista; }
void Film::setDurata(const int &updDurata) { durata = updDurata; }

QString Film::getDetails() const {
    return QString("Film: %1 (%2) - Regista: %3, Durata: %4 min")
           .arg(QString::fromStdString(getTitolo()))
           .arg(getAnno())
           .arg(QString::fromStdString(getRegista()))
           .arg(getDurata());
}

QString Film::getTypeName() const {
    return "Film";
}

QString Film::getShortDescription() const {
    return QString("%1 (%2) - %3 min")
           .arg(QString::fromStdString(getTitolo()))
           .arg(getAnno())
           .arg(getDurata());
}

bool Film::matchesSearch(const QString& searchTerm) const {
    QString title = QString::fromStdString(getTitolo()).toLower();
    QString director = QString::fromStdString(getRegista()).toLower();
    return title.contains(searchTerm.toLower()) || director.contains(searchTerm.toLower());
}

QJsonObject Film::toJson() const {
    QJsonObject jsonObj;
    jsonObj["type"] = "Film";
    jsonObj["titolo"] = QString::fromStdString(getTitolo());
    jsonObj["anno"] = getAnno();
    jsonObj["immagine"] = QString::fromStdString(getImmagine());
    jsonObj["regista"] = QString::fromStdString(getRegista());
    jsonObj["attoreProtagonista"] = QString::fromStdString(getAttoreProtagonista());
    jsonObj["durata"] = getDurata();
    return jsonObj;
}
