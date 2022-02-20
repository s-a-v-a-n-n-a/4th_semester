#include "Dot_dump.hpp"

Dot_dump::Dot_dump(const char *file_name)
: File_dump(file_name)
{
    if (!opened)
    {
        if (to_create)
        {
            dump_file = fopen(dump_file_name, MODES[(int)MODE_NAME::WRITE]);
            to_create = false;
        }
        else
        {
            dump_file = fopen(dump_file_name, MODES[(int)MODE_NAME::APPEND]);
        }

        // opened = true;
    }

    fprintf(dump_file, "digraph structs {\n");

    fclose(dump_file);
}

Dot_dump::~Dot_dump()
{
    if (!opened)
    {
        if (to_create)
        {
            dump_file = fopen(dump_file_name, MODES[(int)MODE_NAME::WRITE]);
            to_create = false;
        }
        else
        {
            dump_file = fopen(dump_file_name, MODES[(int)MODE_NAME::APPEND]);
        }

        // opened = true;
    }

    dump_arrows(); 
    dump_file = fopen(dump_file_name, MODES[(int)MODE_NAME::APPEND]);
    fprintf(dump_file, "}\n");

    fclose(dump_file);
}

void Dot_dump::create_box(const char *name, const char *label, const char *bgcolor, const char *box_type)
{
    if (!opened)
    {
        if (to_create)
        {
            dump_file = fopen(dump_file_name, MODES[(int)MODE_NAME::WRITE]);
            to_create = false;
        }
        else
        {
            dump_file = fopen(dump_file_name, MODES[(int)MODE_NAME::APPEND]);
        }

        // opened = true;
    }

    fprintf(dump_file, "    %s [shape=%s, style=filled, fillcolor=%s label=\"%s\"];\n", name, box_type, bgcolor, label);
    
    fclose(dump_file);
}

void Dot_dump::create_arrow(const char *from, const char *to, const char *arrow_type)
{
    assert(from);
    assert(to);
    assert(arrow_type);

    arrows.push_back({from, to, arrow_type});
}

void Dot_dump::dump_arrows() // Просто выписывает все существующие стрелки и удаляет их из вектора
{
    if (!opened)
    {
        if (to_create)
        {
            dump_file = fopen(dump_file_name, MODES[(int)MODE_NAME::WRITE]);
            to_create = false;
        }
        else
        {
            dump_file = fopen(dump_file_name, MODES[(int)MODE_NAME::APPEND]);
        }

        // opened = true;
    }

    size_t arrows_amount = arrows.size();
    
    for (size_t i = 0; i < arrows_amount; ++i)
    {
        fprintf(dump_file, "    %s -> %s [style=%s];\n", arrows[i].from.c_str(), arrows[i].to.c_str(), arrows[i].type.c_str());
    }

    arrows.clear();

    fclose(dump_file);
}
