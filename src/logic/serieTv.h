#ifndef SERIETV_HEADER
#define SERIETV_HEADER
#include "series.h"
using std::string;

class SerieTv : public Series{
    private:
        string ideatore;
        string casaProduttrice;

    public:
        SerieTv(string titolo, int anno, string immagine, int numEpisodi, int numStagioni, int durataMediaEp, bool inCorso, 
            string ideatore, string casaProduttrice);
        virtual ~SerieTv() = default;
    
        // Getters/Setters specifici di SerieTv
        string getIdeatore() const;
        string getCasaProduttrice() const;
        void setIdeatore(const string &updIdeatore);
        void setCasaProduttrice(const string &updCasaProduttrice);
        
        // Implementazione metodi virtuali
        string getMediaType() const override;
        std::vector<std::pair<string, string>> getSpecificDetails() const override;
        QJsonObject toJsonSpecific() const override;
        void fromJsonSpecific(const QJsonObject& json) override;
        Media* clone() const override;
};

#endif