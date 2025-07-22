#include "anime.h"
using std::string;

Anime::Anime(string titolo, int anno, string immagine, int numEpisodi, int numStagioni, int durataMediaEp, bool inCorso, string disegnatore, string studioAnimazione) :
    Series(titolo, anno, immagine, numEpisodi, numStagioni, durataMediaEp, inCorso), disegnatore(disegnatore), studioAnimazione(studioAnimazione){}

string Anime::getDisegnatore() const{
    return disegnatore;
}

string Anime::getStudioAnimazione() const{
    return studioAnimazione;
}

void Anime::setDisegnatore(const string &updDisegnatore){
    disegnatore = updDisegnatore;
}

void Anime::setStudioAnimazione(const string &updStudioAnimazione){
    studioAnimazione = updStudioAnimazione;
}

QString Anime::getDetails() const {
    return QString("Anime: %1 (%2) - %3 episodes, %4 seasons, %5 min per episode")
           .arg(QString::fromStdString(getTitolo()))
           .arg(getAnno())
           .arg(getNumEpisodi())
           .arg(getNumStagioni())
           .arg(getDurataMediaEp());
}

QString Anime::getTypeName() const {
    return "Anime";
}

QString Anime::getShortDescription() const {
    return QString("%1 (%2) - %3 episodes, %4 seasons")
           .arg(QString::fromStdString(getTitolo()))
           .arg(getAnno())
           .arg(getNumEpisodi())
           .arg(getNumStagioni());
}

bool Anime::matchesSearch(const QString& searchTerm) const {
    QString title = QString::fromStdString(getTitolo()).toLower();
    QString disegnatoreStr = QString::fromStdString(getDisegnatore()).toLower();
    return title.contains(searchTerm.toLower()) || disegnatoreStr.contains(searchTerm.toLower());
}

QJsonObject Anime::toJson() const {
    QJsonObject jsonObj;
    jsonObj["type"] = "Anime";
    jsonObj["titolo"] = QString::fromStdString(getTitolo());
    jsonObj["anno"] = getAnno();
    jsonObj["immagine"] = QString::fromStdString(getImmagine());
    jsonObj["numEpisodi"] = getNumEpisodi();
    jsonObj["numStagioni"] = getNumStagioni();
    jsonObj["durataMediaEp"] = getDurataMediaEp();
    jsonObj["inCorso"] = getInCorso();
    jsonObj["disegnatore"] = QString::fromStdString(getDisegnatore());
    jsonObj["studioAnimazione"] = QString::fromStdString(getStudioAnimazione());
    return jsonObj;
}
