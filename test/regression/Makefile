# Makefile for the paho-mqttpp (C++) unit tests

ifdef DEVELOP
  PAHO_CPP_LIB_DIR ?= $(abspath ../..)/lib
  PAHO_C_LIB_DIR ?= $(abspath ../../../paho.mqtt.c)/build/output
  PAHO_C_INC_DIR ?= $(abspath ../../../paho.mqtt.c)/src
else
  PAHO_CPP_LIB_DIR ?= /usr/local/lib
  PAHO_C_LIB_DIR ?= /usr/local/lib
  PAHO_C_INC_DIR ?= /usr/local/include
endif

.PHONY: all
all: $(TGT) run

ifneq ($(CROSS_COMPILE),)
  CC  = $(CROSS_COMPILE)gcc
  CXX = $(CROSS_COMPILE)g++
  AR  = $(CROSS_COMPILE)ar
  LD  = $(CROSS_COMPILE)ld
endif

CXXFLAGS += -Wall -std=c++11
CPPFLAGS += -I../../src -I$(PAHO_C_INC_DIR)

ifdef DEBUG
  CPPFLAGS += -DDEBUG
  CXXFLAGS += -g -O0
else
  CPPFLAGS += -D_NDEBUG
  CXXFLAGS += -O2
endif

LDLIBS += -L$(PAHO_CPP_LIB_DIR) -L$(PAHO_C_LIB_DIR) -lpaho-mqttpp3 -lpaho-mqtt3a -lcppunit -ldl

.PHONY: test_async_publish
test_async_publish: test_async_publish.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $< $(LDLIBS)
	LD_LIBRARY_PATH=$(PAHO_C_LIB_DIR):$(PAHO_CPP_LIB_DIR) ./$@

.PHONY: test_async_subscribe
test_async_subscribe: test_async_subscribe.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $< $(LDLIBS)
	LD_LIBRARY_PATH=$(PAHO_C_LIB_DIR):$(PAHO_CPP_LIB_DIR) ./$@

run: test_async_publish test_async_subscribe

.PHONY: clean
clean:
	rm -f $(TGT)

.PHONY: distclean
distclean: clean

.PHONY: dump
dump:
	@echo CXX: $(CXX)
	@echo Tests: $(HDR_TESTS)
