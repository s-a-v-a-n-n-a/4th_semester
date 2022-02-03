GREEN   = @echo "\033[0;32m";
DFLT    = @echo "\033[0;m";
 
ifeq ($(ASAN), 1)
ASAN =-fsanitize=address
else
ASAN =
endif

COMPILATOR  = clang++ -std=c++17# g++ -std=c++17
INC     	= 
SFML    	= -lsfml-graphics -lsfml-window -lsfml-system
OPT     	= -O3
DEF     	= -DNDEBUG
CFLAGS  	= $(OPT) $(DEF) $(ASAN) -g $(INC) 
DLL			= -ldl -lm -lpthread -pthread
OBJ     	= obj/
EXE     	= main
 
FILES   	= $(OBJ)main.o \
			$(OBJ)math_structures/Sorts.o \
			$(OBJ)math_structures/Sorts_research.o \
			$(OBJ)Graphical_wrapper/Renderer.o \
			$(OBJ)Graphical_wrapper/screen_functions.o \
			$(OBJ)Graphical_wrapper/colors.o \
			$(OBJ)Graphical_wrapper/Texture_names.o \
			$(OBJ)Graphical_wrapper/Text.o \
			$(OBJ)Graphical_wrapper/Texture.o \
			$(OBJ)GUI/Visual_object_base.o \
			$(OBJ)GUI/Button.o \
			$(OBJ)GUI/Button_manager.o \
			$(OBJ)GUI/Resource_manager.o \
			$(OBJ)GUI/Animations.o \
			$(OBJ)GUI/Chart.o \
			$(OBJ)Editor/Application.o \
			$(OBJ)Editor/Graphical_delegates.o \
			$(OBJ)Editor/Window.o \
			$(OBJ)Editor/Window_control_panel.o \
			$(OBJ)Editor/Main_page.o \
			$(OBJ)Editor/Chart_window.o \
			$(OBJ)Editor/Chart_delegates.o \

          # остальные файлы по правилу a.cpp -> $(OBJ)a.o (a может содержать путь)
 
 
#
# Rules
#
 
all: $(FILES)
	$(GREEN)
	@echo 'Linking $@ (changed $?)';
	$(DFLT)
	@$(COMPILATOR) $(CFLAGS) $(FILES) $(SFML) $(DLL) -o $(EXE)
	
obj/%.o: %.cpp
	$(GREEN)
	@echo 'Building $@ (changed $?)';
	$(DFLT)
	@$(COMPILATOR) $(CFLAGS) $^ -c
	@mkdir -p $(@D)
	@mv $(@F) $@
	
clean:
	$(GREEN)
	@echo 'Cleaning the project';
	$(DFLT)
	@rm $(FILES)

run: all
	./$(EXE)


# COMPILATOR = g++
# CFLAGS = -g -masm=intel -no-pie -march=native -O3 -std=c++17

# link: screen_functions.o colors.o sfml_text.o visual_base.o button.o canvas.o canvas_manager.o window_control_panel.o graphical_editor.o canvas_mm.o tab.o editor_delegate.o palette.o color_picker.o gradient_bar.o color_selection.o button_manager.o texture_names.o animations.o resource_manager.o graphical_delegate.o interpolation.o spline.o slider.o toolbar.o input_string.o app.o main.o
# 	$(COMPILATOR) screen_functions.o colors.o sfml_text.o visual_base.o button.o canvas.o canvas_manager.o window_control_panel.o graphical_editor.o canvas_mm.o tab.o editor_delegate.o palette.o color_picker.o gradient_bar.o color_selection.o button_manager.o texture_names.o animations.o resource_manager.o graphical_delegate.o interpolation.o spline.o slider.o toolbar.o input_string.o app.o main.o -o main -lsfml-graphics -lsfml-window -lsfml-system

# main.o : main.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o main.o main.cpp

