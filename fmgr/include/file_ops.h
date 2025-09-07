// fmgr/include/file_ops.h

#pragma once
#include <filesystem>
#include <string>
#include <vector>

class fmgr {
   private:
    std::string p;  //path
   public:
    fmgr() {p = current_path();}
    std::string current_path(){return std::filesystem::current_path();};
   
    std::vector<std::string> list_directory(const std::string& path);
    bool change_directory(const std::string& path);
    bool copy_file(const std::string& src, const std::string& dest);
    bool move_file(const std::string& src, const std::string& dest);
    bool remove_file(const std::string& path);
};
