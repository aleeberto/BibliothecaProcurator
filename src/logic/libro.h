#ifndef LIBRI_HEADER
#define LIBRI_HEADER
#include "media.h"
using std::string;

class Libro : public Media{
    private:
        string scrittore;
    
    public:
        Libro(string titolo, int anno, string immagine, string scrittore);
        virtual ~Libro() = default;

        string getScrittore() const;

        void setScrittore(const string &updScrittore);
};

#endif