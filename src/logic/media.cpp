#include "media.h"
#include <algorithm>
#include <cctype>
using std::string;

Media::Media(string titolo, int anno, string immagine): titolo(titolo), anno(anno), immagine(immagine){}

string Media::getTitolo() const{
    return titolo;
}

int Media::getAnno() const{
    return anno;
}

string Media::getImmagine() const{
    return immagine;
}

void Media::setTitolo(const string &updTitolo){
    titolo = updTitolo;
}

void Media::setAnno(const int &updAnno){
    anno = updAnno;
}

void Media::setImmagine(const string &updImmagine){
    immagine = updImmagine;
}

bool Media::matchesSearch(const string& searchText) const {
    if (searchText.empty()) return true;
    
    string lowerTitle = titolo;
    string lowerSearch = searchText;
    
    // convert both strings to lowercase for case-insensitive comparison
    std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);
    std::transform(lowerSearch.begin(), lowerSearch.end(), lowerSearch.begin(), ::tolower);
    
    return lowerTitle.find(lowerSearch) != string::npos;
}