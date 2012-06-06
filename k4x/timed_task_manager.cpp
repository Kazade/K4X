#include <algorithm>
#include <functional>

#include "timed_task_manager.h"

namespace k4x {

static ConnectionID connection_counter = 0;

ConnectionID TimedTaskManager::add(std::tr1::function<bool ()> callback, uint32_t milliseconds) {
    TimedTask new_task;
    new_task.connection_id = ++connection_counter;
    new_task.callback = callback;
    new_task.time_elapsed_in_milliseconds = 0;
    new_task.time_between_calls = milliseconds;

    tasks_.push_back(new_task);

    return new_task.connection_id;
}

void TimedTaskManager::remove(ConnectionID connection) {
    tasks_.erase(
        std::remove_if(tasks_.begin(), tasks_.end(), [=](const TimedTask& task) { return task.connection_id == connection; }),
        tasks_.end()
    );
}

uint64_t TimedTaskManager::get_ticks() {
    struct timespec current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    return (uint64_t) ((current_time.tv_sec * 1000UL) + (current_time.tv_nsec / 1000000UL));
}

void TimedTaskManager::execute() {
    static uint64_t last_time = get_ticks();

    uint64_t current_time = get_ticks();
    uint64_t diff = current_time - last_time;

    std::vector<TimedTask> tasks = tasks_;

    /*
      Go through all the tasks, update the elapsed times. If the elapsed time
      is larger than the step, then execute the function and remove it if it
      returns false
    */
    uint32_t i = 0;
    for(TimedTask& task: tasks) {
        task.time_elapsed_in_milliseconds += diff;
        if(task.time_elapsed_in_milliseconds >= task.time_between_calls) {

            task.time_elapsed_in_milliseconds -= task.time_between_calls;

            if(!task.callback()) {
                tasks_.erase(tasks_.begin() + i);
            }
        }
        ++i;
    }

    last_time = current_time;
}


}
