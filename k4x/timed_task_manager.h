#ifndef TIMED_TASK_MANAGER_H
#define TIMED_TASK_MANAGER_H

#include <vector>
#include <tr1/functional>
#include <cstdint>

namespace k4x {

typedef uint32_t ConnectionID;

struct TimedTask {
    ConnectionID connection_id;
    uint32_t time_elapsed_in_milliseconds;
    uint32_t time_between_calls;
    std::tr1::function<bool ()> callback;
};

class TimedTaskManager {
public:
    ConnectionID add(std::tr1::function<bool ()>, uint32_t milliseconds);
    void remove(ConnectionID connection);

    void execute();

private:
    std::vector<TimedTask> tasks_;

    uint64_t get_ticks();
};


}

#endif // TIMED_TASK_MANAGER_H
