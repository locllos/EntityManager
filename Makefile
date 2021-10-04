MAIN_DIR = src
OBJ_DIR = bin
EXEC = g++
MAIN_FLAGS = -g3 -lSDL2_image -lSDL2_ttf `sdl2-config --cflags --libs`
OBJ_FLAGS = -c -g3
EXEC_NAME = entity_master
SUCCESS_MESSAGE = Success!

simple: 
	$(EXEC) $(MAIN_DIR)/main.cpp $(OBJ_DIR)/display.o $(OBJ_DIR)/field.o $(OBJ_DIR)/coordinate_system.o $(OBJ_DIR)/vector.o $(OBJ_DIR)/filled_circle.o $(OBJ_DIR)/entity_manager.o $(OBJ_DIR)/entity.o $(OBJ_DIR)/collision_processor.o $(OBJ_DIR)/physical_circle.o $(OBJ_DIR)/component_connector.o $(OBJ_DIR)/filled_square.o $(OBJ_DIR)/command.o $(OBJ_DIR)/button.o $(OBJ_DIR)/button_manager.o $(OBJ_DIR)/dynamic_graphic.o $(MAIN_FLAGS) -o $(EXEC_NAME)

main: $(OBJ_DIR)/display.o $(OBJ_DIR)/field.o $(OBJ_DIR)/coordinate_system.o $(OBJ_DIR)/vector.o $(OBJ_DIR)/filled_circle.o $(OBJ_DIR)/entity_manager.o $(OBJ_DIR)/entity.o $(OBJ_DIR)/collision_processor.o $(OBJ_DIR)/physical_circle.o $(OBJ_DIR)/component_connector.o $(OBJ_DIR)/filled_square.o $(OBJ_DIR)/command.o $(OBJ_DIR)/button.o $(OBJ_DIR)/button_manager.o $(OBJ_DIR)/dynamic_graphic.o
	$(EXEC) $(MAIN_DIR)/main.cpp $(OBJ_DIR)/display.o $(OBJ_DIR)/field.o $(OBJ_DIR)/coordinate_system.o $(OBJ_DIR)/vector.o $(OBJ_DIR)/filled_circle.o $(OBJ_DIR)/entity_manager.o $(OBJ_DIR)/entity.o $(OBJ_DIR)/collision_processor.o $(OBJ_DIR)/physical_circle.o $(OBJ_DIR)/component_connector.o $(OBJ_DIR)/filled_square.o $(OBJ_DIR)/command.o $(OBJ_DIR)/button.o $(OBJ_DIR)/button_manager.o $(OBJ_DIR)/dynamic_graphic.o $(MAIN_FLAGS) -o $(EXEC_NAME)

$(OBJ_DIR)/display.o:
	$(EXEC) $(OBJ_FLAGS) $(MAIN_DIR)/display.cpp -o $(OBJ_DIR)/display.o

$(OBJ_DIR)/field.o:
	$(EXEC) $(OBJ_FLAGS) $(MAIN_DIR)/field.cpp -o $(OBJ_DIR)/field.o

$(OBJ_DIR)/coordinate_system.o:
	$(EXEC) $(OBJ_FLAGS) $(MAIN_DIR)/coordinate_system.cpp -o $(OBJ_DIR)/coordinate_system.o

$(OBJ_DIR)/vector.o:
	$(EXEC) $(OBJ_FLAGS) $(MAIN_DIR)/vector.cpp -o $(OBJ_DIR)/vector.o

$(OBJ_DIR)/filled_circle.o:
	$(EXEC) $(OBJ_FLAGS) $(MAIN_DIR)/filled_circle.cpp -o $(OBJ_DIR)/filled_circle.o

$(OBJ_DIR)/entity_manager.o:
	$(EXEC) $(OBJ_FLAGS) $(MAIN_DIR)/entity_manager.cpp -o $(OBJ_DIR)/entity_manager.o

$(OBJ_DIR)/entity.o:
	$(EXEC) $(OBJ_FLAGS) $(MAIN_DIR)/entity.cpp -o $(OBJ_DIR)/entity.o

$(OBJ_DIR)/collision_processor.o:
	$(EXEC) $(OBJ_FLAGS) $(MAIN_DIR)/collision_processor.cpp -o $(OBJ_DIR)/collision_processor.o

$(OBJ_DIR)/physical_circle.o:
	$(EXEC) $(OBJ_FLAGS) $(MAIN_DIR)/physical_circle.cpp -o $(OBJ_DIR)/physical_circle.o

$(OBJ_DIR)/component_connector.o:
	$(EXEC) $(OBJ_FLAGS) $(MAIN_DIR)/component_connector.cpp -o $(OBJ_DIR)/component_connector.o

$(OBJ_DIR)/filled_square.o:
	$(EXEC) $(OBJ_FLAGS) $(MAIN_DIR)/filled_square.cpp -o $(OBJ_DIR)/filled_square.o

$(OBJ_DIR)/command.o:
	$(EXEC) $(OBJ_FLAGS) $(MAIN_DIR)/command.cpp -o $(OBJ_DIR)/command.o

$(OBJ_DIR)/button.o:
	$(EXEC) $(OBJ_FLAGS) $(MAIN_DIR)/button.cpp -o $(OBJ_DIR)/button.o

$(OBJ_DIR)/button_manager.o:
	$(EXEC) $(OBJ_FLAGS) $(MAIN_DIR)/button_manager.cpp -o $(OBJ_DIR)/button_manager.o

$(OBJ_DIR)/dynamic_graphic.o:
	$(EXEC) $(OBJ_FLAGS) $(MAIN_DIR)/dynamic_graphic.cpp -o $(OBJ_DIR)/dynamic_graphic.o

# $(OBJ_DIR)/list.o:
# 	$(EXEC) $(OBJ_FLAGS) $(MAIN_DIR)/hdr/list.hpp -o $(OBJ_DIR)/list.o

all: clear main 
	echo -e "\033[0;32m$(SUCCESS_MESSAGE)\033[0m"

clear:
	rm -r $(OBJ_DIR)/*.o