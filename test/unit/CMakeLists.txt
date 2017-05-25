#*******************************************************************************
#  Copyright (c) 2016-2017 Guilherme M. Ferreira <guilherme.maciel.ferreira@gmail.com>
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
#     Guilherme Maciel Ferreira - initial version
#*******************************************************************************/

project(mqttpp-unittest)

## include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(GTEST_INC_DIR ${GTEST_PATH})
include_directories(${GTEST_INC_DIR})

## link directories
set(GTEST_LIB_DIR ${GTEST_PATH})
link_directories(${GTEST_LIB_DIR})

if(PAHO_BUILD_STATIC)
    add_executable(mqttpp-unittest
        test.cpp)

    target_link_libraries(mqttpp-unittest
        ${PAHO_MQTT_C}
        ${PAHO_MQTT_CPP_STATIC}
        gtest)

    add_test(
        NAME check
        COMMAND mqttpp-unittest)
endif()
