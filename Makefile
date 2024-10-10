# Project Name
TARGET = ccam_vco

# Sources
CPP_SOURCES = main.cpp

# Library Locations
LIBDAISY_DIR = libDaisy
DAISYSP_DIR = DaisySP

CPP_STANDARD = -std=gnu++20
APP_TYPE = BOOT_SRAM

BOARD ?= earth

earth: board.h
	$(MAKE) all

board.h: $(JSON_FILE)
	python -m headergen $(BOARD)

# Core location, and generic Makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile