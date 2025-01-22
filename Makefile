BUILD_DIR = build

all: $(BUILD_DIR)/supermarket $(BUILD_DIR)/firefighter $(BUILD_DIR)/customer $(BUILD_DIR)/manager

$(BUILD_DIR):
		mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/supermarket: $(BUILD_DIR)/supermarket.o $(BUILD_DIR)/shared.o | $(BUILD_DIR)
		gcc -o $(BUILD_DIR)/supermarket $(BUILD_DIR)/supermarket.o $(BUILD_DIR)/shared.o -lpthread

$(BUILD_DIR)/supermarket.o: supermarket.c supermarket.h ansi-color-codes.h | $(BUILD_DIR)
		gcc -c supermarket.c -o $(BUILD_DIR)/supermarket.o

$(BUILD_DIR)/shared.o: shared.c supermarket.h | $(BUILD_DIR)
		gcc -c shared.c -o $(BUILD_DIR)/shared.o

$(BUILD_DIR)/firefighter: $(BUILD_DIR)/firefighter.o $(BUILD_DIR)/shared.o | $(BUILD_DIR)
		gcc -o $(BUILD_DIR)/firefighter $(BUILD_DIR)/firefighter.o $(BUILD_DIR)/shared.o -lpthread

$(BUILD_DIR)/firefighter.o: firefighter.c supermarket.h | $(BUILD_DIR)
		gcc -c firefighter.c -o $(BUILD_DIR)/firefighter.o

$(BUILD_DIR)/customer: $(BUILD_DIR)/customer.o $(BUILD_DIR)/shared.o | $(BUILD_DIR)
		gcc -o $(BUILD_DIR)/customer $(BUILD_DIR)/customer.o $(BUILD_DIR)/shared.o -lpthread

$(BUILD_DIR)/customer.o: customer.c supermarket.h | $(BUILD_DIR)
		gcc -c customer.c -o $(BUILD_DIR)/customer.o

$(BUILD_DIR)/manager: $(BUILD_DIR)/manager.o $(BUILD_DIR)/shared.o | $(BUILD_DIR)
		gcc -o $(BUILD_DIR)/manager $(BUILD_DIR)/manager.o $(BUILD_DIR)/shared.o -lpthread

$(BUILD_DIR)/manager.o: manager.c supermarket.h | $(BUILD_DIR)
		gcc -c manager.c -o $(BUILD_DIR)/manager.o

clean:
		rm -rf $(BUILD_DIR)