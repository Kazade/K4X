
#include "engine.h"
#include "chapter_manager.h"
#include "level_manager.h"
#include "chapters/title_chapter.h"

#include "kglt/kazbase/logging/logging.h"

namespace k4x {

Engine::Engine(int argc, char* argv[]):
    is_running_(true),
    chapter_manager_(new ChapterManager(*this)),
    level_manager_(new LevelManager()) {

    logging::get_logger("/")->add_handler(logging::Handler::ptr(new logging::StdIOHandler));

    window_.reset(new kglt::Window());

    //Register the essential chapters
    chapter_manager().register_chapter("title", k4x::TitleChapter::create());
    //chapter_manager().register_chapter("save_selection", k4x::SaveSelectionChapter::create());
    //chapter_manager().register_chapter("in_game", k4x::InGameChapter::create());

    chapter_manager().switch_to_chapter("boot");
}

int32_t Engine::run() {
    is_running_ = true;

    while(is_running_) {
        chapter_manager().current_chapter().frame_start();
        is_running_ = window().update();
        chapter_manager().current_chapter().frame_finish();

        idle().execute();
        timed().execute();
    }

    return 0;
}

ChapterManager& Engine::chapter_manager() {
    assert(chapter_manager_);
    return *chapter_manager_;
}

LevelManager& Engine::level_manager() {
    assert(level_manager_);
    return *level_manager_;
}

TitleChapter& Engine::title() {
    return dynamic_cast<TitleChapter&>(chapter_manager().chapter("title"));
}

}
