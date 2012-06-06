#ifndef K4X_ENGINE_H
#define K4X_ENGINE_H

#include <cstdint>
#include <tr1/memory>

#include <kglt/kglt.h>

#include "idle_task_manager.h"
#include "timed_task_manager.h"

namespace k4x {

enum PlayerMode {
    SINGLE_PLAYER,
    SINGLE_PLAYER_WITH_AI,
    TWO_PLAYER
};

class LevelManager;
class Chapter;
class ChapterManager;
class TitleChapter;

class Engine {
public:
    Engine(int argc, char* argv[]);
    int32_t run();

    TitleChapter& title(); ///< Shortcut function for chapter_manager().chapter("title");
    Chapter& save_selection(); ///< Shortcut function for chapter_manager().chapter("save_selection");

    ChapterManager& chapter_manager();
    LevelManager& level_manager();

    void set_player_mode(PlayerMode mode) {
        player_mode_ = mode;
    }

    PlayerMode player_mode() { return player_mode_; }

    IdleTaskManager& idle() { return idle_tasks_; }
    TimedTaskManager& timed() { return timed_tasks_; }

    kglt::Window& window() {
        assert(window_);
        return *window_;
    }

private:
    bool is_running_;

    std::tr1::shared_ptr<ChapterManager> chapter_manager_;
    std::tr1::shared_ptr<LevelManager> level_manager_;

    void run_idle_tasks();
    void run_timed_tasks();

    std::tr1::shared_ptr<kglt::Window> window_;

    PlayerMode player_mode_;

    IdleTaskManager idle_tasks_;
    TimedTaskManager timed_tasks_;
};

}

#endif
