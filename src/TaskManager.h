#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "Task.h"
#include <string>
#include <vector>

// Manages the list of tasks: add, complete, remove,
// plus saving/loading to a text file so data survives restarts.
class TaskManager {
public:
    // Load tasks from a file. Returns false if the file doesn't exist yet.
    bool load(const std::string& filename);

    // Save all tasks to a file (overwrites it).
    bool save(const std::string& filename) const;

    // Add a new task, returns the new task's id.
    int add(const std::string& title, int priority);

    // Mark a task as done by id. Returns false if not found.
    bool complete(int id);

    // Remove a task by id. Returns false if not found.
    bool remove(int id);

    // All tasks, sorted by priority then id.
    std::vector<Task> all() const;

private:
    std::vector<Task> tasks_;
    int nextId_ = 1;
};

#endif // TASKMANAGER_H
