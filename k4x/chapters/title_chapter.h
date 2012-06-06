#ifndef TITLE_CHAPTER_H
#define TITLE_CHAPTER_H

#include "../chapter.h"

namespace k4x {

class TitleChapter : public Chapter {
public:
    typedef std::tr1::shared_ptr<TitleChapter> ptr;

    static TitleChapter::ptr create() {
        return TitleChapter::ptr(new TitleChapter());
    }
};

}

#endif // TITLE_CHAPTER_H
