#ifndef SFML_TEXT_H
#define SFML_TEXT_H

#include <SFML/Graphics.hpp>

extern const char GHOST_TYPE[];
extern const char ARIAL[];

size_t get_text_length(const char *par_font_name, const char *par_text, const size_t par_text_size);

#endif // SFML_TEXT_H
