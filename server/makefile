TARGET_EXEC := cpter_server

BUILD_DIR := ./build
SRC_DIRS := ./src

SRCS := server.c

$(BUILD_DIR)/$(TARGET_EXEC): $(SRC_DIRS)/$(SRCS)
	gcc $(SRC_DIRS)/$(SRCS) -o $@
	echo "[ OK ]"

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)