# Makefile for Keylogger Project - Windows MSVC
# This Makefile builds a Windows keylogger in C using Visual C++

# Compiler and flags
CC = cl.exe
CFLAGS = /Zi /EHsc /nologo
LDFLAGS = user32.lib kernel32.lib

# Directories
SRC_DIR = Keylogger

# Files
TARGET = $(SRC_DIR)\main.exe

# Default target
all: $(TARGET)

# Build executable
$(TARGET):
	cd $(SRC_DIR) && $(CC) $(CFLAGS) "/Fe:main.exe" main.c keyLogger.c $(LDFLAGS)
	@echo Build complete: $(TARGET)

# Rebuild from scratch
rebuild:
	cd $(SRC_DIR) && del *.exe *.obj *.pdb *.ilk 2>nul || true
	$(MAKE) all

# Clean build artifacts
clean:
	cd $(SRC_DIR) && del *.exe *.obj *.pdb *.ilk 2>nul || true
	@echo Cleaned build artifacts

# Run the executable
run: $(TARGET)
	.\$(TARGET)

# Display help
help:
	@echo   Keylogger Makefile Targets:
	@echo   make all       - Build the keylogger executable (default)
	@echo   make clean     - Remove all build artifacts
	@echo   make rebuild   - Clean and rebuild from scratch
	@echo   make run       - Build and run the keylogger
	@echo   make help      - Display this help message

.PHONY: all clean clean-obj rebuild run help
