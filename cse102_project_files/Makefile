CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

SRC_DIR = src

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/student.c \
       $(SRC_DIR)/course.c \
       $(SRC_DIR)/professor.c \
       $(SRC_DIR)/enrollment.c \
       $(SRC_DIR)/grade.c \
       $(SRC_DIR)/menu.c \
       $(SRC_DIR)/utils.c

OBJS = $(SRCS:.c=.o)

TARGET = student_system

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Compile source files in src/
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean generated files
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

