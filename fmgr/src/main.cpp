#include <iostream>
#include <stdexcept>
#include <string>

#include "file_ops.h"
#include "textView.h"

void printHelp() {
    std::cout << "FMGR 文件管理器命令: \n"
              << "ls   列出当前目录内容" << std::endl;
    // TODO: 完善一切
}

int main(int argc, char* argv[]) {
    try {
        fmgr f;
        std::string command = " ";
        std::cout << f.current_path() << std::endl;
        while (!command.empty()) {
            printHelp();
            std::cout << "输入命令: ";
            std::cin >> command;
            if (command == "ls") {
                f.list_directory(f.current_path());
            } else if (command == "quit") {
                return 0;
            }
        }
    }

    catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
