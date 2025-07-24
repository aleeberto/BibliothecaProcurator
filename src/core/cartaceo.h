#ifndef CARTACEO_HEADER
#define CARTACEO_HEADER

#include "media.h"
#include <QJsonObject>
using std::string;

class Cartaceo : public Media {
private:
    string scrittore;

public:
    Cartaceo(string titolo, int anno, string immagine, string scrittore);
    virtual ~Cartaceo() = default;

    string getScrittore() const;
    void setScrittore(const string &updScrittore);

    // JSON serialization
    virtual QJsonObject toJson() const override;
    static Cartaceo* fromJson(const QJsonObject& obj);
};

#endif
