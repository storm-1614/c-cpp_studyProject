// /include/textView.h

#pragma once
#include <filesystem>
#include <fstream>
#include <string>

class textView{
    private:
        std::fstream file;
        

    public:
        textView(const std::string& path);
        void view();
};

