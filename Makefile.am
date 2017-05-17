#*******************************************************************************
#  Copyright (c) 2016
#
#  All rights reserved. This program and the accompanying materials
#  are made available under the terms of the Eclipse Public License v1.0
#  and Eclipse Distribution License v1.0 which accompany this distribution.
#
#  The Eclipse Public License is available at
#     http://www.eclipse.org/legal/epl-v10.html
#  and the Eclipse Distribution License is available at
#    http://www.eclipse.org/org/documents/edl-v10.php.
#
#  Contributors:
#     Guilherme Maciel Ferreira - initial contribuition
#*******************************************************************************/

AUTOMAKE_OPTIONS = subdir-objects color-tests
ACLOCAL_AMFLAGS = -I m4

###############################################################################
# Library: name
###############################################################################

lib_LTLIBRARIES  = libpaho-mqttpp3.la

###############################################################################
# Library: source code
###############################################################################

libpaho_mqttpp3_la_SOURCES  = src/async_client.cpp
libpaho_mqttpp3_la_SOURCES += src/client.cpp
libpaho_mqttpp3_la_SOURCES += src/connect_options.cpp
libpaho_mqttpp3_la_SOURCES += src/disconnect_options.cpp
libpaho_mqttpp3_la_SOURCES += src/iclient_persistence.cpp
libpaho_mqttpp3_la_SOURCES += src/message.cpp
libpaho_mqttpp3_la_SOURCES += src/response_options.cpp
libpaho_mqttpp3_la_SOURCES += src/string_collection.cpp
libpaho_mqttpp3_la_SOURCES += src/token.cpp
libpaho_mqttpp3_la_SOURCES += src/topic.cpp
libpaho_mqttpp3_la_SOURCES += src/will_options.cpp
libpaho_mqttpp3_la_SOURCES += src/ssl_options.cpp


###############################################################################
# Library: proprocessor flags
###############################################################################

COMMONCPPFLAGS  = $(AM_CPPFLAGS)
if PAHO_WITH_SSL
COMMONCPPFLAGS += -DOPENSSL
endif

libpaho_mqttpp3_la_CPPFLAGS  = $(COMMONCPPFLAGS)

###############################################################################
# Library: compiler flags
###############################################################################

libpaho_mqttpp3_la_CXXFLAGS  = $(CXXFLAGS)
libpaho_mqttpp3_la_CXXFLAGS += -fPIC
libpaho_mqttpp3_la_CXXFLAGS += -I $(srcdir)/src -I src

###############################################################################
# Library: linker flags
###############################################################################

# Create SONAME entry. Same as -Wl,-soname,libname.so.major
VERSION_INFO = `echo '$(PACKAGE_VERSION)' | $(SED) -e "s/\(.*\)\.\(.*\\)\.\(.*\)/\1:\3:\2/g" `
libpaho_mqttpp3_la_LDFLAGS  = -version-info $(VERSION_INFO)

libpaho_mqttpp3_la_LDFLAGS += $(LDFLAGS)
libpaho_mqttpp3_la_LDFLAGS += $(LIBS)


###############################################################################
# Library: headers to install
###############################################################################

pkgincludedir = $(includedir)/mqtt

pkginclude_HEADERS  = src/mqtt/async_client.h
pkginclude_HEADERS += src/mqtt/buffer_ref.h
pkginclude_HEADERS += src/mqtt/buffer_view.h
pkginclude_HEADERS += src/mqtt/callback.h
pkginclude_HEADERS += src/mqtt/client.h
pkginclude_HEADERS += src/mqtt/connect_options.h
pkginclude_HEADERS += src/mqtt/delivery_token.h
pkginclude_HEADERS += src/mqtt/disconnect_options.h
pkginclude_HEADERS += src/mqtt/exception.h
pkginclude_HEADERS += src/mqtt/iaction_listener.h
pkginclude_HEADERS += src/mqtt/iasync_client.h
pkginclude_HEADERS += src/mqtt/iclient_persistence.h
pkginclude_HEADERS += src/mqtt/message.h
pkginclude_HEADERS += src/mqtt/response_options.h
pkginclude_HEADERS += src/mqtt/thread_queue.h
pkginclude_HEADERS += src/mqtt/token.h
pkginclude_HEADERS += src/mqtt/topic.h
pkginclude_HEADERS += src/mqtt/string_collection.h
pkginclude_HEADERS += src/mqtt/types.h
pkginclude_HEADERS += src/mqtt/will_options.h
pkginclude_HEADERS += src/mqtt/ssl_options.h


