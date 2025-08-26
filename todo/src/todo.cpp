#include "todo.h"
#include <string>
#include <iostream>

void todolist::createTodo(std::string name, std::string dec) {
    todo temp;
    temp.name = name;
    temp.description = dec;

    list.emplace_back(temp);
}

void todolist::printList() {
    if (!list.empty()) {
        for (int i = 0; i < list.size() ; i++) {
            std::string finish = list[i].status ? "Finished" : "Unfinished";

            std::cout << i << " => " << list[i].name << std::endl;
            std::cout << "Descriptionion: " << list[i].description << std::endl;
            std::cout << "Status: "<< finish << std::endl;
            std::cout << "===============" << std::endl; 
        }
    }
    else{
        std::cout << "None" << std::endl;
    }
}

void todolist::finshTodo(int num){
    if (num < list.size()) {
        list[num].status = true;
    }
}
