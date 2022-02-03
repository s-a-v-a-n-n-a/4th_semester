#ifndef TEXT_CLASS
#define TEXT_CLASS

#include <cstring>

#include "Visual_object_base.hpp"

class Text : public Visual_object
{
private:
	// List<Visual_object*> objects;

	// Vector_ll position;
	// Color color;

	// size_t width;
	// size_t height;

	// bool active;

	// char *font_file; 
	bool was_drawn;
	size_t font_size; 

	char *text;

	bool centered;

public:
	Text(Visual_object *parent, const size_t par_type, const char *par_text, const size_t par_font_size, const Vector_ll &par_position, const Color &par_color, const bool par_centered = true)
	: Visual_object({parent, par_type, par_position, nullptr, par_color, strlen(par_text), par_font_size}), centered(par_centered)
	{
		set_color(par_color);

		font_size = par_font_size;

		text = new char[strlen(par_text) + 1];
		strcpy(text, par_text);

		was_drawn = false;
	}

	~Text()
	{
		delete [] text;
	}

	void set_text(const char *par_text)
	{
		size_t par_text_size = strlen(par_text);
		if (strlen(text) < par_text_size)
		{
			delete text;
			text = new char[par_text_size + 1];
		}
		strncpy(text, par_text, par_text_size);
		text[par_text_size] = '\0';
	}

	char *get_text()
	{
		return text;
	}

	void set_font_size(const size_t par_font_size) { font_size = par_font_size; }

	void draw(Screen_information *screen) override
	{
		screen->draw_text(text, get_position(), get_color(), font_size, centered);
	}
};

#endif // TEXT_CLASS
