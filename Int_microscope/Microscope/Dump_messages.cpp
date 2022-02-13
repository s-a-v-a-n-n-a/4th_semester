#include "Dump_messages.hpp"

const char *ARROW_PARTS[] = 
{
    // "|",
    "--->",
    "<---"
};

const char *OP_COLORS[] =
{
    "000000",
    "000000",
    "000000",
    "000000",
    "000000",
    "000000",
    "000000",
    "000000",
    "000000",
    "000000",
    "000000",
    "000000",
    "000000",
    "DA3131", // COPY
    "000000",
    "000000",
    "000000",
    "000000",
    "000000",
    "000000",
    "7BE76D", // MOVE
    "000000",
    "000000"
};

const char *FONT_PARAM_NAMES[] = 
{
    "color",
    "size",
    "face"
};

const char **FONT_PARAMS[] = 
{
    OP_COLORS, 
    nullptr,
    nullptr
};

const char *MODES[] = 
{
    "wb",
    "rb", 
    "ab"
};

File_dump::File_dump(const char *file_name)
: dump_file(nullptr), to_create(true), opened(false)
{
    size_t file_name_len = strlen(file_name);
    dump_file_name = new char[file_name_len];

    strncpy(dump_file_name, file_name, file_name_len);
}

File_dump::~File_dump()
{
    delete [] dump_file_name;
}

void File_dump::dump(std::string message)
{
    bool not_close = true;

    if (!opened)
    {
        not_close = false;
        if (to_create)
        {
            dump_file = fopen(DUMP_FILE, MODES[(int)MODE_NAME::WRITE]);
            to_create = false;
        }
        else
        {
            dump_file = fopen(DUMP_FILE, MODES[(int)MODE_NAME::APPEND]);
        }
    }

    fprintf(dump_file, "%s", message.c_str());

    if (!not_close)
        fclose(dump_file);
}

size_t HTML_dump::tags_amount = 1;

HTML_dump::HTML_dump(const char *file_name)
: File_dump(file_name) {}

void HTML_dump::open_tag(std::string tag, size_t attributes_amount, ...)
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

    fprintf(dump_file, "%c%s", '<', tag.c_str());

    va_list attributes;
    va_start(attributes, attributes_amount);
    for (size_t i = 0; i < attributes_amount; ++i)
    {
        char *attribute_name = va_arg(attributes, char *);
        char *attribute_value = va_arg(attributes, char *);

        fprintf(dump_file, " %s=\"%s\"", attribute_name, attribute_value);
    }
    va_end(attributes);

    fprintf(dump_file, ">");
}

void HTML_dump::close_tag(std::string tag)
{
    if (!opened)
    {
        if (to_create)
        {
            dump_file = fopen(DUMP_FILE, MODES[(int)MODE_NAME::WRITE]);
            to_create = false;
        }
        else
            dump_file = fopen(DUMP_FILE, MODES[(int)MODE_NAME::APPEND]);
    }

    fprintf(dump_file, "</%s>", tag.c_str());

    fclose(dump_file);
    opened = false;
}


// void HTML_dump::custemized_dump(std::string message, Tags tags, ...)
// {
//     bool not_close = true;

//     if (!opened)
//     {
//         not_close = false;
//         if (to_create)
//         {
//             dump_file = fopen(DUMP_FILE, MODES[(int)MODE_NAME::WRITE]);
//             to_create = false;
//         }
//         else
//         {
//             dump_file = fopen(DUMP_FILE, MODES[(int)MODE_NAME::APPEND]);
//         }
//     }
    
//     size_t tags_amount = 0;
    
//     va_list attributes;
//     va_start(attributes, tags); 

//     for (size_t i = 0; i < tags_amount; ++i)
//     {
//         if (tags.tags[i])
//         {
//             switch(i)
//             {
//             case tags.FONT:
//             {
//                 Font_attributes font_settings = va_arg(attributes, Font_attributes);
//                 // open_font_tag(i, font_settings);
//                 break;
//             }
//             default:
//                 break;
//             }
//         }
//     }

//     File_dump::dump(message);

//     for (size_t i = 0; i < tags_amount; ++i)
//     {
//         if (tags.tags[i])
//         {
//             // close_tag(i);
//         }
//     }

//     if (not_close)
//         fclose(dump_file);
// }