# # graphic shell
# # -----------------------------------------------------------------------------------
# screen_functions.o: sfml_drawing/screen_functions.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o screen_functions.o sfml_drawing/screen_functions.cpp

# colors.o: sfml_drawing/colors.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o colors.o sfml_drawing/colors.cpp

# texture_names.o: sfml_drawing/Texture_names.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o texture_names.o sfml_drawing/Texture_names.cpp

# sfml_text.o: sfml_drawing/Text.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o sfml_text.o sfml_drawing/Text.cpp
# # -----------------------------------------------------------------------------------


# # math
# # -----------------------------------------------------------------------------------
# # Vector_ll.o: math_structures/Vector_ll.cpp
# # 	$(COMPILATOR) $(CFLAGS) -c -o Vector_ll.o math_structures/Vector_ll.cpp
# interpolation.o: math_structures/Interpolator.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o interpolation.o math_structures/Interpolator.cpp
# # -----------------------------------------------------------------------------------


# # visual objects
# # -----------------------------------------------------------------------------------
# visual_base.o: GUI/Visual_object_base.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o visual_base.o GUI/Visual_object_base.cpp

# button.o: GUI/Button.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o button.o GUI/Button.cpp

# button_manager.o: GUI/Button_manager.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o button_manager.o GUI/Button_manager.cpp

# spline.o: GUI/Spline.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o spline.o GUI/Spline.cpp

# slider.o: GUI/Slider.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o slider.o GUI/Slider.cpp

# input_string.o: GUI/Input_string.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o input_string.o GUI/Input_string.cpp

# resource_manager.o: GUI/Resource_manager.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o resource_manager.o GUI/Resource_manager.cpp

# animations.o: GUI/Animations.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o animations.o GUI/Animations.cpp
# # -----------------------------------------------------------------------------------

# # tools
# # -----------------------------------------------------------------------------------
# toolbar.o: Tools/Toolbar.cpp 
# 	$(COMPILATOR) $(CFLAGS) -c -o toolbar.o Tools/Toolbar.cpp

# # editor part
# # -----------------------------------------------------------------------------------
# # Editor/%.o: Editor/%.cpp
# # 	$(COMPILATOR) $(CFLAGS) -c -o canvas Editor/Canvas.cpp
# app.o: Editor/Application.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o app.o Editor/Application.cpp

# canvas.o: Editor/Canvas.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o canvas.o Editor/Canvas.cpp

# tab.o: Editor/Tab.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o tab.o Editor/Tab.cpp

# editor_delegate.o: Editor/Editor_delegates.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o editor_delegate.o Editor/Editor_delegates.cpp

# graphical_delegate.o: Editor/Graphical_delegates.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o graphical_delegate.o Editor/Graphical_delegates.cpp

# palette.o: Editor/Palette.cpp 
# 	$(COMPILATOR) $(CFLAGS) -c -o palette.o Editor/Palette.cpp

# gradient_bar.o: Editor/Gradient_bar.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o gradient_bar.o Editor/Gradient_bar.cpp

# color_picker.o: Editor/Color_picker.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o color_picker.o Editor/Color_picker.cpp

# color_selection.o: Editor/Color_selection.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o color_selection.o Editor/Color_selection.cpp

# canvas_manager.o: Editor/Canvas_manager.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o canvas_manager.o Editor/Canvas_manager.cpp

# canvas_mm.o: Editor/Canvas_manager_manager.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o canvas_mm.o Editor/Canvas_manager_manager.cpp

# window_control_panel.o: Editor/Window_control_panel.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o window_control_panel.o Editor/Window_control_panel.cpp

# graphical_editor.o: Editor/Graphical_editor_main_page.cpp
# 	$(COMPILATOR) $(CFLAGS) -c -o graphical_editor.o Editor/Graphical_editor_main_page.cpp
# # -----------------------------------------------------------------------------------

# clean: 
# 	rm *.o

# run: link
# 	./main

# valgrind: link
# 	valgrind --leak-check=full ./main
