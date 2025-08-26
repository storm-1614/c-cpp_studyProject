#pragma once
#include "todo.h"
#include <string>
#include <vector>

class interface {
   private:
   public:
    std::vector<std::string> cmdList;

    interface(todolist& todoList);
    std::vector<std::string> manageCmd(std::string cmd);
    void help();
    ~interface();
};
