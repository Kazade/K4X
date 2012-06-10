#include "title_chapter.h"
#include "../engine.h"
#include "../chapter_manager.h"

namespace k4x {

TitleChapter::TitleChapter() {

}

void TitleChapter::set_background_image(const std::string& background_image) {
    background_image_path_ = background_image;
}

void TitleChapter::on_prepare_start() {
    kglt::Window& window = manager().engine().window();
    kglt::Scene& scene = window.scene();

    if(!background_image_path_.empty()) {
        L_DEBUG("Loading background image from: " + background_image_path_);
        scene.background().add_layer(background_image_path_);
        L_DEBUG("Background loaded");
    }

    /*
    if(!title_music_path_.empty()) {
        kalt::System& system = manager().engine().sound();
        title_music_ = system.new_track();
        kalt::Track& track = system.track(title_music);
        system.loader_for(title_music_path_)->into(track);
    }*/
}

void TitleChapter::on_start() {
    kglt::Window& window = manager().engine().window();
    window.scene().pass().viewport().configure(kglt::VIEWPORT_TYPE_BLACKBAR_16_BY_9);

    double height = 224.0 * 4.0;
    double width = window.scene().pass().renderer().set_orthographic_projection_from_height(height, 16.0 / 9.0);

    /*
    kalt::System& system = manager().engine().sound();
    kalt::Track& track = system.track(title_music_);
    track.play();
    */

    unfade();    

    scroll_connection_ = manager().engine().idle().add(sigc::mem_fun(this, &TitleChapter::scroll_background));
}

void TitleChapter::on_stop() {
    manager().engine().idle().remove(scroll_connection_);
}

bool TitleChapter::scroll_background() {
    kglt::Window& window = manager().engine().window();
    window.scene().background().layer(0).scroll_x(0.1 * window.delta_time());
    return true;
}

void TitleChapter::add_demo(const std::string &demo_video) {

}

}
