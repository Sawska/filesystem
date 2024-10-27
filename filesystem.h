#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "directory.h"
#include <unordered_map>

class Filesystem {
    public:
    Filesystem();
    void createFile(const std::string& path, const std::string& filename);
    void createDirectory(const std::string& path, const std::string& dirname);
    void deleteFile(const std::string& path);
    void deleteDirectory(const std::string& path);
    void listDirectoryContents(const std::string& path);
    Directory* navigateTo(const std::string& path);
    void mount(const std::string& path,Directory* fs);
    void unmount(const std::string& path);
    void search(const std::string& name, const std::string& path);
    bool chmod(const std::string& path, int new_permissions);
    bool chown(const std::string& path, int new_owner_id);
    private:
    Directory* root;
    std::unordered_map<std::string,Directory*> mounts;
};

#endif //FILESYSTEM_H