#include <utility>

#include "idle_task_manager.h"

namespace k4x {

static uint32_t connection_counter = 0;

IdleTaskManager::IdleTaskManager() {

}

ConnectionID IdleTaskManager::add(std::tr1::function<bool ()> callback) {
    ConnectionID new_id = ++connection_counter;
    signals_.insert(std::make_pair(new_id, callback));
    return new_id;
}

void IdleTaskManager::execute() {
    /*for(std::pair<ConnectionID, std::tr1::function<bool> > p: signals_.copy()) {
        bool result = p.second();
        if(!result) {
            signals_.erase(p.first);
        }
    }*/
}

}
