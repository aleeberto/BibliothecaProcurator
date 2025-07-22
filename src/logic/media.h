#ifndef MEDIA_HEADER
#define MEDIA_HEADER
#include <string>
#include <QString>
#include <QJsonObject>
using std::string;

class Media{
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

        virtual QString getDetails() const = 0;
        virtual QString getTypeName() const = 0;
        virtual QString getShortDescription() const = 0;
        virtual bool matchesSearch(const QString& searchTerm) const;
        virtual QJsonObject toJson() const = 0;
    };

#endif
