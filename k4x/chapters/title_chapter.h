#ifndef TITLE_CHAPTER_H
#define TITLE_CHAPTER_H

#include <tr1/memory>
#include <string>

#include <kglt/kglt.h>

#include "../idle_task_manager.h"
#include "../chapter.h"

namespace k4x {

enum SpritePosition {
    SPRITE_POSITION_CENTRED
};

class TitleChapter : public Chapter {
public:
    typedef std::tr1::shared_ptr<TitleChapter> ptr;

    TitleChapter();

    static TitleChapter::ptr create() {
        return TitleChapter::ptr(new TitleChapter());
    }

    void add_demo(const std::string& demo_video);
    void add_background_image(const std::string& background_image);
    void add_sprite(const std::string& sprite, SpritePosition position);

    void enable_background_scrolling(bool value=true);

    bool scroll_background();
private:
    std::string background_image_path_;
    std::vector<std::string> demo_videos_;
    std::vector<kglt::SpriteID> sprites_;

    void on_prepare_start();
    void on_start();
    void on_stop();

    ConnectionID scroll_connection_;

    bool background_scrolling_enabled_;
};

}

#endif // TITLE_CHAPTER_H
