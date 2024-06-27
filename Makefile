# Compiler
CC=g++

# Compiler flags
CFLAGS=-std=c++11 -O3 -I/usr/local/include -I/usr/include/opencv4
LDFLAGS=-L/usr/local/lib -ldlib -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lpng -lcblas -llapack -lgif -lopencv_videoio
# Target executable
TARGET=emotion-check

# Source files
SRCS=try3.cpp

# Object files
OBJS=$(SRCS:.cpp=.o)

# Build target
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile source files to object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean


#
# # Compiler
# CXX = g++
#
# # Compiler flags
# CXXFLAGS = -std=c++11 `pkg-config --cflags opencv4 `
# LDFLAGS = `pkg-config --libs opencv4` -ldlib -lcblas -llapack
## LDFLAGS = `pkg-config --libs opencv4 dlib-1`
# # Target executable
# TARGET = emotion_check
#
# # Source files
# SRCS = main.cpp
#
# # Object files
# OBJS = $(SRCS:.cpp=.o)
#
# # Build target
# all: $(TARGET)
#
# # Link
# $(TARGET): $(OBJS)
# 	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)
#
# # Compile
# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@
#
# # Clean
# clean:
# 	rm -f $(TARGET) $(OBJS)


