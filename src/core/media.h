#ifndef MEDIA_HEADER
#define MEDIA_HEADER

#include <string>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
using std::string;

// Forward declarations
class Film;
class Manga;
class Anime;
class SerieTv;
class Series;
class Cartaceo;
class Libro;

class Media {
private:
    string titolo;
    int anno;
    string immagine;

public:
    Media(string titolo, int anno, string immagine);
    virtual ~Media() = default;

    string getTitolo() const;
    int getAnno() const;
    string getImmagine() const;

    void setTitolo(const string &updTitolo);
    void setImmagine(const string &updImmagine);
    void setAnno(const int &updAnno);

    // Serializzazione JSON
    virtual QJsonObject toJson() const;

    // Factory per deserializzare dal JSON
    static Media* fromJson(const QJsonObject& obj);
};

#endif
