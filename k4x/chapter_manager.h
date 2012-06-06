#ifndef K4X_CHAPTER_MANAGER_H
#define K4X_CHAPTER_MANAGER_H

#include <cassert>
#include <future>
#include <string>
#include <tr1/memory>
#include <map>

namespace k4x {

class Engine;
class Chapter;

class ChapterManager {
public:
    ChapterManager(Engine& engine);

    void register_chapter(const std::string& name, std::tr1::shared_ptr<Chapter> chapter);
    void restart_chapter();
    void switch_to_chapter(const std::string& name);

    Chapter& chapter(const std::string& name);
    Engine& engine() { return engine_; }

    Chapter& current_chapter() {
        assert(!current_chapter_name_.empty());
        return chapter(current_chapter_name_);
    }

    bool switch_when_ready(const std::string& next);

private:
    Engine& engine_;
    std::string current_chapter_name_;

    std::map<std::string, std::tr1::shared_ptr<Chapter> > chapters_;

    std::future<void> prepare_start_future_;
    std::future<void> prepare_stop_future_;
};

}

#endif