###############################################################################
# Samples
###############################################################################

if PAHO_BUILD_SAMPLES

###############################################################################
# Samples: names
###############################################################################

bin_PROGRAMS  = async_publish
bin_PROGRAMS += async_subscribe
bin_PROGRAMS += async_consume
bin_PROGRAMS += sync_publish
bin_PROGRAMS += sync_consume
bin_PROGRAMS += data_publish
bin_PROGRAMS += pub_speed_test

if PAHO_WITH_SSL
bin_PROGRAMS += ssl_publish
endif

###############################################################################
# Samples: source code
###############################################################################

async_publish_SOURCES = src/samples/async_publish.cpp

async_subscribe_SOURCES = src/samples/async_subscribe.cpp

async_consume_SOURCES = src/samples/async_consume.cpp

sync_publish_SOURCES = src/samples/sync_publish.cpp

sync_consume_SOURCES = src/samples/sync_consume.cpp

data_publish_SOURCES = src/samples/data_publish.cpp

pub_speed_test_SOURCES = src/samples/pub_speed_test.cpp

if PAHO_WITH_SSL
ssl_publish_SOURCES = src/samples/ssl_publish.cpp
endif

###############################################################################
# Samples: proprocessor flags
###############################################################################

async_publish_CPPFLAGS = $(COMMONCPPFLAGS)

async_subscribe_CPPFLAGS = $(COMMONCPPFLAGS)

async_consume_CPPFLAGS = $(COMMONCPPFLAGS)

sync_publish_CPPFLAGS = $(COMMONCPPFLAGS)

sync_consume_CPPFLAGS = $(COMMONCPPFLAGS)

data_publish_CPPFLAGS = $(COMMONCPPFLAGS)

pub_speed_test_CPPFLAGS = $(COMMONCPPFLAGS)

if PAHO_WITH_SSL
ssl_publish_CPPFLAGS = $(COMMONCPPFLAGS)
endif

###############################################################################
# Samples: compiler flags
###############################################################################

COMMONCXXFLAGS  = $(CXXFLAGS)
COMMONCXXFLAGS += -I$(top_srcdir)/src/

async_publish_CXXFLAGS = $(COMMONCXXFLAGS)

async_subscribe_CXXFLAGS = $(COMMONCXXFLAGS)

async_consume_CXXFLAGS = $(COMMONCXXFLAGS)

sync_publish_CXXFLAGS = $(COMMONCXXFLAGS)

sync_consume_CXXFLAGS = $(COMMONCXXFLAGS)

data_publish_CXXFLAGS = $(COMMONCXXFLAGS)

pub_speed_test_CXXFLAGS = $(COMMONCXXFLAGS)

if PAHO_WITH_SSL
ssl_publish_CXXFLAGS = $(COMMONCXXFLAGS)
endif

###############################################################################
# Samples: linker flags
###############################################################################

COMMONLDFLAGS  = $(LDFLAGS)
COMMONLDFLAGS += $(LIBS)
COMMONLDFLAGS += libpaho-mqttpp3.la

async_publish_LDADD = $(COMMONLDFLAGS)

async_subscribe_LDADD = $(COMMONLDFLAGS)

async_consume_LDADD = $(COMMONLDFLAGS)

sync_publish_LDADD = $(COMMONLDFLAGS)

sync_consume_LDADD = $(COMMONLDFLAGS)

