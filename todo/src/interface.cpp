#include "interface.h"
#include "todo.h"
#include <iostream>
#include <string>
#include <vector>

interface::interface(todolist& todoList){
    help();
    while (true) {
        std::string cmd;
        std::vector<std::string> cmdList;

        std::cout << ">>>";

        std::getline(std::cin, cmd);
        cmdList = manageCmd(cmd);

        if(cmdList[0] == "q"){
            break;
        }
        else if (cmdList[0] == "c"){
            todoList.createTodo(cmdList[1], cmdList[2]);
        }

        else if (cmdList[0] == "r") {
            todoList.finshTodo(std::stoi(cmdList[1]));
        }
        else if(cmdList[0] == "l"){
            todoList.printList();
        }
        else if(cmdList[0] == "h"){
            help();
        }
        else {
            std::cout << std::endl;
            std::cout << "Error" << std::endl;
            std::cout << std::endl;
        }
        
    }
}

std::vector<std::string> interface::manageCmd(std::string cmd){
    std::string temp;
    std::vector<std::string> res;

    for (int i = 0; i < (cmd.size() + 1); i++){
        if (cmd[i] == ' ' || cmd[i] == '\0'){
            res.emplace_back(temp);
            temp.clear();
        }
        temp += cmd[i];
    }
    
    return res;
}

void interface::help() {
    std::cout << std::endl;
    std::cout << "TODO List Program" << std::endl;
    std::cout << "<q>: quit program." << std::endl;
    std::cout << "<c name description>: creat a todo" << std::endl;
    std::cout << "<r num> remove target todo" << std::endl;
    std::cout << "<l> print todo list." << std::endl;
    std::cout << "<h> print help." << std::endl;
    std::cout << std::endl;
}

interface::~interface(){
    std::cout << "Goodbye!" << std::endl;
}
