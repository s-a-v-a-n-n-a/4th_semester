#ifndef BAR_GRAPH_HPP
#define BAR_GRAPH_HPP

#include "../GUI/Visual_object_base.hpp"
#include "../Shapes/Rectangle.hpp"
#include "../math_structures/Int_container.hpp"

class Bar_graph : public Visual_object
{
private:
    std::vector<Rectangle*> elements;
    Int_container *reference;

public:
    Bar_graph(const Visual_object::Config &par_base, Int_container *par_reference);

    void draw(Screen_information *screen);
    void change_places(size_t index1, size_t index2);
    void redraw();
};

#endif // BAR_GRAPH_HPP
