#ifndef FILE_H

#define FILE_H

#include <string>
#include <vector>
#include <ctime>

class File {
private:
    int id;
    int size;
    int valid_bit;
    int permission_bits;
    bool is_open; 
    std::string name;
    std::time_t created_at;
    std::time_t modified_at;
    int owner_id;
    bool is_hidden = false;
    bool is_read_only = false;
    std::time_t accessed_at;

public:
    File(std::string name, int id, int permission_bits);

    bool read();
    bool write(const std::string& data);
    bool open();
    void close();

    std::string get_name() const;
    void chmod(int new_permissions) { permission_bits = new_permissions; }
    void chown(int new_owner_id) { owner_id = new_owner_id; }
    void set_flag(std::string flag, bool value);
    int get_size() const;
    int get_permissions() const;
    void set_permissions(int permissions);
    std::time_t get_created_at() const { return created_at; }
    std::time_t get_modified_at() const { return modified_at; }
    void update_modified_at() { modified_at = std::time(nullptr); }
    void update_accessed_at() { accessed_at = std::time(nullptr); }
};

#endif //FILE_H