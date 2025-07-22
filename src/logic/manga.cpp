#include "manga.h"
using std::string;

Manga::Manga(string titolo, int anno, string immagine, string scrittore, string illustratore, int numLibri, bool concluso) :
    Cartaceo(titolo, anno, immagine, scrittore), illustratore(illustratore), numLibri(numLibri), concluso(concluso){}

string Manga::getIllustratore() const {
    return illustratore;
}

int Manga::getNumLibri() const {
    return numLibri;
}

bool Manga::getConcluso() const {
    return concluso;
}

void Manga::setIllustratore(const string &updIllustratore) {
    illustratore = updIllustratore;
}

void Manga::setNumLibri(const int &updNumLibri) {
    numLibri = updNumLibri;
}

void Manga::setConcluso(const bool &updConcluso) {
    concluso = updConcluso;
}

QString Manga::getDetails() const {
    return QString("Manga: %1 (%2) - Scrittore: %3, Illustratore: %4, Volumi: %5, Stato: %6")
           .arg(QString::fromStdString(getTitolo()))
           .arg(getAnno())
           .arg(QString::fromStdString(getScrittore()))
           .arg(QString::fromStdString(getIllustratore()))
           .arg(getNumLibri())
           .arg(getConcluso() ? "Concluso" : "In corso");
}

QString Manga::getTypeName() const {
    return "Manga";
}

QString Manga::getShortDescription() const {
    return QString("%1 (%2) - %3")
           .arg(QString::fromStdString(getTitolo()))
           .arg(getAnno())
           .arg(QString::fromStdString(getScrittore()));
}

bool Manga::matchesSearch(const QString& searchTerm) const {
    QString title = QString::fromStdString(getTitolo()).toLower();
    QString scrittore = QString::fromStdString(getScrittore()).toLower();
    QString illustratore = QString::fromStdString(getIllustratore()).toLower();
    return title.contains(searchTerm.toLower()) || scrittore.contains(searchTerm.toLower()) || illustratore.contains(searchTerm.toLower());
}

QJsonObject Manga::toJson() const {
    QJsonObject jsonObj;
    jsonObj["type"] = "Manga";
    jsonObj["titolo"] = QString::fromStdString(getTitolo());
    jsonObj["anno"] = getAnno();
    jsonObj["immagine"] = QString::fromStdString(getImmagine());
    jsonObj["scrittore"] = QString::fromStdString(getScrittore());
    jsonObj["illustratore"] = QString::fromStdString(getIllustratore());
    jsonObj["numLibri"] = getNumLibri();
    jsonObj["concluso"] = getConcluso();
    return jsonObj;
}
