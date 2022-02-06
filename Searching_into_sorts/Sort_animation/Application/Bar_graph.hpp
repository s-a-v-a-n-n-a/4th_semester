#ifndef BAR_GRAPH_HPP
#define BAR_GRAPH_HPP

#include "../GUI/Visual_object_base.hpp"
#include "../Shapes/Rectangle.hpp"
#include "../math_structures/Int_signal_receiver.hpp"
#include "../math_structures/Int_container.hpp"

class Bar_graph : public Visual_object, public Int_signal_receiver
{
private:
    std::vector<Rectangle*> elements;
    
    std::vector<size_t> match_prototypes_indices;
    std::vector<size_t> old_prototypes_indices;

    Int_container *reference;

public:
    Bar_graph(const Visual_object::Config &par_base, Int_container *par_reference);
    ~Bar_graph();

    void signal(Int_signal signal_type, const Intercepted_int &sender, const Intercepted_int &other) override;

    void draw(Screen_information *screen) override;
    
    void change_places(size_t whom, size_t where);
    void redraw();

    void synchronize();
};

#endif // BAR_GRAPH_HPP
