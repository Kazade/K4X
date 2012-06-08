#include "title_chapter.h"
#include "../engine.h"
#include "../chapter_manager.h"

namespace k4x {

TitleChapter::TitleChapter():
    background_sprite_id_(0) {

}

void TitleChapter::set_background_image(const std::string& background_image) {
    background_image_path_ = background_image;
}

void TitleChapter::on_prepare_start() {
    kglt::Window& window = manager().engine().window();
    kglt::Scene& scene = window.scene();

    if(!background_image_path_.empty()) {
        L_DEBUG("Loading background image from: " + background_image_path_);

        background_sprite_id_ = scene.new_sprite();
        kglt::Sprite& background = scene.sprite(background_sprite_id_);
        L_DEBUG("Loading...");

        window.loader_for(background_image_path_, "LOADER_HINT_SPRITE")->into(background, { "SPRITE_FRAME_WIDTH", "512" });
        background.set_render_dimensions(640, 480);
        background.move_to(0.0, 0.0, -1.0);
        background.set_animation_frames(0, 0);
        background.set_animation_fps(0);

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

void TitleChapter::on_frame_start() {
    kglt::Window& window = manager().engine().window();
    window.scene().pass().viewport().configure(kglt::VIEWPORT_TYPE_BLACKBAR_16_BY_9);
    window.scene().pass().renderer().set_orthographic_projection_from_height(224.0 * 4.0, 16.0 / 9.0);

    //FIXME: Need to set the backgorund render dimensions to the orthographic render dimensions

    /*
    kalt::System& system = manager().engine().sound();
    kalt::Track& track = system.track(title_music_);
    track.play();
    */
}

void TitleChapter::add_demo(const std::string &demo_video) {

}

}
