#ifndef SERIETV_HEADER
#define SERIETV_HEADER
#include "series.h"
#include <QString>
#include <QJsonObject>
using std::string;

class SerieTv : public Series {
private:
    string ideatore;
    string casaProduttrice;

public:
    SerieTv(string titolo, int anno, string immagine, int numEpisodi, int numStagioni, int durataMediaEp, bool inCorso, string ideatore, string casaProduttrice);
    
    string getIdeatore() const;
    string getCasaProduttrice() const;

    void setIdeatore(const string &updIdeatore);
    void setCasaProduttrice(const string &updCasaProduttrice);

    QString getDetails() const override;
    QString getTypeName() const override;
    QString getShortDescription() const override;
    bool matchesSearch(const QString& searchTerm) const override;
    QJsonObject toJson() const override;
};

#endif
