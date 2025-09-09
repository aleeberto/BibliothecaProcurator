#ifndef CARTACEO_HEADER
#define CARTACEO_HEADER
#include "media.h"
using std::string;

class Cartaceo : public Media{
    private:
        string scrittore;

    public:
        Cartaceo(string titolo, int anno, string immagine, string scrittore);
        virtual ~Cartaceo() = default;

        // Getters/Setters comuni ai cartacei
        string getScrittore() const;
        void setScrittore(const string &updScrittore);
        
    protected:
        // Metodi helper per le classi derivate
        QJsonObject getCartaceoBaseJson() const;
        void setCartaceoBaseFromJson(const QJsonObject& json);
};

#endif // CARTACEO_HEADER