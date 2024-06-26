# # make file to easily compile the emotion-check
# CC=g++
# LIB_DIR=/usr/lib/x86_64-linux-gnu
# LIBS = -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio -lopencv_video
# INCLUDE_DIR=/usr/include/opencv4
#
# SRC=main.cpp
# OUT=emotion-check
#
# build:
# 	$(CC) $(SRC) -I$(INCLUDE_DIR) -L$(LIB_DIR) $(LIBS) -o $(OUT)
# 	./$(OUT)
#
# clean:
# 	rm -f $(OUT)
#
# .PHONY: build clean
#
#
# # Compiler
# CC=g++
#
# # Compiler flags
# CFLAGS=-std=c++11 -I/usr/local/include -I/usr/include/opencv4
# LDFLAGS=-L/usr/local/lib -ldlib -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lpng -lcblas -llapack
# # Target executable
# TARGET=emotion-check
#
# # Source files
# SRCS=try.cpp
#
# # Object files
# OBJS=$(SRCS:.cpp=.o)
#
# # Build target
# $(TARGET): $(OBJS)
# 	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)
#
# # Compile source files to object files
# %.o: %.cpp
# 	$(CC) $(CFLAGS) -c $< -o $@
#
# # Clean up build files
# clean:
# 	rm -f $(OBJS) $(TARGET)
#
# # Phony targets
# .PHONY: all clean
#


# # Compiler
# CXX = g++
#
# # Compiler flags
# CXXFLAGS = -std=c++11 `pkg-config --cflags opencv4`
# LDFLAGS = `pkg-config --libs opencv4` -ldlib
#
# # Target executable
# TARGET = emotion_check
#
# # Source files
# SRCS = try1.cpp
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

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -msse2 `pkg-config --cflags opencv4 dlib-1`
LDFLAGS = `pkg-config --libs opencv4 dlib-1`

# Target executable
TARGET = face_landmark_detection

# Source files
SRCS = try1.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Rule to link the target executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

