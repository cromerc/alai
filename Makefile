# This makefile is used to compile the project
SHELL := /bin/bash
PROCS := $(shell nproc)
USE_LLVM := "yes"
RELEASE_TYPE := "debug"

all: godot-cpp game docs

linux: game-linux

# Only needs to be run once after cloning
init:
	pushd godot-cpp; git submodule update --init --recursive

# This needs to be run to create all the libraries for godot-cpp
godot-cpp: godot-cpp-linux godot-cpp-windows

godot-cpp-linux:
	pushd godot-cpp; scons use_llvm=$(USE_LLVM) target=$(RELEASE_TYPE) platform=linux generate_bindings=yes bits=64 -j $(PROCS)

godot-cpp-windows:
	pushd godot-cpp; scons target=$(RELEASE_TYPE) platform=windows generate_bindings=yes bits=64 -j $(PROCS)

game: game-linux game-windows

game-linux:
	scons use_llvm=$(USE_LLVM) target=$(RELEASE_TYPE) target_path=godot/gdnative/ target_name=libalai platform=linux bits=64 -j $(PROCS)

game-windows:
	scons target=$(RELEASE_TYPE) target_name=libalai target_path=godot/gdnative/ platform=windows bits=64 -j $(PROCS)

docs:
# if doxygen and bear are installed create the code documentation
ifneq (, $(shell which bear))
ifeq (, $(wildcard ./compile_commands.json))
	$(MAKE) clean-docs
	$(MAKE) bear
endif
ifneq (, $(shell which doxygen))
	doxygen doxygen.conf
	make -C docs/latex
endif
endif

bear:
	bear make linux

clean: clean-godot-cpp clean-game clean-docs

clean-godot-cpp:
	pushd godot-cpp; scons -c
	rm -f godot-cpp/bin/*

clean-game:
	find ./src -name "*.os" -type f -delete
	rm -rf gdnative/{linux,windows}.*	

clean-docs:
	rm -rf docs
	rm -rf compile_commands.json

.PHONY: all linux init godot-cpp godot-cpp-linux godot-cpp-windows game game-linux game-windows clean clean-godot-cpp clean-game clean-docs clean-docs docs bear
