CXX = clang++
CXXFLAGS = -std=c++17 -fPIC
INCLUDES = -I/Users/nicolas/Documents/ProjectAliex/godot-cpp/gen/include \
           -I/Users/nicolas/Documents/ProjectAliex/godot-cpp/include \
           -I/Users/nicolas/Documents/ProjectAliex/godot-cpp/include/core \
           -I/Users/nicolas/Documents/ProjectAliex/godot-cpp/include/gen \
           -I/Users/nicolas/Documents/ProjectAliex/godot-cpp/gdextension
LDFLAGS = -L/Users/nicolas/Documents/ProjectAliex/godot-cpp/bin -lgodot-cpp.macos.template_debug.arm64
TARGET = test/test_droplet
SRCS = test/test_droplet.cpp src/droplet.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TARGET) $(SRCS) $(LDFLAGS)

clean:
	rm -f $(TARGET)