#include "chapter.h"
#include "engine.h"
#include "chapter_manager.h"

namespace k4x {

Chapter::Chapter():
    manager_(nullptr) {

}

void Chapter::frame_start() {
    on_frame_start();
}

void Chapter::frame_finish() {
    on_frame_finish();
}

void Chapter::start() {
    on_start();
}

void Chapter::stop() {
    on_stop();
}

void Chapter::prepare_start() {
    on_prepare_start();
}

void Chapter::prepare_stop() {
    on_prepare_stop();
}

void Chapter::set_manager(ChapterManager* manager) {
    manager_ = manager;
}

void Chapter::fade_to_black(float time_in_seconds, bool show_loading) {
    this->fade_to_black_opacity_ = 0.0;
    this->is_fading_to_black_ = true;
    this->show_loading_when_black_ = true;

    //Add a regular timed update every 100 milliseconds (FULL_OPACITY / TIME / 10)
    manager().engine().timed().add(
        sigc::bind(
            sigc::mem_fun(this, &Chapter::increase_fade_opacity),
            1.0 / time_in_seconds / 10.0
        ),
        100
    );
}

bool Chapter::increase_fade_opacity(float amount) {
    this->fade_to_black_opacity_ += amount;
    if(this->fade_to_black_opacity_ >= 1.0) {
        if(show_loading_when_black_) {
            //display_loading_icon();
        }

        this->is_fading_to_black_ = false;
        //Stop the regular update
        return false;
    }

    //Continue the regular update
    return true;
}

void Chapter::unfade() {
    this->fade_to_black_opacity_ = 0.0;
}

}
