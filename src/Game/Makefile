COMPILER = g++

#GAME
GAME_PATH = .
GAME_ENTITIES = Main Logger Game SFMLGame Loader ResourceManager GameObject Transform MovementScript
GAME_CPP = $(foreach e, $(GAME_ENTITIES), $(GAME_PATH)/$(e).cpp)
GAME_OBJS = $(foreach e, $(GAME_ENTITIES), $(e).o)

#GUI
GUI_PATH = ./GUI
GUI_ENTITIES = Label LabelElement Drawable
GUI_CPP = $(foreach e, $(GUI_ENTITIES), $(GUI_PATH)/$(e).cpp)
GUI_OBJS = $(foreach e, $(GUI_ENTITIES), $(e).o)

#Rendering
RENDERING_PATH = ./Rendering
RENDERING_ENTITIES = Camera Renderer SpriteRenderer CircleRenderer
RENDERING_CPP = $(foreach e, $(RENDERING_ENTITIES), $(RENDERING_PATH)/$(e).cpp)
RENDERING_OBJS = $(foreach e, $(RENDERING_ENTITIES), $(e).o)

# Physics
PHYSICS_PATH = ./Physics
PHYSICS_ENTITIES = PhysicsSubsystem PhysicsBody BoxCollider
PHYSICS_CPP = $(foreach e, $(PHYSICS_ENTITIES), $(PHYSICS_PATH)/$(e).cpp)
PHYSICS_OBJS = $(foreach e, $(PHYSICS_ENTITIES), $(e).o)

# Box2D
BOX2D_INCLUDE_PATH = Box2D_v2.3.0/Box2D
BOX2D_LINK_PATH = Box2D_v2.3.0/Box2D/Box2D

OUTPUT_PATH = ./Build

COMPILER_FLAGS = -std=c++11

OUTPUT = output

LINKER_FLAGS = -lsfml-system -lsfml-graphics -lsfml-window -lBox2D

DEFINE = ENABLE_LOG DEBUG_PRINT

# Total
OBJS = $(GAME_OBJS) $(PHYSICS_OBJS) $(RENDERING_OBJS) $(GUI_OBJS)
INCLUDE_PATHS = $(PHYSICS_PATH)/include $(RENDERING_PATH)/include $(GUI_PATH)/include $(BOX2D_INCLUDE_PATH) ./include
LINK_PATHS = $(BOX2D_LINK_PATH)

all : $(foreach o, $(GAME_OBJS), $(OUTPUT_PATH)/$(GAME_PATH)/$(o)) \
$(foreach o, $(PHYSICS_PATH), $(OUTPUT_PATH)/$(PHYSICS_PATH)/$(o)) \
$(foreach o, $(RENDERING_PATH), $(OUTPUT_PATH)/$(RENDERING_PATH)/$(o))\
$(foreach o, $(GUI_PATH), $(OUTPUT_PATH)/$(GUI_PATH)/$(o))
	$(COMPILER) $(foreach o, $(OBJS), $(OUTPUT_PATH)/$(o)) $(COMPILER_FLAGS) $(foreach p, $(LINK_PATHS),-L$(p)) $(LINKER_FLAGS) -o $(OUTPUT_PATH)/$(OUTPUT) #$(foreach s, $(DEFINE),-D $(s))

run : ./$(OUTPUT_PATH)/$(OUTPUT)
	./$(OUTPUT_PATH)/$(OUTPUT)

$(OUTPUT_PATH)/$(GAME_PATH)/%.o : $(GAME_PATH)/%.cpp
	$(COMPILER) $(foreach p, $(INCLUDE_PATHS),-I $(p)) -c $< $(COMPILER_FLAGS) -o $@ $(foreach s, $(DEFINE),-D $(s))	

$(OUTPUT_PATH)/$(PHYSICS_PATH)/%.o : $(PHYSICS_PATH)/%.cpp
	$(COMPILER) $(foreach p, $(INCLUDE_PATHS),-I $(p)) -c $< $(COMPILER_FLAGS) -o $@ $(foreach s, $(DEFINE),-D $(s))

$(OUTPUT_PATH)/$(RENDERING_PATH)/%.o : $(RENDERING_PATH)/%.cpp
	$(COMPILER) $(foreach p, $(INCLUDE_PATHS),-I $(p)) -c $< $(COMPILER_FLAGS) -o $@ $(foreach s, $(DEFINE),-D $(s))

$(OUTPUT_PATH)/$(GUI_PATH)/%.o : $(GUI_PATH)/%.cpp
	$(COMPILER) $(foreach p, $(INCLUDE_PATHS),-I $(p)) -c $< $(COMPILER_FLAGS) -o $@ $(foreach s, $(DEFINE),-D $(s))	