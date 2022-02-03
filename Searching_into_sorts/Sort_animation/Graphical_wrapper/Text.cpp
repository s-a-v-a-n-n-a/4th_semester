#include "Text.hpp"

const char GHOST_TYPE[] = "graphical_attributes/Fonts/OpenGostTypeA-Regular.ttf";
const char ARIAL[]      = "graphical_attributes/Fonts/arial.ttf";

size_t get_text_length(const char *par_font_name, const char *par_text, const size_t par_text_size)
{
	sf::Font font = {};
	if (!font.loadFromFile(par_font_name))
	{
	    printf("No fonts found\n");
	    return 0;
	}
	else
	{
		sf::Text drawable_text = {};//(par_text, font, par_text_size);
		drawable_text.setFont(font);
		drawable_text.setString(par_text);
		drawable_text.setCharacterSize(par_text_size);
		
		return drawable_text.getGlobalBounds().width;
	}
}