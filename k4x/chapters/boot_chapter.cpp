#include "boot_chapter.h"
#include "../chapter_manager.h"

namespace k4x {

BootChapter::BootChapter() {

}

void BootChapter::on_start() {
    fade_to_black(0, /*show_loading=true*/true);
    manager().switch_to_chapter("title");
}

}
