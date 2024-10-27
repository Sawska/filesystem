#include "filesystem.h"
#include <iostream>
#include <sstream>

Filesystem::Filesystem() {
    root = new Directory("root");  
}

void Filesystem::createFile(const std::string& path, const std::string& filename) {
    Directory* dir = navigateTo(path);
    if (!dir) {
        std::cerr << "Error: Directory " << path << " does not exist." << std::endl;
        return;
    }
    File new_file(filename, 0, 644);
    if (dir->add_file(new_file)) {
        std::cout << "File " << filename << " created at " << path << std::endl;
    } else {
        std::cerr << "Error: File " << filename << " could not be created." << std::endl;
    }
}

void Filesystem::createDirectory(const std::string& path, const std::string& dirname) {
    Directory* dir = navigateTo(path);
    if (!dir) {
        std::cerr << "Error: Directory " << path << " does not exist." << std::endl;
        return;
    }
    if (dir->add_subdirectory(dirname)) {
        std::cout << "Directory " << dirname << " created at " << path << std::endl;
    } else {
        std::cerr << "Error: Directory " << dirname << " could not be created." << std::endl;
    }
}

void Filesystem::deleteFile(const std::string& path) {
    size_t last_slash = path.find_last_of('/');
    std::string dir_path = path.substr(0, last_slash);
    std::string filename = path.substr(last_slash + 1);

    Directory* dir = navigateTo(dir_path);
    if (!dir) {
        std::cerr << "Error: Directory " << dir_path << " does not exist." << std::endl;
        return;
    }
    if (dir->remove_file(filename)) {
        std::cout << "File " << filename << " deleted from " << dir_path << std::endl;
    } else {
        std::cerr << "Error: File " << filename << " could not be deleted." << std::endl;
    }
}

void Filesystem::deleteDirectory(const std::string& path) {
    size_t last_slash = path.find_last_of('/');
    std::string parent_path = path.substr(0, last_slash);
    std::string dirname = path.substr(last_slash + 1);

    Directory* parent_dir = navigateTo(parent_path);
    if (!parent_dir) {
        std::cerr << "Error: Directory " << parent_path << " does not exist." << std::endl;
        return;
    }
    if (parent_dir->remove_subdirectory(dirname)) {
        std::cout << "Directory " << dirname << " deleted from " << parent_path << std::endl;
    } else {
        std::cerr << "Error: Directory " << dirname << " could not be deleted." << std::endl;
    }
}

void Filesystem::listDirectoryContents(const std::string& path) {
    Directory* dir = navigateTo(path);
    if (!dir) {
        std::cerr << "Error: Directory " << path << " does not exist." << std::endl;
        return;
    }
    dir->list_contents();
}

Directory* Filesystem::navigateTo(const std::string& path) {
    std::istringstream path_stream(path);
    std::string token;
    Directory* current = root;

    while (std::getline(path_stream, token, '/')) {
        if (token.empty()) continue;
        Directory* next_dir = current->get_subdirectory(token);
        if (!next_dir) {
            std::cerr << "Error: Path " << path << " does not exist." << std::endl;
            return nullptr;
        }
        current = next_dir;
    }
    return current;
}

void Filesystem::mount(const std::string &path, Directory *fs)
{
        if(navigateTo(path)) {
            mounts[path] = fs;
            std::cout << "Mounted filesystem at" << path << std::endl;
        } else {
            std::cerr << "Error: Mount point " << path << " does not exist." << std::endl;
        }
}

void Filesystem::unmount(const std::string& path) {
    if (mounts.erase(path)) {
        std::cout << "Unmounted filesystem from " << path << std::endl;
    } else {
        std::cerr << "Error: Mount point " << path << " not found." << std::endl;
    }
}

void Filesystem::search(const std::string& name, const std::string& path) {
    Directory* dir = navigateTo(path);
    if (!dir) return;

 
    for (const auto& file : dir->get_files()) {
        if (file.get_name() == name) {
            std::cout << "File found: " << file.get_name() << " in " << path << std::endl;
        }
    }
    for (const auto& subdir : dir->get_subdirectories()) {
        search(name, path + "/" + subdir->get_name());
    }
}

bool Filesystem::chmod(const std::string& path, int new_permissions) {
    Directory* dir = navigateTo(path);
    if (dir) {
        dir->chmod(new_permissions);
        std::cout << "Permissions set for directory and contents at " << path << std::endl;
        return true;
    }
    File* file = dir->get_file(path);
    if (file) {
        file->chmod(new_permissions);
        std::cout << "Permissions set for file at " << path << std::endl;
        return true;
    }
    std::cerr << "Error: Path " << path << " not found." << std::endl;
    return false;
}

bool Filesystem::chown(const std::string& path, int new_owner_id) {
    Directory* dir = navigateTo(path);
    if (dir) {
        dir->chown(new_owner_id);
        std::cout << "Ownership set for directory and contents at " << path << std::endl;
        return true;
    }
    File* file = dir->get_file(path);
    if (file) {
        file->chown(new_owner_id);
        std::cout << "Ownership set for file at " << path << std::endl;
        return true;
    }
    std::cerr << "Error: Path " << path << " not found." << std::endl;
    return false;
}