pub_speed_test_LDADD = $(COMMONLDFLAGS)

data_publish_LDADD = $(COMMONLDFLAGS)

if PAHO_WITH_SSL
ssl_publish_LDADD = $(COMMONLDFLAGS)
endif

endif

###############################################################################
# Test: names
###############################################################################

check_PROGRAMS  = async_client_test
check_PROGRAMS += buffer_ref_test
check_PROGRAMS += client_test
check_PROGRAMS += connect_options_test
check_PROGRAMS += delivery_response_options_test
check_PROGRAMS += disconnect_options_test
check_PROGRAMS += exception_test
check_PROGRAMS += iclient_persistence_test
check_PROGRAMS += message_test
check_PROGRAMS += response_options_test
check_PROGRAMS += ssl_options_test
check_PROGRAMS += string_collection_test
check_PROGRAMS += token_test
check_PROGRAMS += topic_test
check_PROGRAMS += will_options_test

TESTS = $(check_PROGRAMS)

###############################################################################
# Test: source code
###############################################################################

async_client_test_SOURCES = test/unit/async_client_test.cpp

buffer_ref_test_SOURCES = test/unit/buffer_ref_test.cpp

client_test_SOURCES = test/unit/client_test.cpp

connect_options_test_SOURCES = test/unit/connect_options_test.cpp

delivery_response_options_test_SOURCES = test/unit/delivery_response_options_test.cpp

disconnect_options_test_SOURCES = test/unit/disconnect_options_test.cpp

exception_test_SOURCES = test/unit/exception_test.cpp

iclient_persistence_test_SOURCES = test/unit/iclient_persistence_test.cpp

message_test_SOURCES = test/unit/message_test.cpp

response_options_test_SOURCES = test/unit/response_options_test.cpp

ssl_options_test_SOURCES = test/unit/ssl_options_test.cpp

string_collection_test_SOURCES = test/unit/string_collection_test.cpp

token_test_SOURCES = test/unit/token_test.cpp

topic_test_SOURCES = test/unit/topic_test.cpp

will_options_test_SOURCES = test/unit/will_options_test.cpp

###############################################################################
# Test: preprocessor flags
###############################################################################

async_client_test_CPPFLAGS  = $(COMMONCPPFLAGS)

buffer_ref_test_CPPFLAGS  = $(COMMONCPPFLAGS)

client_test_CPPFLAGS  = $(COMMONCPPFLAGS)

connect_options_test_CPPFLAGS  = $(COMMONCPPFLAGS)

delivery_response_options_test_CPPFLAGS  = $(COMMONCPPFLAGS)

disconnect_options_test_CPPFLAGS  = $(COMMONCPPFLAGS)

exception_test_CPPFLAGS  = $(COMMONCPPFLAGS)

iclient_persistence_test_CPPFLAGS  = $(COMMONCPPFLAGS)

message_test_CPPFLAGS  = $(COMMONCPPFLAGS)

response_options_test_CPPFLAGS  = $(COMMONCPPFLAGS)

ssl_options_test_CPPFLAGS  = $(COMMONCPPFLAGS)

string_collection_test_CPPFLAGS  = $(COMMONCPPFLAGS)

token_test_CPPFLAGS  = $(COMMONCPPFLAGS)

topic_test_CPPFLAGS  = $(COMMONCPPFLAGS)

will_options_test_CPPFLAGS  = $(COMMONCPPFLAGS)

###############################################################################
# Test: compiler flags
###############################################################################

UNITTESTCXXFLAGS  = $(CXXFLAGS)
UNITTESTCXXFLAGS += -I $(srcdir)/src

async_client_test_CXXFLAGS  = $(UNITTESTCXXFLAGS)

buffer_ref_test_CXXFLAGS  = $(UNITTESTCXXFLAGS)

client_test_CXXFLAGS  = $(UNITTESTCXXFLAGS)

connect_options_test_CXXFLAGS  = $(UNITTESTCXXFLAGS)

