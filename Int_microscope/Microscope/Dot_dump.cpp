#include "Dot_dump.hpp"

Dot_dump::Dot_dump(const char *file_name)
: File_dump(file_name)
{
    if (!opened)
    {
        if (to_create)
        {
            dump_file = fopen(DUMP_FILE, MODES[(int)MODE_NAME::WRITE]);
            to_create = false;
        }
        else
        {
            dump_file = fopen(DUMP_FILE, MODES[(int)MODE_NAME::APPEND]);
        }

        opened = true;
    }

    fprintf(dump_file, "digraph structs {\n");
}

Dot_dump::~Dot_dump()
{
    if (!opened)
    {
        if (to_create)
        {
            dump_file = fopen(DUMP_FILE, MODES[(int)MODE_NAME::WRITE]);
            to_create = false;
        }
        else
        {
            dump_file = fopen(DUMP_FILE, MODES[(int)MODE_NAME::APPEND]);
        }

        opened = true;
    }

    dump_arrows(); 
    fprintf(dump_file, "}\n");

    fclose(dump_file);
}

void Dot_dump::create_box(const char *name, const char *label, std::string arrow_beginning, std::string arrow_type)
{
    if (!opened)
    {
        if (to_create)
        {
            dump_file = fopen(DUMP_FILE, MODES[(int)MODE_NAME::WRITE]);
            to_create = false;
        }
        else
        {
            dump_file = fopen(DUMP_FILE, MODES[(int)MODE_NAME::APPEND]);
        }

        opened = true;
    }

    fprintf(dump_file, "    struct%s [label=\"%s\"];\n", name, label);
    if (arrow_beginning.size())
        arrows.push_back({arrow_beginning, name, arrow_type});

    fclose(dump_file);
}

void Dot_dump::dump_arrows() // Просто выписывает все существующие стрелки и удаляет их из вектора
{
    if (!opened)
    {
        if (to_create)
        {
            dump_file = fopen(DUMP_FILE, MODES[(int)MODE_NAME::WRITE]);
            to_create = false;
        }
        else
        {
            dump_file = fopen(DUMP_FILE, MODES[(int)MODE_NAME::APPEND]);
        }

        opened = true;
    }

    size_t arrows_amount = arrows.size();
    
    for (size_t i = 0; i < arrows_amount; ++i)
    {
        fprintf(dump_file, "%s -> %s [style=%s]\n", arrows[i].from, arrows[i].to, arrows[i].type);
    }

    arrows.clear();

    fclose(dump_file);
}
