#ifndef MANGA_HEADER
#define MANGA_HEADER
#include "cartaceo.h"
using std::string;

class Manga : public Cartaceo{
    private:
        string illustratore;
        int numLibri;
        bool concluso;
        
    public:
        Manga(string titolo, int anno, string immagine, string scrittore, string illustratore, int numLibri, bool concluso);
        virtual ~Manga() = default;

        // Getters/Setters specifici Manga
        string getIllustratore() const;
        int getNumLibri() const;
        bool getConcluso() const;
        void setIllustratore(const string &updIllustratore);
        void setNumLibri(const int &updNumLibri);
        void setConcluso(const bool &updConcluso);
        
        // Implementazione metodi virtuali
        QJsonObject toJsonSpecific() const override;
        void fromJsonSpecific(const QJsonObject& json) override;
        Media* clone() const override;
        
        // Visitor pattern
        void accept(MediaVisitor* visitor) override;
        
        // Polimorfismo per filtri
        bool matchesCategory(const string& category) const override;
};

#endif // MANGA_HEADER