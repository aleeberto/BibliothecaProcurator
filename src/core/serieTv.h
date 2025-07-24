#ifndef SERIETV_HEADER
#define SERIETV_HEADER

#include "series.h"
#include <QJsonObject>
using std::string;

class SerieTv : public Series {
private:
    string ideatore;
    string casaProduttrice;

public:
    SerieTv(string titolo, int anno, string immagine, int numEpisodi, int numStagioni, int durataMediaEp, bool inCorso, 
            string ideatore, string casaProduttrice);
    virtual ~SerieTv() = default;

    string getIdeatore() const;
    string getCasaProduttrice() const;

    void setIdeatore(const string &updIdeatore);
    void setCasaProduttrice(const string &updCasaProduttrice);

    // JSON serialization
    virtual QJsonObject toJson() const override;
    static SerieTv* fromJson(const QJsonObject& obj);
};

#endif
