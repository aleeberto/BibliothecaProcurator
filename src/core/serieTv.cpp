#include "serietv.h"
using std::string;

SerieTv::SerieTv(string titolo, int anno, string immagine, int numEpisodi, int numStagioni, int durataMediaEp, bool inCorso,
                 string ideatore, string casaProduttrice) :
    Series(titolo, anno, immagine, numEpisodi, numStagioni, durataMediaEp, inCorso),
    ideatore(ideatore), casaProduttrice(casaProduttrice) {}

string SerieTv::getIdeatore() const {
    return ideatore;
}

string SerieTv::getCasaProduttrice() const {
    return casaProduttrice;
}

void SerieTv::setIdeatore(const string &updIdeatore) {
    ideatore = updIdeatore;
}

void SerieTv::setCasaProduttrice(const string &updCasaProduttrice) {
    casaProduttrice = updCasaProduttrice;
}

QJsonObject SerieTv::toJson() const {
    QJsonObject obj = Series::toJson();
    obj["type"] = "SerieTv";
    obj["ideatore"] = QString::fromStdString(ideatore);
    obj["casaProduttrice"] = QString::fromStdString(casaProduttrice);
    return obj;
}

SerieTv* SerieTv::fromJson(const QJsonObject& obj) {
    string titolo = obj["titolo"].toString().toStdString();
    int anno = obj["anno"].toInt();
    string immagine = obj["immagine"].toString().toStdString();
    int numEpisodi = obj["numEpisodi"].toInt();
    int numStagioni = obj["numStagioni"].toInt();
    int durataMediaEp = obj["durataMediaEp"].toInt();
    bool inCorso = obj["inCorso"].toBool();
    string ideatore = obj["ideatore"].toString().toStdString();
    string casaProduttrice = obj["casaProduttrice"].toString().toStdString();

    return new SerieTv(titolo, anno, immagine, numEpisodi, numStagioni, durataMediaEp, inCorso, ideatore, casaProduttrice);
}
