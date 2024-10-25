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
    std::string name;
    std::time_t created_at;
    std::time_t modified_at;

public:
    File(std::string name, int id, int permission_bits);

    bool read();
    bool write(const std::string& data);
    bool open();
    void close();

    std::string get_name() const;
    int get_size() const;
    int get_permissions() const;
    void set_permissions(int permissions);
};

#endif //FILE_H