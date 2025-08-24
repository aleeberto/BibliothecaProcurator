#ifndef LIBRO_HEADER
#define LIBRO_HEADER
#include "cartaceo.h"
using std::string;

class Libro : public Cartaceo{
    private:
        int annoStampa;
        string casaEditrice;
    
    public:
        Libro(string titolo, int anno, string immagine, string scrittore, int annoStampa, string casaEditrice);
        virtual ~Libro() = default;

        // Getters/Setters specifici Libro
        int getAnnoStampa() const;
        string getCasaEditrice() const;
        void setAnnoStampa(const int &updAnnoStampa);
        void setCasaEditrice(const string &updCasaEditrice);
        
        // Implementazione metodi virtuali
        string getMediaType() const override;
        std::vector<std::pair<string, string>> getSpecificDetails() const override;
        QJsonObject toJsonSpecific() const override;
        void fromJsonSpecific(const QJsonObject& json) override;
        Media* clone() const override;
};

#endif