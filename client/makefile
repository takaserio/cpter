TARGET_EXEC := cpter_client

BUILD_DIR := ./build
SRC_DIRS := ./src

SRCS := client.c

$(BUILD_DIR)/$(TARGET_EXEC): $(SRC_DIRS)/$(SRCS)
	gcc $(SRC_DIRS)/$(SRCS) -o $@
	echo "[ ok ]"