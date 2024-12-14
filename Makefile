BUILD_DIR = build

all: $(BUILD_DIR)/supermarket $(BUILD_DIR)/firefighter $(BUILD_DIR)/client $(BUILD_DIR)/manager

$(BUILD_DIR):
		mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/supermarket: $(BUILD_DIR)/supermarket.o $(BUILD_DIR)/semaphores.o | $(BUILD_DIR)
		gcc -o $(BUILD_DIR)/supermarket $(BUILD_DIR)/supermarket.o $(BUILD_DIR)/semaphores.o

$(BUILD_DIR)/supermarket.o: supermarket.c semaphores.h | $(BUILD_DIR)
		gcc -c supermarket.c -o $(BUILD_DIR)/supermarket.o

$(BUILD_DIR)/semaphores.o: semaphores.c | $(BUILD_DIR)
		gcc -c semaphores.c -o $(BUILD_DIR)/semaphores.o

$(BUILD_DIR)/firefighter: $(BUILD_DIR)/firefighter.o $(BUILD_DIR)/semaphores.o | $(BUILD_DIR)
		gcc -o $(BUILD_DIR)/firefighter $(BUILD_DIR)/firefighter.o $(BUILD_DIR)/semaphores.o

$(BUILD_DIR)/firefighter.o: firefighter.c | $(BUILD_DIR)
		gcc -c firefighter.c -o $(BUILD_DIR)/firefighter.o

$(BUILD_DIR)/client: $(BUILD_DIR)/client.o $(BUILD_DIR)/semaphores.o | $(BUILD_DIR)
		gcc -o $(BUILD_DIR)/client $(BUILD_DIR)/client.o $(BUILD_DIR)/semaphores.o

$(BUILD_DIR)/client.o: client.c | $(BUILD_DIR)
		gcc -c client.c -o $(BUILD_DIR)/client.o

$(BUILD_DIR)/manager: $(BUILD_DIR)/manager.o $(BUILD_DIR)/semaphores.o | $(BUILD_DIR)
		gcc -o $(BUILD_DIR)/manager $(BUILD_DIR)/manager.o $(BUILD_DIR)/semaphores.o

$(BUILD_DIR)/manager.o: manager.c | $(BUILD_DIR)
		gcc -c manager.c -o $(BUILD_DIR)/manager.o

clean:
		rm -rf $(BUILD_DIR)