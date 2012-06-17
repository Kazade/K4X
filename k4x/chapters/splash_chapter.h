#ifndef SPLASH_CHAPTER_H
#define SPLASH_CHAPTER_H

#include "chapter.h"

namespace k4x {

class SplashChapter : Chapter {
public:
    SplashChapter();

    static SplashChapter::ptr create() {
        return SplashChapter::ptr(new SplashChapter());
    }
};

}

#endif // SPLASH_CHAPTER_H
