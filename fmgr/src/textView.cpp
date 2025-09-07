#include "textView.h"
#include <iostream>
#include <stdexcept>

textView::textView(const std::string& path):
    file(path)

{
    if (!file.is_open()){
        throw std::runtime_error("Error");
    }
};

void textView::view(){
    std::string text;
        std::cout << text << std::endl;
        while(getline(file, text)){
    }
}

