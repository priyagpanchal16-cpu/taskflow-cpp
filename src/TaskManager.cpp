#include "TaskManager.h"
#include <algorithm>
#include <fstream>
#include <iostream>

bool TaskManager::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false; // no saved file yet — start with an empty list
    }

    tasks_.clear();
    Task t;
    while (file >> t.id >> t.priority >> t.done) {
        file.ignore(); // skip the space after the "done" field
        std::getline(file, t.title);
        tasks_.push_back(t);
    }

    // Make sure the next id doesn't clash with loaded tasks.
    nextId_ = 1;
    for (const Task& task : tasks_) {
        nextId_ = std::max(nextId_, task.id + 1);
    }
    return true;
}

bool TaskManager::save(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    for (const Task& task : tasks_) {
        // One task per line: id priority done title
        file << task.id << ' ' << task.priority << ' '
             << (task.done ? 1 : 0) << ' ' << task.title << '\n';
    }
    return true;
}

int TaskManager::add(const std::string& title, int priority) {
    Task t{nextId_++, title, priority, false};
    tasks_.push_back(t);
    return t.id;
}

bool TaskManager::complete(int id) {
    for (Task& task : tasks_) {
        if (task.id == id) {
            task.done = true;
            return true;
        }
    }
    return false;
}

bool TaskManager::remove(int id) {
    for (size_t i = 0; i < tasks_.size(); i++) {
        if (tasks_[i].id == id) {
            tasks_.erase(tasks_.begin() + i);
            return true;
        }
    }
    return false;
}

std::vector<Task> TaskManager::all() const {
    std::vector<Task> sorted = tasks_;
    std::sort(sorted.begin(), sorted.end(), [](const Task& a, const Task& b) {
        if (a.priority != b.priority) {
            return a.priority < b.priority; // high priority first
        }
        return a.id < b.id; // then oldest first
    });
    return sorted;
}
