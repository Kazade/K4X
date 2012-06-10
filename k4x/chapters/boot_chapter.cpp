#include "boot_chapter.h"
#include "../chapter_manager.h"

#include "kglt/kazbase/logging/logging.h"

namespace k4x {

BootChapter::BootChapter() {

}

void BootChapter::on_start() {
    L_DEBUG("Starting boot chapter");

    fade_to_black(0, /*show_loading=true*/true);
    manager().switch_to_chapter("title");
}

}
