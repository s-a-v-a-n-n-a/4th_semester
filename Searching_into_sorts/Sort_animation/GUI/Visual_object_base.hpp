#ifndef VISUAL_OBJECT_BASE
#define VISUAL_OBJECT_BASE

#include <cstdio>
#include <cstdlib>
#include <cassert>

#include "../simple_list/simple_list.hpp"
#include "../Graphical_wrapper/screen_functions.hpp"
#include "../Graphical_wrapper/Texture.hpp"
#include "../math_structures/Radius_vector.hpp"

// #include "../Editor/Vidget_types.hpp"

#include "Resource_manager.hpp"

class Visual_object
{
protected:
	struct Config
	{
		Visual_object *parent;

		const size_t type;

		Vector_ll position;

		Texture *texture;
		Color color;
		// bool is_texture;

		size_t width;
		size_t height;
	};

	Visual_object *current_active;

private:
	
	Config base;

	// Visual_object *parent;
	List<Visual_object*> objects;

	bool active;
	bool visible;
	bool reactive;
	bool alive;

public:
	Visual_object() = delete;
	Visual_object(const Visual_object::Config &par_base);
	~Visual_object() {};
	
	virtual void add_visual_object(Visual_object *par_object);
	virtual void slow_delete_visual_object(size_t index);
	virtual long long very_slow_delete_visual_object(Visual_object *par_object);
	virtual long long very_slow_extract_visual_object(Visual_object *par_object);

	virtual void draw(Screen_information *screen);

	void move_to_end(Visual_object *child, size_t child_number);

	virtual bool point_inside (const size_t par_x, const size_t par_y);
	virtual bool on_mouse_click  (const bool state, const size_t par_x, const size_t par_y); //const Mouse_event par_event,
	virtual bool on_mouse_move	(const Vector_ll from, const Vector_ll to);
	virtual bool on_key_pressed(const bool pressed_state, const unsigned key_mask); 
	virtual bool on_text_entered(const char symbol); 
	// virtual bool on_key_press(const Key_event par_event);

	virtual void tick(const double delta);

	Visual_object 		   *get_parent()                { return base.parent; }
	List<Visual_object*>   *get_objects()        		{ return &objects; }
	Vector_ll  				get_position() 		const 	{ return base.position; }
	Color         		 	get_color()    		const 	{ return base.color; }
	size_t         			get_width()    		const 	{ return base.width; }
	size_t         			get_height()   		const 	{ return base.height; }
	Visual_object 		   *get_active() 				{ return current_active; }
	bool					get_active_state() 	const 	{ return active; }
	bool				    get_visible()  	   	const 	{ return visible; }
	bool				    get_reactive()  	const 	{ return reactive; }
	bool				    get_alive()  		const 	{ return alive; }
	size_t					get_type()			const	{ return base.type; }
	Texture 			   *get_texture()				{ return base.texture; }

	virtual void set_parent         (Visual_object *par_parent)   		{ base.parent = par_parent; }
	virtual void set_position 		(const Vector_ll &par_position);
	virtual void set_color    		(const Color &par_color)            { base.color = par_color; }
	virtual void set_width    		(const size_t par_width);
	virtual void set_height   		(const size_t par_height);
	virtual void set_active_state   (const bool par_active)             { active = par_active; }
	virtual void set_active  		(Visual_object *par_current_active);
	virtual void set_visible		(const bool par_visible)			{ visible = par_visible; }
	virtual void set_reactive		(const bool par_reactive)			{ reactive = par_reactive; }
	virtual void set_alive			(const bool par_alive)				{ alive = par_alive; }
	virtual void set_texture 		(Texture *par_texture)				{ base.texture = par_texture; }
};

#endif // VISUAL_OBJECT_BASE
