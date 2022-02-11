#include "Dump_messages.hpp"

const char *ARROW_PARTS[] = 
{
    "|",
    "+--->"
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
    "DA3131", // COPY
    "000000",
    "000000",
    "000000",
    "000000",
    "000000",
    "000000",
    "7BE76D" // MOVE
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
