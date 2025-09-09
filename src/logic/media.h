#ifndef MEDIA_HEADER
#define MEDIA_HEADER
#include <string>
#include <vector>
#include <QJsonObject>
#include "mediaVisitor.h"

using std::string;

class Media{
    private:
        string titolo;
        int anno;
        string immagine;

    public:
        Media(string titolo, int anno, string immagine);
        virtual ~Media() = default;

        // Getters/Setters comuni
        string getTitolo() const;
        int getAnno() const;
        string getImmagine() const;
        void setTitolo(const string &updTitolo);
        void setImmagine(const string &updImmagine);
        void setAnno(const int &updAnno);
        
        // Metodi virtuali
        virtual QJsonObject toJsonSpecific() const = 0;
        virtual void fromJsonSpecific(const QJsonObject& json) = 0;
        
        // Metodo clone polimorfismo
        virtual Media* clone() const = 0;
        
        // Visitor pattern
        virtual void accept(MediaVisitor* visitor) = 0;
        
        // Metodi di match per filtri e ricerche
        virtual bool matchesCategory(const string& category) const = 0;
        virtual bool matchesSearch(const string& searchText) const;
};

#endif // MEDIA_HEADER