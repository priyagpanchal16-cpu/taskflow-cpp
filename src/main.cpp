#include "TaskManager.h"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>

const std::string DATA_FILE = "tasks.txt";

// Ask the user for a whole number, retrying until valid.
int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "  Please enter a number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Ask the user for a line of text, retrying until not empty.
std::string readLine(const std::string& prompt) {
    std::string text;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, text);
        if (!text.empty()) {
            return text;
        }
        std::cout << "  Please enter something.\n";
    }
}

void printTasks(const TaskManager& manager) {
    std::vector<Task> tasks = manager.all();
    if (tasks.empty()) {
        std::cout << "\n  No tasks yet. Add one with option 1!\n";
        return;
    }

    std::cout << "\n  ID  PRI  DONE  TITLE\n";
    std::cout << "  --  ---  ----  -----\n";
    for (const Task& task : tasks) {
        std::cout << "  " << task.id << "    " << task.priority << "    "
                  << (task.done ? "[x]  " : "[ ]  ") << task.title << "\n";
    }
    std::cout << "\n  " << tasks.size() << " task(s) total.\n";
}

int main() {
    TaskManager manager;
    manager.load(DATA_FILE);

    std::cout << "\n=== TaskFlow — simple task manager (C++) ===\n";

    while (true) {
        std::cout << "\n1. Add task\n"
                     "2. List tasks\n"
                     "3. Complete task\n"
                     "4. Delete task\n"
                     "5. Save and quit\n"
                     "> ";

        int choice;
        if (!(std::cin >> choice)) {
            break; // input closed — quit safely
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                std::string title = readLine("  Task title: ");
                int priority = readInt("  Priority (1 high, 2 medium, 3 low): ");
                if (priority < 1 || priority > 3) {
                    priority = 2; // invalid input falls back to medium
                }
                int id = manager.add(title, priority);
                std::cout << "  Added task #" << id << ".\n";
                break;
            }
            case 2:
                printTasks(manager);
                break;
            case 3: {
                int id = readInt("  Task id to complete: ");
                std::cout << (manager.complete(id)
                                  ? "  Nice, one done!\n"
                                  : "  No task with that id.\n");
                break;
            }
            case 4: {
                int id = readInt("  Task id to delete: ");
                std::cout << (manager.remove(id) ? "  Deleted.\n"
                                                 : "  No task with that id.\n");
                break;
            }
            case 5:
                manager.save(DATA_FILE);
                std::cout << "  Saved to " << DATA_FILE << ". Bye!\n";
                return 0;
            default:
                std::cout << "  Pick a number from 1 to 5.\n";
        }
    }

    manager.save(DATA_FILE); // save even on unexpected exit
    return 0;
}
