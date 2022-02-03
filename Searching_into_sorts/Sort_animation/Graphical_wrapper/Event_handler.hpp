#ifndef EVENT_HANDLER
#define EVENT_HANDLER

#include <SFML/Graphics.hpp>
#include <cctype>

enum class Event_type
{
	NO_EVENT,
	WINDOW,
	MOUSE,
	KEYBOARD,
	TEXT
};

struct Event
{
	Event_type type;
	size_t event;
	size_t sender;
	Vector_ll position;
};

/*enum class Sfml_events
{
	NOTHING,
	WINDOW_CLOSED,
	MOUSE_CLICKED,
	MOUSE_RELEASED,
	MOUSE_MOVED,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_ESC,
	KEY_LCTRL,
	KEY_LSHIFT,
	BACKSPACE
};*/

enum class Window_state
{
	CLOSED,
	OPEN
};

enum class Mouse_state
{
	CLICKED,
	RELEASED,
	MOVED
};

enum class Key_state
{
	PRESSED,
	RELEASED
};

enum class Mouse
{
	LEFT,
	RIGHT,
	MIDDLE
};

enum class Key
{
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	NUM0,
	NUM1,
	NUM2,
	NUM3,
	NUM4,
	NUM5,
	NUM6,
	NUM7,
	NUM8,
	NUM9,
	ESC,
	LCTRL,
	LSHIFT,
	LALT,
	LSYSTEM, 
	RCTRL, 
	RSHIFT,
  	RALT, 
  	RSYSTEM, 
  	MENU, 
  	LBRACKET,
    RBRACKET, 
    SEMICOLON, 
    COMMA, 
    PERIOD = sf::Keyboard::Period,
  	QUOTE, 
  	SLASH, 
  	BACKSLASH, 
  	TILDE,
    EQUAL, 
    HYPHEN, 
    SPACE, 
    ENTER,
    BACKSPACE = sf::Keyboard::Backspace,
	TAB, 
	PAGE_UP, 
	PAGE_DOWN,
	END,
	HOME,
    INSERT, 
    DELETE,
  	ADD, 
  	SUB, 
  	MULT, 
  	DIV,
  	LEFT, 
  	RIGHT, 
  	UP, 
  	DOWN,
  	NUMPAD0,
  	NUMPAD1,
  	NUMPAD2,
  	NUMPAD3,
  	NUMPAD4,
  	NUMPAD5,
  	NUMPAD6,
  	NUMPAD7,
  	NUMPAD8,
  	NUMPAD9,
  	F1,
  	F2,
  	F3,
  	F4,
  	F5,
  	F6,
  	F7,
  	F8,
  	F9,
  	F10,
  	F11,
  	F12,
  	F13,
  	F14,
  	F15,
  	PAUSE
};

class Event_handler
{
public:
	Event detect_event(sf::RenderWindow &window, sf::Event &event)
	{
		if(window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed)
	        {
	           // return Sfml_events::WINDOW_CLOSED;
	        	return { Event_type::WINDOW, (size_t)Window_state::CLOSED, 0 };
	        }

	        if (event.type == sf::Event::MouseButtonPressed)
	        {
	        	// return Sfml_events::MOUSE_CLICKED;
	        	Vector_ll pos = Vector_ll((long long)event.mouseButton.x, (long long)event.mouseButton.y);
	        	return { Event_type::MOUSE, (size_t)Mouse_state::CLICKED, (size_t)Mouse::LEFT, pos };
	        }

	        if (event.type == sf::Event::MouseButtonReleased)
	        {
	        	// return Sfml_events::MOUSE_RELEASED;
	        	Vector_ll pos = Vector_ll((long long)event.mouseButton.x, (long long)event.mouseButton.y);
	        	return { Event_type::MOUSE, (size_t)Mouse_state::RELEASED, (size_t)Mouse::LEFT, pos };
	        }

	        if (event.type == sf::Event::MouseMoved)
	        {
	        	// return Sfml_events::MOUSE_MOVED;
	        	Vector_ll pos = Vector_ll((long long)event.mouseMove.x, (long long)event.mouseMove.y);
	        	return { Event_type::MOUSE, (size_t)Mouse_state::MOVED, (size_t)Mouse::LEFT, pos };
	        }

	        if (event.type == sf::Event::TextEntered)
			{
			    char symbol = event.text.unicode;
			    if (isalpha(symbol) || isdigit(symbol) || ispunct(symbol) || (symbol == ' '))
			    {
			    	return { Event_type::TEXT, (size_t)event.text.unicode, 0 };
			    }
			        // std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
			}
			
			if (event.type == sf::Event::KeyPressed)
	        {
	        	return { Event_type::KEYBOARD, (size_t)Key_state::PRESSED, (size_t)Key::A + (size_t)event.key.code };
	        }

	        if (event.type == sf::Event::KeyReleased)
	        {
	        	return { Event_type::KEYBOARD, (size_t)Key_state::RELEASED, (size_t)Key::A + (size_t)event.key.code };
	        }
	    }

        // return Sfml_events::NOTHING;
        return { Event_type::NO_EVENT, 0 };
	}
};

#endif // EVENT_HANDLER
