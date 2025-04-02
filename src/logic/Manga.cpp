#include "Manga.h"
using std::string;

Manga::Manga(string titolo, int anno, string immagine, string scrittore, string illustratore, int numLibri, bool concluso) :
    Libro(titolo, anno, immagine, scrittore), illustratore(illustratore), numLibri(numLibri), concluso(concluso) {}  // Correzione: chiusura corretta del costruttore

string Manga::getIllustratore() const {
    return illustratore;
}

int Manga::getNumLibri() const {
    return numLibri;
}

bool Manga::getConcluso() const {
    return concluso;
}

void Manga::setIllustratore(const string &updIllustratore) {
    illustratore = updIllustratore;
}

void Manga::setNumLibri(const int &updNumLibri) {
    numLibri = updNumLibri;
}

void Manga::setConcluso(const bool &updConcluso) {
    concluso = updConcluso;
}