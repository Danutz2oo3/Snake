# Get a list of all .cpp files in the current directory
SOURCES := $(wildcard *.cpp)

# Specify the target executable name
TARGET := main

# Specify include and library directories
INCLUDE_DIRS := -I src/include
LIBRARY_DIRS := -L src/lib

# Specify libraries to link against
LIBRARIES := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

# Build rule for the target executable
$(TARGET): $(SOURCES)
	g++ $(INCLUDE_DIRS) $(LIBRARY_DIRS) -o $@ $^ $(LIBRARIES)

# Clean rule to remove the target executable
clean:
	rm -f $(TARGET)
