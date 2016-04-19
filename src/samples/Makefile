# Makefile for the paho-mqttpp (C++) sample applications

ifndef VERBOSE
  QUIET := @
endif

ifdef DEVELOP
  PAHO_C_LIB_DIR ?= $(abspath ../../../paho.mqtt.c)/build/output
  PAHO_C_INC_DIR ?= $(abspath ../../../paho.mqtt.c)/src
else
  PAHO_C_LIB_DIR ?= /usr/local/lib
  PAHO_C_INC_DIR ?= /usr/local/include
endif

SAMPLES = async_publish async_subscribe sync_publish paho_cpp_sub paho_cpp_pub

all: $(SAMPLES)

ifneq ($(CROSS_COMPILE),)
  CC  = $(CROSS_COMPILE)gcc
  CXX = $(CROSS_COMPILE)g++
  AR  = $(CROSS_COMPILE)ar
  LD  = $(CROSS_COMPILE)ld
endif

CXXFLAGS += -Wall -std=c++11
CPPFLAGS += -I.. -I$(PAHO_C_INC_DIR)

ifdef DEBUG
  CPPFLAGS += -DDEBUG
  CXXFLAGS += -g -O0
else
  CPPFLAGS += -D_NDEBUG
  CXXFLAGS += -O2
endif

LDLIBS += -L../../lib -L$(PAHO_C_LIB_DIR) -lpaho-mqttpp3 -lpaho-mqtt3a

async_publish: async_publish.cpp
	$(QUIET) $(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $< $(LDLIBS)

async_subscribe: async_subscribe.cpp
	$(QUIET) $(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $< $(LDLIBS)

sync_publish: sync_publish.cpp
	$(QUIET) $(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $< $(LDLIBS)

paho_cpp_sub: paho_cpp_sub.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $< $(LDLIBS)

paho_cpp_pub: paho_cpp_pub.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $< $(LDLIBS)

.PHONY: clean distclean

clean:
	$(QUIET) $(RM) $(SAMPLES)

distclean: clean


