#include "serieTv.h"
#include <QJsonObject>

SerieTv::SerieTv(string titolo, int anno, string immagine, int numEpisodi, int numStagioni, int durataMediaEp, bool inCorso, string ideatore, string casaProduttrice)
    : Media(titolo, anno, immagine), numEpisodi(numEpisodi), numStagioni(numStagioni), durataMediaEp(durataMediaEp), inCorso(inCorso), ideatore(ideatore), casaProduttrice(casaProduttrice) {}

int SerieTv::getNumEpisodi() const { return numEpisodi; }
int SerieTv::getNumStagioni() const { return numStagioni; }
int SerieTv::getDurataMediaEp() const { return durataMediaEp; }
bool SerieTv::getInCorso() const { return inCorso; }
string SerieTv::getIdeatore() const { return ideatore; }
string SerieTv::getCasaProduttrice() const { return casaProduttrice; }

void SerieTv::setNumEpisodi(const int &updNumEpisodi) { numEpisodi = updNumEpisodi; }
void SerieTv::setNumStagioni(const int &updNumStagioni) { numStagioni = updNumStagioni; }
void SerieTv::setDurataMediaEp(const int &updDurataMediaEp) { durataMediaEp = updDurataMediaEp; }
void SerieTv::setInCorso(const bool &updInCorso) { inCorso = updInCorso; }
void SerieTv::setIdeatore(const string &updIdeatore) { ideatore = updIdeatore; }
void SerieTv::setCasaProduttrice(const string &updCasaProduttrice) { casaProduttrice = updCasaProduttrice; }

QString SerieTv::getDetails() const {
    return QString("Serie TV: %1 (%2) - %3 episodes, %4 seasons, %5 min per episode")
           .arg(QString::fromStdString(getTitolo()))
           .arg(getAnno())
           .arg(getNumEpisodi())
           .arg(getNumStagioni())
           .arg(getDurataMediaEp());
}

QString SerieTv::getTypeName() const {
    return "Serie Tv";
}

QString SerieTv::getShortDescription() const {
    return QString("%1 (%2) - %3 episodes, %4 seasons")
           .arg(QString::fromStdString(getTitolo()))
           .arg(getAnno())
           .arg(getNumEpisodi())
           .arg(getNumStagioni());
}

bool SerieTv::matchesSearch(const QString& searchTerm) const {
    QString title = QString::fromStdString(getTitolo()).toLower();
    QString ideatore = QString::fromStdString(getIdeatore()).toLower();
    return title.contains(searchTerm.toLower()) || ideatore.contains(searchTerm.toLower());
}

QJsonObject SerieTv::getDetails() const {
    return QString("Serie Tv: %1 (%2<thinking>
The attempt to create or edit the file src/logic/film.cpp failed due to an editor error. To proceed, I will try a safer approach by reading the existing src/logic/film.cpp file content first, then prepare a precise edit patch to add the polymorphic virtual methods implementations. This approach avoids overwriting the entire file blindly and reduces the risk of editor errors.

I will read the current src/logic/film.cpp file content now.
</thinking>

<read_file>
<path>src/logic/film.cpp</path>
</read_file>
