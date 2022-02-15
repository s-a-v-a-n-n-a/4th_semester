#ifndef DOT_DUMP_HPP
#define DOT_DUMP_HPP

#include <vector>

#include "Dump_messages.hpp"

class Dot_dump : public File_dump
{
private:
    struct Arrow
    {
        std::string from;
        std::string to;
    };

    std::vector<Arrow> arrows;

public:
    Dot_dump(const char *file_name);

    void create_box(const char *name, const char *label, std::vector<char*> arrow_ends);
    void dump_arrows(); // Просто выписывает все существующие стрелки и удаляет их из вектора
};

#endif // DOT_DUMP_HPP
