#ifndef FILM_HEADER
#define FILM_HEADER
#include "media.h"
#include <QJsonObject>
using std::string;

class Film : public Media{
    private:
        string regista;
        string attoreProtagonista;
        int durata;
    
    public:
        Film(string titolo, int anno, string immagine, string regista, string attoreProtagonista, int durata);
        virtual ~Film() = default;

        // Getters/Setters specifici Film
        string getRegista() const;
        string getAttoreProtagonista() const;
        int getDurata() const;
        void setRegista(const string &updRegista);
        void setAttoreProtagonista(const string &updAttoreProtagonista);
        void setDurata(const int &durata);
        
        // Implementazione metodi virtuali
        QJsonObject toJsonSpecific() const override;
        void fromJsonSpecific(const QJsonObject& json) override;
        Media* clone() const override;
        
        // Visitor pattern
        void accept(MediaVisitor* visitor) override;
        
        // Polimorfismo per filtri
        bool matchesCategory(const string& category) const override;
};

#endif // FILM_HEADER