#include "media.h"
#include "film.h"
#include "manga.h"
#include "anime.h"
#include "serietv.h"
#include "series.h"
#include "cartaceo.h"
#include "libro.h"

using std::string;

Media::Media(string titolo, int anno, string immagine) : titolo(titolo), anno(anno), immagine(immagine) {}

string Media::getTitolo() const {
    return titolo;
}

int Media::getAnno() const {
    return anno;
}

string Media::getImmagine() const {
    return immagine;
}

void Media::setTitolo(const string &updTitolo) {
    titolo = updTitolo;
}

void Media::setAnno(const int &updAnno) {
    anno = updAnno;
}

void Media::setImmagine(const string &updImmagine) {
    immagine = updImmagine;
}

QJsonObject Media::toJson() const {
    QJsonObject obj;
    obj["type"] = "Media";
    obj["titolo"] = QString::fromStdString(titolo);
    obj["anno"] = anno;
    obj["immagine"] = QString::fromStdString(immagine);
    return obj;
}

Media* Media::fromJson(const QJsonObject& obj) {
    string type = obj["type"].toString().toStdString();

    if (type == "Film") {
        return Film::fromJson(obj);
    }
    else if (type == "Manga") {
        return Manga::fromJson(obj);
    }
    else if (type == "Anime") {
        return Anime::fromJson(obj);
    }
    else if (type == "SerieTv") {
        return SerieTv::fromJson(obj);
    }
    else if (type == "Libro") {
        return Libro::fromJson(obj);
    }
    else if (type == "Series") {
        return Series::fromJson(obj);
    }
    else if (type == "Cartaceo") {
        return Cartaceo::fromJson(obj);
    }
    else if (type == "Media") {
        string titolo = obj["titolo"].toString().toStdString();
        int anno = obj["anno"].toInt();
        string immagine = obj["immagine"].toString().toStdString();
        return new Media(titolo, anno, immagine);
    }

    // Se tipo sconosciuto, ritorna nullptr o un Media base
    return nullptr;
}
