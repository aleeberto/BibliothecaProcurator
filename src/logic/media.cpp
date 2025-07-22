#include "media.h"
using std::string;

Media::Media(string titolo, int anno, string immagine): titolo(titolo), anno(anno), immagine(immagine){}

string Media::getTitolo() const{
    return titolo;
}

int Media::getAnno() const{
    return anno;
}

string Media::getImmagine() const{
    return immagine;
}

void Media::setTitolo(const string &updTitolo){
    titolo = updTitolo;
}

void Media::setAnno(const int &updAnno){
    anno = updAnno;
}

void Media::setImmagine(const string &updImmagine){
    immagine = updImmagine;
}

QString Media::getDetails() const {
    return QString();
}

QString Media::getTypeName() const {
    return QString();
}

QString Media::getShortDescription() const {
    return QString();
}

bool Media::matchesSearch(const QString& searchTerm) const {
    Q_UNUSED(searchTerm);
    return false;
}

QJsonObject Media::toJson() const {
    return QJsonObject();
}
