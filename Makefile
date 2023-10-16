
LIBRARY_NAME = PololuDualG2HighPowerMotorShield

# Build path -- used to store built binary and object files
BUILD_DIR ?= build

WIN_LIBRARY_PATH = /mnt/c/Users/steve/Documents/Arduino/libraries

.PHONY: all clean install-win install-winlib uninstall-lib zip

all: 

clean:
	@rm -rf $(BUILD_DIR)
	@rm $(BUILD_DIR)/*.elf
	@rm $(BUILD_DIR)/*.hex

install-winlib:
	unzip $(BUILD_DIR)/$(LIBRARY_NAME).zip -d $(WIN_LIBRARY_PATH)

uninstall-winlib:
	rm -r $(WIN_LIBRARY_PATH)/$(LIBRARY_NAME)

zip:
	mkdir -p $(BUILD_DIR)
	# ignore the output of rm on the next line
	-rm $(BUILD_DIR)/$(LIBRARY_NAME).zip
	(cd src/ && zip -FSr - $(LIBRARY_NAME)) > $(BUILD_DIR)/$(LIBRARY_NAME).zip

install-win: zip install-winlib
