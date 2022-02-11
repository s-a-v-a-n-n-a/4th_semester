#include "Int_listing.hpp"

const char *Signal_names[] = 
{
    "+",
    "+=",
    "prefix increment",
    "postfix increment",
    "-",
    "-=",
    "prefix decrement",
    "postfix decrement",
    "*",
    "*=",
    "/",
    "/=",
    "=",
    ">",
    ">=",
    "<",
    "<=",
    "==",
    "!="
};

void Int_listing::signal(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other)
{
    printf("Operation %s on int %d by address %p with int %d by address %p\n", Signal_names[(int)signal_type], sender.get_num(), &sender, other.get_num(), &other);
}

/*
void list_print_list_appearance(List *that_list, list_code code, const list_functions function)
{
    static long int doing = 0;

    const char* mode = "";
    if (!doing)
        mode = "wb";
    else
        mode = "ab";
    FILE* log = fopen("list_print_list_appearance.html", mode);

    fprintf(log, "<pre><font size=\"5\"  face=\"Times New Roman\">\n");

    fprintf(log, "<p><span style=\"font-weight: bold\">CURRENT STATE OF LIST</span></p>\n");
    fprintf(log, "THE NEWS FROM %s\n", FUNCTION_IDENTIFIERS[function]);

    fprintf(log, "%s", state_text[code]);
    if (that_list->sorted)
        fprintf(log, "CURRENT STATE OF SORTING IS <span style=\"font-weight: bolder\">TRUE</span>\n");
    else
        fprintf(log, "CURRENT STATE OF SORTING IS <span style=\"font-weight: bolder\">FALSE</span>\n");

    fprintf(log, "CURRENT CAPACITY IS %u\n", that_list->capacity);
    fprintf(log, "CURRENT SIZE IS            %u\n", that_list->length);

    fprintf(log, "</font><tt>\n");

    char picture_name[MAX_PICTURE_NAME]          = "";

    char picture_adding[MAX_PICTURE_NAME]        = "";
    sprintf(picture_adding, "%d.txt", doing);

    char picture_format_name[MAX_PICTURE_NAME]   = "";
    char picture_format_adding[MAX_PICTURE_NAME] = "";
    #ifdef SLOW_PRINT
    sprintf(picture_name, "%s", PICTURE_FILE_CODE);

    strncat(picture_name, picture_adding, MAX_PICTURE_NAME);

    sprintf(picture_format_name, "%s", PICTURE_FILE_CODE);

    strncat(picture_format_name, picture_adding, MAX_PICTURE_NAME);

    sprintf(picture_format_adding, ".%s", PICTURE_FORMAT);

    strncat(picture_format_name, picture_format_adding, MAX_PICTURE_NAME);

    list_slow_print_logical_state(that_list, picture_name);
    fprintf(log, "<img src=%s>\n", picture_format_name);
    #endif

    sprintf(picture_name, "%s", PICTURE_FILE_CODE_REAL);
    strncat(picture_name, picture_adding, MAX_PICTURE_NAME);

    sprintf(picture_format_name, "%s", PICTURE_FILE_CODE_REAL);
    strncat(picture_format_name, picture_adding, MAX_PICTURE_NAME);
    strncat(picture_format_name, picture_format_adding, MAX_PICTURE_NAME);

    list_print_physical_state(that_list, picture_name);
    fprintf(log, "<img src=%s>", picture_format_name);

    fprintf(log, "\n");

    fclose(log);

    doing++;
}
*/

/*
void make_box(FILE *picture, List *that_list, const char *index_color, const char *fill_color, size_t index)
{
    fprintf(picture, "  nod%u[shape=\"none\" ", index);
    if (index == 0)
    {
        fprintf(picture, "      label = <<table border = \"0\" cellborder = \"1\" cellspacing = \"0\">\n   <tr>\n      <td bgcolor = \"%s\" rowspan = \"3\">%u</td>\n", COLOR_FICTIVE_INDEX, index);
        fprintf(picture, "      <td bgcolor =  \"%s\" port = \"n%u\">%u</td>\n", COLOR_FICTIVE_FILL, index, that_list->next[index]);
        fprintf(picture, "      </tr>\n      <tr>\n");
        fprintf(picture, "      <td bgcolor =  \"%s\">"list_elem_specifier"</td>\n", COLOR_FICTIVE_FILL, that_list->data[index]);
        fprintf(picture, "      </tr>\n      <tr>\n");
        fprintf(picture, "      <td bgcolor =  \"%s\" port = \"p%u\">%u</td>\n", COLOR_FICTIVE_FILL, index, that_list->prev[index]);
    }
    else
    {
        fprintf(picture, "      label = <<table border = \"0\" cellborder = \"1\" cellspacing = \"0\">\n   <tr>\n      <td bgcolor = \"%s\" rowspan = \"3\">%u</td>\n", index_color, index);
        fprintf(picture, "      <td bgcolor =  \"%s\" port = \"n%u\">%u</td>\n", fill_color, index, that_list->next[index]);
        fprintf(picture, "      </tr>\n      <tr>\n");
        fprintf(picture, "      <td bgcolor =  \"%s\">"list_elem_specifier"</td>\n", fill_color, that_list->data[index]);
        fprintf(picture, "      </tr>\n      <tr>\n");
        fprintf(picture, "      <td bgcolor =  \"%s\" port = \"p%u\">%u</td>\n", fill_color, index, that_list->prev[index]);
    }
    fprintf(picture, "      </tr>\n      </table>>];\n");
}
*/

/*
index = that_list->first_free;
for (size_t i = that_list->length + 1; i <= that_list->capacity; i++)
{
    make_box(picture, that_list, COLOR_INDEX_ADD, COLOR_FILL_ADD, index);

    index = that_list->next[index];
}
index = that_list->first_free;
fprintf(picture, "  nod%u->", that_list->prev[0]);
*/
