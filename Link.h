#ifndef LINK_H
#define LINK_H

#include "file.h"

class Link : public File {
public:
    enum class LinkType { SYMBOLIC, HARD };
    
    Link(const std::string& name, LinkType type, File* target = nullptr, const std::string& target_path = "")
        : File(name, 0, 0), link_type(type), target_file(target), target_path(target_path) {}

    LinkType get_type() const { return link_type; }
    File* get_target_file() const { return target_file; }
    const std::string& get_target_path() const { return target_path; }

private:
    LinkType link_type;
    File* target_file;
    std::string target_path;
};

#endif // LINK_H
