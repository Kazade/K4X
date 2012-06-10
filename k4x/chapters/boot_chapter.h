#ifndef BOOT_CHAPTER_H
#define BOOT_CHAPTER_H

#include "../chapter.h"

namespace k4x {

/**
  All the boot chapter does is display the loading screen, it just
  gives time for the next chapter to do any loading in the background while
  leaving the window responsive on first launch
*/

class BootChapter : public Chapter {
public:
    BootChapter();

private:
    void on_start();
};

}
#endif // BOOT_CHAPTER_H
