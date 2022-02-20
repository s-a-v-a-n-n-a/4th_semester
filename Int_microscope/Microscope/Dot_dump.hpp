#ifndef DOT_DUMP_HPP
#define DOT_DUMP_HPP

#include <vector>
#include <string>
#include <cassert>

#include "Dump_messages.hpp"

class Dot_dump : public File_dump
{
private:
    struct Arrow
    {
        std::string from;
        std::string to;

        std::string type;
    };

    std::vector<Arrow> arrows;

public:
    Dot_dump(const char *file_name);
    ~Dot_dump();

    void create_box(const char *name, const char *label, const char *bgcolor = "\"#ffffff\"", const char *box_type = "record");
    void create_arrow(const char *from, const char *to, const char *arrow_type = "solid");
    void dump_arrows(); // Просто выписывает все существующие стрелки и удаляет их из вектора
};

#endif // DOT_DUMP_HPP
