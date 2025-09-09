#ifndef CD_HEADER
#define CD_HEADER
#include "media.h"
using std::string;

class Cd : public Media{
    private:
        string artista;
        int numTracce;
        int durataMedTracce;
    
    public:
        Cd(string titolo, int anno, string immagine, string artista, int numTracce, int durataMedTracce);
        virtual ~Cd() = default;

        // Getters/Setters specifici Cd
        string getArtista() const;
        int getNumTracce() const;
        int getDurataMedTracce() const;
        void setArtista(const string &updArtista);
        void setNumTracce(const int &updNumTracce);
        void setDurataMedTracce(const int &updDurataMedTracce);
        
        // Implementazione metodi virtuali
        QJsonObject toJsonSpecific() const override;
        void fromJsonSpecific(const QJsonObject& json) override;
        Media* clone() const override;
        
        // Visitor pattern
        void accept(MediaVisitor* visitor) override;
        
        // Polimorfismo per filtri
        bool matchesCategory(const string& category) const override;
};

#endif // CD_HEADER