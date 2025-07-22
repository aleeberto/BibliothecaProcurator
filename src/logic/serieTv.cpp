#include "serieTv.h"
using std::string;

SerieTv::SerieTv(string titolo, int anno, string immagine, int numEpisodi, int numStagioni, int durataMediaEp, bool inCorso, string ideatore, string casaProduttrice) :
    Series(titolo, anno, immagine, numEpisodi, numStagioni, durataMediaEp, inCorso), ideatore(ideatore), casaProduttrice(casaProduttrice){}

string SerieTv::getIdeatore() const{
    return ideatore;
}

string SerieTv::getCasaProduttrice() const{
    return casaProduttrice;
}

void SerieTv::setIdeatore(const string &updIdeatore){
    ideatore = updIdeatore;
}

void SerieTv::setCasaProduttrice(const string &updCasaProduttrice){
    casaProduttrice = updCasaProduttrice;
}

QString SerieTv::getDetails() const {
    return QString("Serie TV: %1 (%2) - %3 episodes, %4 seasons, %5 min per episode")
           .arg(QString::fromStdString(getTitolo()))
           .arg(getAnno())
           .arg(getNumEpisodi())
           .arg(getNumStagioni())
           .arg(getDurataMediaEp());
}

QString SerieTv::getTypeName() const {
    return "Serie Tv";
}

QString SerieTv::getShortDescription() const {
    return QString("%1 (%2) - %3 episodes, %4 seasons")
           .arg(QString::fromStdString(getTitolo()))
           .arg(getAnno())
           .arg(getNumEpisodi())
           .arg(getNumStagioni());
}

bool SerieTv::matchesSearch(const QString& searchTerm) const {
    QString title = QString::fromStdString(getTitolo()).toLower();
    QString ideatore = QString::fromStdString(getIdeatore()).toLower();
    return title.contains(searchTerm.toLower()) || ideatore.contains(searchTerm.toLower());
}

QJsonObject SerieTv::toJson() const {
    QJsonObject jsonObj;
    jsonObj["type"] = "Serie Tv";
    jsonObj["titolo"] = QString::fromStdString(getTitolo());
    jsonObj["anno"] = getAnno();
    jsonObj["immagine"] = QString::fromStdString(getImmagine());
    jsonObj["numEpisodi"] = getNumEpisodi();
    jsonObj["numStagioni"] = getNumStagioni();
    jsonObj["durataMediaEp"] = getDurataMediaEp();
    jsonObj["inCorso"] = getInCorso();
    jsonObj["ideatore"] = QString::fromStdString(getIdeatore());
    jsonObj["casaProduttrice"] = QString::fromStdString(getCasaProduttrice());
    return jsonObj;
}