delivery_response_options_test_CXXFLAGS  = $(UNITTESTCXXFLAGS)

disconnect_options_test_CXXFLAGS  = $(UNITTESTCXXFLAGS)

exception_test_CXXFLAGS  = $(UNITTESTCXXFLAGS)

iclient_persistence_test_CXXFLAGS  = $(UNITTESTCXXFLAGS)

message_test_CXXFLAGS  = $(UNITTESTCXXFLAGS)

response_options_test_CXXFLAGS  = $(UNITTESTCXXFLAGS)

ssl_options_test_CXXFLAGS  = $(UNITTESTCXXFLAGS)

string_collection_test_CXXFLAGS  = $(UNITTESTCXXFLAGS)

token_test_CXXFLAGS  = $(UNITTESTCXXFLAGS)

topic_test_CXXFLAGS  = $(UNITTESTCXXFLAGS)

will_options_test_CXXFLAGS  = $(UNITTESTCXXFLAGS)

###############################################################################
# Test: linker flags
###############################################################################

UNITTESTLDFLAGS  = $(LDFLAGS)
UNITTESTLDFLAGS += $(LIBS)

async_client_test_LDFLAGS  = $(UNITTESTLDFLAGS)

buffer_ref_test_LDFLAGS  = $(UNITTESTLDFLAGS)

client_test_LDFLAGS  = $(UNITTESTLDFLAGS)

connect_options_test_LDFLAGS  = $(UNITTESTLDFLAGS)

delivery_response_options_test_LDFLAGS  = $(UNITTESTLDFLAGS)

disconnect_options_test_LDFLAGS  = $(UNITTESTLDFLAGS)

exception_test_LDFLAGS  = $(UNITTESTLDFLAGS)

iclient_persistence_test_LDFLAGS  = $(UNITTESTLDFLAGS)

message_test_LDFLAGS  = $(UNITTESTLDFLAGS)

response_options_test_LDFLAGS  = $(UNITTESTLDFLAGS)

ssl_options_test_LDFLAGS  = $(UNITTESTLDFLAGS)

string_collection_test_LDFLAGS  = $(UNITTESTLDFLAGS)

token_test_LDFLAGS  = $(UNITTESTLDFLAGS)

topic_test_LDFLAGS  = $(UNITTESTLDFLAGS)

will_options_test_LDFLAGS  = $(UNITTESTLDFLAGS)


UNITTESTLDADD  = libpaho-mqttpp3.la
UNITTESTLDADD += -lgtest

async_client_test_LDADD  = $(UNITTESTLDADD)

buffer_ref_test_LDADD  = $(UNITTESTLDADD)

client_test_LDADD  = $(UNITTESTLDADD)

connect_options_test_LDADD  = $(UNITTESTLDADD)

delivery_response_options_test_LDADD  = $(UNITTESTLDADD)

disconnect_options_test_LDADD  = $(UNITTESTLDADD)

exception_test_LDADD  = $(UNITTESTLDADD)

iclient_persistence_test_LDADD  = $(UNITTESTLDADD)

message_test_LDADD  = $(UNITTESTLDADD)

response_options_test_LDADD  = $(UNITTESTLDADD)

ssl_options_test_LDADD  = $(UNITTESTLDADD)

string_collection_test_LDADD  = $(UNITTESTLDADD)

token_test_LDADD  = $(UNITTESTLDADD)

topic_test_LDADD  = $(UNITTESTLDADD)

will_options_test_LDADD  = $(UNITTESTLDADD)

###############################################################################
# Documentation
###############################################################################

if PAHO_BUILD_DOC
doxyfile.stamp:
	$(MKDIR_P) @top_builddir@/doc
	cd doc && $(DOXYGEN) Doxyfile
	echo Timestamp > doxyfile.stamp

CLEANFILES = doxyfile.stamp

all-local: doxyfile.stamp
clean-local:
	rm -rf $(top_srcdir)/docs/man
endif

