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

QJsonObject SerieTv::toJsonSpecific() const {
    auto json = getSeriesBaseJson();
    json["type"] = "Serie Tv";
    json["ideatore"] = QString::fromStdString(ideatore);
    json["casaProduttrice"] = QString::fromStdString(casaProduttrice);
    return json;
}

void SerieTv::fromJsonSpecific(const QJsonObject& json) {
    setSeriesBaseFromJson(json);
    ideatore = json["ideatore"].toString().toStdString();
    casaProduttrice = json["casaProduttrice"].toString().toStdString();
}

Media* SerieTv::clone() const {
    return new SerieTv(getTitolo(), getAnno(), getImmagine(), getNumEpisodi(), 
                      getNumStagioni(), getDurataMediaEp(), getInCorso(), 
                      ideatore, casaProduttrice);
}

void SerieTv::accept(MediaVisitor* visitor) {
    if (visitor) {
        visitor->visit(this);
    }
}

bool SerieTv::matchesCategory(const string& category) const {
    return category == "Tutti" || category == "Serie Tv";
}