#*******************************************************************************
#  Copyright (c) 2016-2017
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

## Note: on OS X you should install XCode and the associated command-line tools

## install headers
file(GLOB COMMON_HDR *.h)

if(PAHO_WITH_SSL)
    set(COMMON_HDR
        ${COMMON_HDR}
        ssl_options.h)
endif()

install(
    FILES ${COMMON_HDR}
    DESTINATION include/mqtt
)
