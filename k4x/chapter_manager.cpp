#include <future>
#include <thread>
#include <sigc++/sigc++.h>

#include "kglt/kazbase/logging/logging.h"
#include "chapter.h"
#include "chapter_manager.h"
#include "engine.h"

#include "chapters/boot_chapter.h"

namespace k4x {

ChapterManager::ChapterManager(Engine& engine):
    engine_(engine) {

    register_chapter("boot", std::tr1::shared_ptr<Chapter>(new BootChapter()));
}

void ChapterManager::register_chapter(const std::string& name, std::tr1::shared_ptr<Chapter> chapter) {
    assert(chapters_.find(name) == chapters_.end());

    chapter->set_manager(this);

    chapters_[name] = chapter;
    if(current_chapter_name_.empty()) {
        current_chapter_name_ = name;
    }
}

Chapter& ChapterManager::chapter(const std::string& name) {
    assert(chapters_.find(name) != chapters_.end());
    return *chapters_[name];
}

void ChapterManager::switch_to_chapter(const std::string& name) {
    L_DEBUG("Switching to chapter: " + name);
    Chapter& next = chapter(name);
    Chapter& current = current_chapter();

    //Start threads for shutting down this chapter, and booting up the next one

    prepare_start_future_ = std::async(std::launch::async, sigc::mem_fun(&next, &Chapter::prepare_start));
    prepare_stop_future_ = std::async(std::launch::async, sigc::mem_fun(&current, &Chapter::prepare_stop));

    //Wait for the threads to complete before switching
    engine().idle().add(sigc::bind(sigc::mem_fun(this, &ChapterManager::switch_when_ready), name));

    //Fade the existing chapter to black while it shuts down and while the next one loads
    //Show the loading icon if we get to full black and we haven't finished loading the next scene
    current.fade_to_black(1.0, /*show_loading=*/true);
}

bool ChapterManager::switch_when_ready(const std::string& next) {
    if(prepare_start_future_.valid() && prepare_stop_future_.valid()) {
        L_DEBUG("Prepare threads finished, switching to chapter now: " + next);

        prepare_start_future_.get();
        prepare_stop_future_.get(); //Apparently we should call this anyway, so exceptions can be propagated..

        current_chapter().stop();
        current_chapter_name_ = next; //Move to the next chapter
        current_chapter().start();

        return false;
    }

    return true;
}

}
