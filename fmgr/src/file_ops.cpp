// fmgr/file_ops.cpp

#include "file_ops.h"
#include <filesystem>

namespace fs = std::filesystem;

std::vector<std::string> fmgr::list_directory(const std::string& path) {
    std::vector<std::string> files;
    for (const auto& entry : fs::directory_iterator(path)) {
        files.push_back(entry.path().filename().string());
    }
    return files;
}

bool fmgr::change_directory(const std::string &path){
    try {
        fs::current_path(path);
    
        return true;
    } catch (...) {
        return false;
    }
}

bool fmgr::copy_file(const std::string &src, const std::string &dest){
    try {
        std::filesystem::copy_file(src, dest);
        return true;
    } catch (...) {
        return false;
    }
}

bool fmgr::move_file(const std::string &src, const std::string &dest){
    try {
        fs::copy(src, dest);
        fs::remove(src);
        return true;
    } catch (...) {
        return false;
    }
}

bool fmgr::remove_file(const std::string &path){
    try {
        fs::remove(path);
        return true;
    } catch (...) {
        return false;
    }
}
