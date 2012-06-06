#ifndef K4X_CHAPTER_H
#define K4X_CHAPTER_H

#include <cassert>

namespace k4x {

class ChapterManager;

class Chapter {
public:
    Chapter();
    virtual ~Chapter() {}

    void prepare_start(); ///< Called before previous chapter shuts down
    void start(); ///< Called when this chapter becomes active

    void frame_start();
    void frame_finish();

    void prepare_stop(); ///< Called when shutdown is initialized
    void stop(); ///< Called when this chapter actually becomes inactive

    void fade_to_black(float time_in_seconds, bool show_loading=false);
    void unfade();
    bool increase_fade_opacity(float amount);

    void set_manager(ChapterManager* manager);
    ChapterManager& manager() {
        assert(manager_);
        return *manager_;
    }
private:
    ChapterManager* manager_;

    float fade_to_black_opacity_;
    bool is_fading_to_black_;
    bool show_loading_when_black_;

    virtual void on_prepare_start() {}
    virtual void on_prepare_stop() {}

    virtual void on_frame_start() {}
    virtual void on_frame_finish() {}

    virtual void on_start() {}
    virtual void on_stop() {}
};

}

#endif // K4X_CHAPTER_H
