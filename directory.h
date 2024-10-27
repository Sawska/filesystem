#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include <vector>
#include <sstream>
#include <memory>  
#include "file.h"
#include "Link.h"

class Directory {
private:
    std::string name;
    std::vector<File> files;
    std::vector<std::shared_ptr<Directory>> subdirectories;  

public:
    Directory(const std::string& name);

    bool add_file(const File& file);
    bool remove_file(const std::string& filename);
    File* get_file(const std::string& filename);

    bool add_subdirectory(const std::string& dirname);
    bool remove_subdirectory(const std::string& dirname);
    Directory* get_subdirectory(const std::string& dirname);

    void list_contents() const;
    std::string get_name() const;
    std::vector<File>& get_files();
    std::vector<std::shared_ptr<Directory>>& get_subdirectories();  
     bool create_link(const std::string& link_name, Link::LinkType link_type, File* target_file = nullptr, const std::string& target_path = "");
    void chmod(int new_permissions);
    void chown(int new_owner_id);
    File* resolve_symbolic_link(const Link& link);
};

#endif // DIRECTORY_H
