#ifndef DUMP_MESSAGES_HPP
#define DUMP_MESSAGES_HPP

#include <cstring>
#include <string>
#include <cstdarg>

extern const char *ARROW_PARTS[];
extern const char *OP_COLORS[];

const char TAB[] = "    ";

const char DUMP_FILE[] = "Int_dump.html";

const char PREFIX[] = "pre";

const unsigned long font_params_amount = 1;
const char FONT[] = "font";
extern const char *FONT_PARAM_NAMES[];
extern const char **FONT_PARAMS[];

const char TMP_VAR[] = "tmp #";

extern const char *MODES[];
enum class MODE_NAME
{
    WRITE,
    READ,
    APPEND
};

/*
 /        \
|  tmp #1  |
 \        /
*/

class File_dump
{
protected:
    FILE *dump_file;
    char *dump_file_name;

    bool to_create;
    bool opened;

public:
    File_dump(const char *file_name);
    virtual ~File_dump();

    virtual void dump(std::string message);
};

class HTML_dump : public File_dump
{
private:
    static size_t tags_amount;

public: 
    struct Tags
    {
        enum Tag_name
        {
            FONT
        };
        bool tags[1];
    };

    struct Attributes {};
    
    struct Font_attributes : public Attributes
    {
        char *color;
        size_t size;
    };

    HTML_dump(const char *file_name);

    void open_tag(std::string tag, size_t attributes_amount, ...);
    void close_tag(std::string tag);

    // void custemized_dump(std::string message, Tags tags, ...);
    // void dump(std::string message) override;
};

#endif // DUMP_MESSAGES_HPP
