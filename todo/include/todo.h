#pragma once

#include <string>
#include <vector>

struct todo {
    std::string name;
    std::string description;
    bool status = false;
};

class todolist{
    private:
        
        std::vector<todo> list;
    public:
        void createTodo(std::string name, std::string dec);
        void finshTodo(int num);
        void printList();
};
