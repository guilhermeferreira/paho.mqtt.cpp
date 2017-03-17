// test.cpp
// Unit tests for the connect_options class in the Paho MQTT C++ library.

/*******************************************************************************
 * Copyright (c) 2016 Frank Pagliughi <fpagliughi@mindspring.com>
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Frank Pagliughi - initial implementation and documentation
 *******************************************************************************/

#include "message_test.h"
#include "will_options_test.h"
#include "ssl_options_test.h"
#include "connect_options_test.h"
#include "disconnect_options_test.h"
#include "response_options_test.h"
#include "delivery_response_options_test.h"
#include "iclient_persistence_test.h"
#include "token_test.h"
#include "topic_test.h"
#include "exception_test.h"

using namespace CppUnit;

/////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	CPPUNIT_TEST_SUITE_REGISTRATION( message_test );
	CPPUNIT_TEST_SUITE_REGISTRATION( will_options_test );
	CPPUNIT_TEST_SUITE_REGISTRATION( ssl_options_test );
	CPPUNIT_TEST_SUITE_REGISTRATION( connect_options_test );
	CPPUNIT_TEST_SUITE_REGISTRATION( disconnect_options_test );
	CPPUNIT_TEST_SUITE_REGISTRATION( response_options_test );
	CPPUNIT_TEST_SUITE_REGISTRATION( delivery_response_options_test );
	CPPUNIT_TEST_SUITE_REGISTRATION( iclient_persistence_test );
	CPPUNIT_TEST_SUITE_REGISTRATION( token_test );
	CPPUNIT_TEST_SUITE_REGISTRATION( topic_test );
	CPPUNIT_TEST_SUITE_REGISTRATION( exception_test );

	TextUi::TestRunner runner;
	TestFactoryRegistry &registry = TestFactoryRegistry::getRegistry();

	runner.addTest(registry.makeTest());
	return (runner.run()) ? 0 : 1;
}
