#include "title_chapter.h"
#include "../engine.h"
#include "../chapter_manager.h"

#include "kglt/ui/shortcuts.h"
#include "kglt/kazbase/logging/logging.h"

namespace k4x {

TitleChapter::TitleChapter():
    scroll_connection_(0) {

}

void TitleChapter::add_sprite(const std::string& sprite_image, SpritePosition position) {
    kglt::Window& window = manager().engine().window();
    kglt::SpriteID sprite_id = window.scene().new_sprite();
    kglt::Sprite& sprite = window.scene().sprite(sprite_id);
    window.loader_for(sprite_image, "LOADER_HINT_SPRITE")->into(sprite);

    sprite.move_to(0, 0, -1.0);
    sprite.set_animation_frames(0, 0);
    sprite.set_animation_fps(0);
    sprite.set_render_dimensions(256*4, 256*4);

    switch(position) {
        case SPRITE_POSITION_CENTRED:
        break;
    }
}

void TitleChapter::add_background_image(const std::string& background_image) {
    L_DEBUG("Loading background image from: " + background_image);
    kglt::Scene& scene = manager().engine().window().scene();
    scene.background().add_layer(background_image);
    L_DEBUG("Background loaded");
}

void TitleChapter::enable_background_scrolling(bool value) {
    //if(background_image_path_.empty()) return;

    background_scrolling_enabled_ = value;
    if(!value && scroll_connection_) {
        manager().engine().idle().remove(scroll_connection_);
        scroll_connection_ = 0;
    }
    if(value && !scroll_connection_) {
        scroll_connection_ = manager().engine().idle().add(sigc::mem_fun(this, &TitleChapter::scroll_background));
    }
}

void TitleChapter::on_prepare_start() {
    kglt::Window& window = manager().engine().window();
    kglt::Scene& scene = window.scene();

    kglt::ui::Label& label = kglt::ui::return_new_label(scene);
    label.set_position(0.75, 0.025);
    label.background().set_visible(false);
    label.border().set_visible(false);
    label.set_text(u8"\u00a9 SEGA 1991");

    /*            
    if(!title_music_path_.empty()) {
        kalt::System& system = manager().engine().sound();
        title_music_ = system.new_track();
        kalt::Track& track = system.track(title_music);
        system.loader_for(title_music_path_)->into(track);
    }*/
}

void TitleChapter::on_start() {
    L_DEBUG("Starting title chapter");

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
    enable_background_scrolling();
}

void TitleChapter::on_stop() {
    if(scroll_connection_) {
        manager().engine().idle().remove(scroll_connection_);
    }
}

bool TitleChapter::scroll_background() {
    kglt::Window& window = manager().engine().window();

    if(!window.scene().background().layer_count()) {
        return false;
    }

    window.scene().background().layer(0).scroll_x(0.05 * window.delta_time());
    window.scene().background().layer(1).scroll_x(0.06 * window.delta_time());
    window.scene().background().layer(2).scroll_x(0.07 * window.delta_time());
    return true;
}

void TitleChapter::add_demo(const std::string &demo_video) {

}

}
