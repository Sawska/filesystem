#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include <vector>
#include <memory>  
#include "file.h"

class Directory {
private:
    std::string name;
    std::vector<File> files;  // List of files in the directory
    std::vector<std::shared_ptr<Directory>> subdirectories;  // List of subdirectories

public:
    Directory(const std::string& name);

    bool add_file(const File& file);
    bool remove_file(const std::string& filename);
    File* get_file(const std::string& filename);

    bool add_subdirectory(const std::string& dirname);
    bool remove_subdirectory(const std::string& dirname);
    Directory* get_subdirectory(const std::string& dirname);

    void list_contents() const;  // Lists files and subdirectories
    std::string get_name() const;  // Accessor for directory name
    std::vector<File>& get_files();  // Accessor for the list of files
    std::vector<std::shared_ptr<Directory>>& get_subdirectories();  // Accessor for subdirectories
};

#endif // DIRECTORY_H
