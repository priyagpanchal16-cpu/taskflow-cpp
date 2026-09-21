#ifndef TASK_H
#define TASK_H

#include <string>

// A single task in the list.
struct Task {
    int id;                 // unique id, assigned by TaskManager
    std::string title;      // what needs to be done
    int priority;           // 1 = high, 2 = medium, 3 = low
    bool done;              // completed or not
};

#endif // TASK_H
