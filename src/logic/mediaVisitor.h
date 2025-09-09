#ifndef MEDIAVISITOR_HEADER
#define MEDIAVISITOR_HEADER

// Forward declarations
class Film;
class SerieTv;
class Anime;
class Libro;
class Manga;
class Cd;

class MediaVisitor {
public:
    virtual ~MediaVisitor() = default;
    
    virtual void visit(Film* film) = 0;
    virtual void visit(SerieTv* serieTv) = 0;
    virtual void visit(Anime* anime) = 0;
    virtual void visit(Libro* libro) = 0;
    virtual void visit(Manga* manga) = 0;
    virtual void visit(Cd* cd) = 0;
};

#endif // MEDIAVISITOR_HEADER