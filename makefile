# ==== Begin: Build options
ARCH := x86-64
ifeq ($(OS), Windows_NT)
SYS := win32
else
SYS := linux
endif
BUILD := debug
COMPILER := clang
# ==== End: Build options

# ==== Begin: Available shell commands
MKDIR := mkdir -p
RM := rm -f
RMDIR := rm -r -f
CP := cp
#MKDIR := mkdir
#RM := del /f /q
#RMDIR := rmdir /s /q
#CP := copy
# ==== End: Available shell commands

# ==== Begin: Derived middle-man options
TRIPLE := $(ARCH)
DIR := $(TRIPLE)_$(BUILD)
# ==== End: Derived middle-man options

# ==== Begin: Input/Output Files/Directories
SRC := ./src
OBJ := ./build/$(DIR)
BIN := ./bin/$(DIR)
TARGET := $(BIN)/Crisp

INC_PATHS.linux := 
LIB_PATHS.linux := 
LIB_FILES.linux := vulkan SDL2 GLEW

INC_PATHS.win32 := C:\Dev\SDL2\include C:\Dev\VulkanSDK\include C:\Dev\glew\include C:\Dev\glm\include C:\Dev\nlohmannJson\include C:\Dev\stb\include C:\Dev\tinyobjloader\include C:\Dev\tinygltf C:\Dev\entt-master\single_include\entt C:\Dev\volk
LIB_PATHS.win32 := C:\Dev\SDL2\lib\$(ARCH) C:\Dev\VulkanSDK\lib\$(ARCH) C:\Dev\glew\lib\$(ARCH)
LIB_FILES.win32 := SDL2 glew32

INC_PATHS := ${INC_PATHS.${SYS}}
LIB_PATHS := ${LIB_PATHS.${SYS}}
LIB_FILES := ${LIB_FILES.${SYS}}
# ==== End: Input/Output Files/Directories

# ==== Begin: Build tools selection
CXX.gcc := g++
CC.gcc := gcc
LD.gcc := g++
AR.gcc := ar

CXX.clang := clang++
CC.clang := clang
LD.clang := clang++
AR.clang := ar

CXX := ${CXX.${COMPILER}}
CC := ${CC.${COMPILER}}
LD := ${LD.${COMPILER}}
AR := ${AR.${COMPILER}}
# ==== End: Build tools selection

# ==== Begin: Compiler flags selection
CCXFLAGS.includes := $(INC_PATHS:%=-I%)

# release flags set to O1 for now (instead O3) while on laptop

CXXFLAGS.gcc.linux := 
CXXFLAGS.gcc.win32 := -D_WIN32
CXXFLAGS.gcc.debug := -O0 -fstack-protector-all -g3 -ggdb
CXXFLAGS.gcc.release := -O1 -march=native -g0 -DNDEBUG
CCXFLAGS.gcc.exclude := -Wno-unused-variable -Wno-unused-parameter -Wno-unused-but-set-variable -Wno-ignored-attributes
CXXFLAGS.gcc := -pthread -std=gnu++2a -fmessage-length=0 ${CXXFLAGS.gcc.${BUILD}} ${CXXFLAGS.gcc.${SYS}}

CXXFLAGS.clang.linux := 
CXXFLAGS.clang.win32 := -D_WIN32
CXXFLAGS.clang.debug := -O0 -fstack-protector-all -g3 -ggdb
CXXFLAGS.clang.release := -O1 -march=native -g0 -DNDEBUG 
CCXFLAGS.clang.exclude := -Wno-unused-variable -Wno-unused-parameter -Wno-unused-private-field -Wno-ignored-attributes -Wno-language-extension-token
CXXFLAGS.clang := -pthread -std=gnu++2a -fmessage-length=0 ${CXXFLAGS.clang.${BUILD}} ${CXXFLAGS.clang.${SYS}}

CCXFLAGS.warning := -Wall -Wextra -pedantic ${CCXFLAGS.${COMPILER}.exclude} -Werror

CXXFLAGS := ${CXXFLAGS.${COMPILER}} ${CCXFLAGS.includes} ${CCXFLAGS.warning}
# ==== End: Compiler flags selection

# ==== Begin: Linker flags selection

LDFLAGS.libraries := $(LIB_PATHS:%=-L%) $(LIB_FILES:%=-l%)

LDFLAGS.gcc.linux := -pthread
LDFLAGS.gcc.win32 := 
LDFLAGS.gcc.debug := -fstack-protector -O0
LDFLAGS.gcc.release := 
LDFLAGS.gcc := ${LDFLAGS.gcc.${SYS}} ${LDFLAGS.gcc.${BUILD}} #-fuse-ld=gold

LDFLAGS.clang.linux := -pthread
LDFLAGS.clang.win32 := 
LDFLAGS.clang.debug := -fstack-protector -O0
LDFLAGS.clang.release := 
LDFLAGS.clang := ${LDFLAGS.clang.${SYS}} ${LDFLAGS.clang.${BUILD}} -fuse-ld=lld

LDFLAGS := -g ${LDFLAGS.${COMPILER}} ${LDFLAGS.libraries}
# ==== End: Linker flags selection

SRCS := $(wildcard $(SRC)/*.cpp) $(wildcard $(SRC)/**/*.cpp) $(wildcard $(SRC)/**/**/*.cpp)
OBJS := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRCS))
DEPS := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.d,$(SRCS))

default: $(SYS)

$(TARGET): $(OBJS) | $(BIN)
	$(LD) $^ -o $@ $(LDFLAGS)

-include $(DEPS)

$(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ)/*/
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(BIN) $(OBJ):
	$(MKDIR) "$@"

$(OBJ)/%/:
	$(MKDIR) "$@"

linux: $(TARGET)
win32: $(TARGET) dlls

dlls:
	$(CP) "C:\Dev\SDL2\lib\$(ARCH)\SDL2.dll" $(BIN)

run: 
	$(TARGET)

clean:
	$(RM) gmon.out
	$(RMDIR) $(BIN) $(OBJ)
	$(MKDIR) $(OBJ)/engine/packages $(OBJ)/engine/vulkan $(OBJ)/engine/opengl $(OBJ)/game

.PHONY: run clean default linux win32 dlls