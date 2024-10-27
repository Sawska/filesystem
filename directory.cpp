#include "directory.h"
#include <iostream>
#include <algorithm>


Directory::Directory(const std::string& name) : name(name) {}


bool Directory::add_file(const File& file) {
    for (const auto& existing_file : files) {
        if (existing_file.get_name() == file.get_name()) {
            std::cerr << "File already exists: " << file.get_name() << std::endl;
            return false;
        }
    }
    files.push_back(file);
    std::cout << "File added: " << file.get_name() << std::endl;
    return true;
}


bool Directory::remove_file(const std::string& filename) {
    auto it = std::find_if(files.begin(), files.end(), [&filename](const File& file) {
        return file.get_name() == filename;
    });

    if (it != files.end()) {
        files.erase(it);
        std::cout << "File removed: " << filename << std::endl;
        return true;
    } else {
        std::cerr << "File not found: " << filename << std::endl;
        return false;
    }
}


File* Directory::get_file(const std::string& filename) {
    for (auto& file : files) {
        if (file.get_name() == filename) {
            return &file;
        }
    }
    std::cerr << "File not found: " << filename << std::endl;
    return nullptr;
}


bool Directory::add_subdirectory(const std::string& dirname) {
    for (const auto& existing_subdir : subdirectories) {
        if (existing_subdir->get_name() == dirname) {
            std::cerr << "Subdirectory already exists: " << dirname << std::endl;
            return false;
        }
    }
    subdirectories.push_back(std::make_shared<Directory>(dirname));
    std::cout << "Subdirectory added: " << dirname << std::endl;
    return true;
}


bool Directory::remove_subdirectory(const std::string& dirname) {
    auto it = std::find_if(subdirectories.begin(), subdirectories.end(), [&dirname](const std::shared_ptr<Directory>& subdir) {
        return subdir->get_name() == dirname;
    });

    if (it != subdirectories.end()) {
        subdirectories.erase(it);
        std::cout << "Subdirectory removed: " << dirname << std::endl;
        return true;
    } else {
        std::cerr << "Subdirectory not found: " << dirname << std::endl;
        return false;
    }
}


Directory* Directory::get_subdirectory(const std::string& dirname) {
    for (const auto& subdir : subdirectories) {
        if (subdir->get_name() == dirname) {
            return subdir.get();
        }
    }
    std::cerr << "Subdirectory not found: " << dirname << std::endl;
    return nullptr;
}


void Directory::list_contents() const {
    std::cout << "Contents of directory: " << name << std::endl;

    std::cout << "Files:" << std::endl;
    for (const auto& file : files) {
        std::cout << " - " << file.get_name() << std::endl;
    }

    std::cout << "Subdirectories:" << std::endl;
    for (const auto& subdir : subdirectories) {
        std::cout << " - " << subdir->get_name() << std::endl;
    }
}


std::string Directory::get_name() const {
    return name;
}


std::vector<File>& Directory::get_files() {
    return files;
}


std::vector<std::shared_ptr<Directory>>& Directory::get_subdirectories() {
    return subdirectories;
}

bool Directory::create_link(const std::string& link_name, Link::LinkType link_type, File* target_file, const std::string& target_path) {
    if (link_type == Link::LinkType::HARD && !target_file) {
        std::cerr << "Error: Hard link requires a valid target file." << std::endl;
        return false;
    }
    if (link_type == Link::LinkType::SYMBOLIC && target_path.empty()) {
        std::cerr << "Error: Symbolic link requires a valid target path." << std::endl;
        return false;
    }

    Link new_link(link_name, link_type, target_file, target_path);
    files.push_back(new_link);
    return true;
}


void Directory::chmod(int new_permissions) {
    for (auto& file : files) {
        file.chmod(new_permissions);
    }
    for (auto& subdir : subdirectories) {
        subdir->chmod(new_permissions);
    }
}

void Directory::chown(int new_owner_id) {
    for (auto& file : files) {
        file.chown(new_owner_id);
    }
    for (auto& subdir : subdirectories) {
        subdir->chown(new_owner_id);
    }
}


File* Directory::resolve_symbolic_link(const Link& link) {
    if (link.get_type() != Link::LinkType::SYMBOLIC) {
        std::cerr << "Error: Not a symbolic link." << std::endl;
        return nullptr;
    }

    std::string target_path = link.get_target_path();
    
    
    std::istringstream path_stream(target_path);
    std::string segment;
    std::vector<std::string> path_segments;

    while (std::getline(path_stream, segment, '/')) {
        if (!segment.empty()) {
            path_segments.push_back(segment);
        }
    }

    Directory* current_dir = this; 
    File* target_file = nullptr;


    for (size_t i = 0; i < path_segments.size(); ++i) {
        const std::string& segment = path_segments[i];


        if (i == path_segments.size() - 1) {
            target_file = current_dir->get_file(segment);
            if (!target_file) {
                std::cerr << "Error: Target file not found: " << segment << std::endl;
            }
            return target_file;
        } else {

            current_dir = current_dir->get_subdirectory(segment);
            if (!current_dir) {
                std::cerr << "Error: Directory not found: " << segment << std::endl;
                return nullptr;
            }
        }
    }

    return target_file;
}
