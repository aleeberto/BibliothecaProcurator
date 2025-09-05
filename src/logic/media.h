#ifndef MEDIA_HEADER
#define MEDIA_HEADER
#include <string>
#include <vector>
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

        // Getters/Setters comuni
        string getTitolo() const;
        int getAnno() const;
        string getImmagine() const;
        void setTitolo(const string &updTitolo);
        void setImmagine(const string &updImmagine);
        void setAnno(const int &updAnno);
        
        // Metodi virtuali
        virtual string getMediaType() const = 0;
        virtual std::vector<std::pair<string, string>> getSpecificDetails() const = 0;
        virtual QJsonObject toJsonSpecific() const = 0;
        virtual void fromJsonSpecific(const QJsonObject& json) = 0;
        
        // Metodo clone polimorfismo
        virtual Media* clone() const = 0;
};

#endif