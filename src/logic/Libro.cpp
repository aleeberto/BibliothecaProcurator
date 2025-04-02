#include "Libro.h"
using std::string;

Libro::Libro(string titolo, int anno, string immagine, string scrittore) 
    : Media(titolo, anno, immagine), scrittore(scrittore){}

string Libro::getScrittore()const{
    return scrittore;
}


void Libro::setScrittore(const string &updScrittore){
    scrittore = updScrittore;
}