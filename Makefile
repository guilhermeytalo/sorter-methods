CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99
SRC_DIR = src
BUILD_DIR = build
RESULTS_DIR = results

SOURCES = $(SRC_DIR)/sorting.c $(SRC_DIR)/experiment.c
OBJECTS = $(BUILD_DIR)/sorting.o $(BUILD_DIR)/experiment.o
TARGET = $(BUILD_DIR)/experiment

.PHONY: all clean run

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(RESULTS_DIR):
	mkdir -p $(RESULTS_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

run: $(TARGET) | $(RESULTS_DIR)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(RESULTS_DIR)

help:
	@echo "Sorting Algorithm Analysis - Makefile"
	@echo ""
	@echo "Targets:"
	@echo "  make          - Build the experiment"
	@echo "  make run      - Build and run the experiment"
	@echo "  make clean    - Remove build files and results"
	@echo "  make help     - Show this help message"
