#ifndef TITLE_CHAPTER_H
#define TITLE_CHAPTER_H

#include <tr1/memory>
#include <string>

#include <kglt/kglt.h>

#include "../idle_task_manager.h"
#include "../chapter.h"

namespace k4x {

class TitleChapter : public Chapter {
public:
    typedef std::tr1::shared_ptr<TitleChapter> ptr;

    TitleChapter();

    static TitleChapter::ptr create() {
        return TitleChapter::ptr(new TitleChapter());
    }

    void add_demo(const std::string& demo_video);
    void set_background_image(const std::string& background_image);

    void enable_background_scrolling(bool value=true);

    bool scroll_background();
private:
    std::string background_image_path_;
    std::vector<std::string> demo_videos_;

    void on_prepare_start();
    void on_start();
    void on_stop();

    ConnectionID scroll_connection_;

    bool background_scrolling_enabled_;
};

}

#endif // TITLE_CHAPTER_H
