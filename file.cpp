#include "file.h"
#include <iostream>
#include <ctime>

File::File(std::string name, int id, int permission_bits)
    : name(name), id(id), permission_bits(permission_bits), size(0), valid_bit(1) {
    created_at = std::time(nullptr);  
    modified_at = created_at;
}

bool File::open() {
    if(valid_bit == 0) {
        std::cerr << "Error: File is marked as deleted" << std::endl;
        return false;
    }

    std::cout << "File" << name << "opened succsesfully" << std::endl;
    return true;
}

bool File::read() {
    if ((permission_bits & 0b100) == 0) {  
        std::cerr << "Error: Read permission denied for " << name << std::endl;
        return false;
    }
 
    std::cout << "Reading from file " << name << "..." << std::endl;
    return true;
}

bool File::write(const std::string& data) {
    if ((permission_bits & 0b100) == 0 ) {
        std::cerr << "Error: Write permission denied for " << name << std::endl;
        return false;
    }

    size += data.size();
    modified_at = std::time(nullptr);
    std::cout << "Writting data to file" << name << ":" << data << std::endl;
    return true;
 }

std::string File::get_name() const {
    return name;
}

int File::get_size() const {
    return size;
}

int File::get_permissions() const {
    return permission_bits;
}

void File::set_permissions(int permissions) {
    permission_bits = permissions;
}