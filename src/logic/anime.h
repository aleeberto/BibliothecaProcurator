#ifndef ANIME_HEADER
#define ANIME_HEADER
#include "series.h"
using std::string;

class Anime : public Series{
    private:
        string disegnatore;
        string studioAnimazione;

    public:
        Anime(string titolo, int anno, string immagine, int numEpisodi, int numStagioni, int durataMediaEp, bool inCorso, string disegnatore, string studioAnimazione);
        virtual ~Anime() = default;
    
        // Getters/Setters specifici Anime
        string getDisegnatore() const;
        string getStudioAnimazione() const;
        void setDisegnatore(const string &updDisegnatore);
        void setStudioAnimazione(const string &updStudioAnimazione);
        
        // Implementazione metodi virtuali
        string getMediaType() const override;
        std::vector<std::pair<string, string>> getSpecificDetails() const override;
        QJsonObject toJsonSpecific() const override;
        void fromJsonSpecific(const QJsonObject& json) override;
        Media* clone() const override;
};

#endif