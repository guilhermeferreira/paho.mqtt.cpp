// ssl_options_test.h
// Unit tests for the ssl_options class in the Paho MQTT C++ library.

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
 *    Guilherme M. Ferreira - add more test cases
 *******************************************************************************/

#ifndef __mqtt_ssl_options_test_h
#define __mqtt_ssl_options_test_h

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "mqtt/ssl_options.h"

/////////////////////////////////////////////////////////////////////////////

class ssl_options_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( ssl_options_test );

	CPPUNIT_TEST( test_dflt_constructor );
	CPPUNIT_TEST( test_user_constructor );
	CPPUNIT_TEST( test_copy_constructor );
	CPPUNIT_TEST( test_move_constructor );
	CPPUNIT_TEST( test_copy_assignment );
	CPPUNIT_TEST( test_move_assignment );
	CPPUNIT_TEST( test_set_user );
	CPPUNIT_TEST( test_set_empty_strings );

	CPPUNIT_TEST_SUITE_END();

	const std::string EMPTY_STR;
	const std::string TRUST_STORE { "trust store" };
	const std::string KEY_STORE { "key store" };
	const std::string PRIVATE_KEY { "private key" };
	const std::string PRIVATE_KEY_PASSWORD { "private key password" };
	const std::string ENABLED_CIPHER_SUITES { "cipher suite" };
	const bool SERVER_CERT { false };

	mqtt::ssl_options orgOpts;

public:
	void setUp() {
		orgOpts = mqtt::ssl_options{
			TRUST_STORE,
			KEY_STORE,
			PRIVATE_KEY,
			PRIVATE_KEY_PASSWORD,
			ENABLED_CIPHER_SUITES,
			SERVER_CERT};
	}
	void tearDown() {}

// ----------------------------------------------------------------------
// Test the default constructor
// ----------------------------------------------------------------------

	void test_dflt_constructor() {
		mqtt::ssl_options opts;

		CPPUNIT_ASSERT_EQUAL(EMPTY_STR, opts.get_trust_store());
		CPPUNIT_ASSERT_EQUAL(EMPTY_STR, opts.get_key_store());
		CPPUNIT_ASSERT_EQUAL(EMPTY_STR, opts.get_private_key());
		CPPUNIT_ASSERT_EQUAL(EMPTY_STR, opts.get_private_key_password());
		CPPUNIT_ASSERT_EQUAL(true, opts.get_enable_server_cert_auth());

		// Make sure the empty string represents a nullptr for C library
		MQTTAsync_SSLOptions copts = opts.get_c_struct();
		CPPUNIT_ASSERT_EQUAL(static_cast<const char*>(nullptr), static_cast<const char*>(copts.trustStore));
		CPPUNIT_ASSERT_EQUAL(static_cast<const char*>(nullptr), static_cast<const char*>(copts.keyStore));
		CPPUNIT_ASSERT_EQUAL(static_cast<const char*>(nullptr), static_cast<const char*>(copts.privateKey));
		CPPUNIT_ASSERT_EQUAL(static_cast<const char*>(nullptr), static_cast<const char*>(copts.privateKeyPassword));
		CPPUNIT_ASSERT_EQUAL(static_cast<const char*>(nullptr), static_cast<const char*>(copts.enabledCipherSuites));
	}

// ----------------------------------------------------------------------
// Test the constructor that takes user arguments
// ----------------------------------------------------------------------

	void test_user_constructor() {
		mqtt::ssl_options opts{TRUST_STORE, KEY_STORE, PRIVATE_KEY,
			PRIVATE_KEY_PASSWORD, ENABLED_CIPHER_SUITES, SERVER_CERT};

		CPPUNIT_ASSERT_EQUAL(TRUST_STORE, opts.get_trust_store());
		CPPUNIT_ASSERT_EQUAL(KEY_STORE, opts.get_key_store());
		CPPUNIT_ASSERT_EQUAL(PRIVATE_KEY, opts.get_private_key());
		CPPUNIT_ASSERT_EQUAL(PRIVATE_KEY_PASSWORD, opts.get_private_key_password());
		CPPUNIT_ASSERT_EQUAL(ENABLED_CIPHER_SUITES, opts.get_enabled_cipher_suites());
		CPPUNIT_ASSERT_EQUAL(SERVER_CERT, opts.get_enable_server_cert_auth());
	}

// ----------------------------------------------------------------------
// Test the copy constructor
// ----------------------------------------------------------------------

	void test_copy_constructor() {
		mqtt::ssl_options opts{orgOpts};

		CPPUNIT_ASSERT_EQUAL(TRUST_STORE, opts.get_trust_store());
		CPPUNIT_ASSERT_EQUAL(KEY_STORE, opts.get_key_store());
		CPPUNIT_ASSERT_EQUAL(PRIVATE_KEY, opts.get_private_key());
		CPPUNIT_ASSERT_EQUAL(PRIVATE_KEY_PASSWORD, opts.get_private_key_password());
		CPPUNIT_ASSERT_EQUAL(ENABLED_CIPHER_SUITES, opts.get_enabled_cipher_suites());
		CPPUNIT_ASSERT_EQUAL(SERVER_CERT, opts.get_enable_server_cert_auth());

		// Make sure it's a true copy, not linked to the original
		orgOpts.set_trust_store("");
		orgOpts.set_key_store("");
		orgOpts.set_private_key("");
		orgOpts.set_private_key_password("");
		orgOpts.set_enabled_cipher_suites("");
		orgOpts.set_enable_server_cert_auth(!SERVER_CERT);

		CPPUNIT_ASSERT_EQUAL(TRUST_STORE, opts.get_trust_store());
		CPPUNIT_ASSERT_EQUAL(KEY_STORE, opts.get_key_store());
		CPPUNIT_ASSERT_EQUAL(PRIVATE_KEY, opts.get_private_key());
		CPPUNIT_ASSERT_EQUAL(PRIVATE_KEY_PASSWORD, opts.get_private_key_password());
		CPPUNIT_ASSERT_EQUAL(ENABLED_CIPHER_SUITES, opts.get_enabled_cipher_suites());
		CPPUNIT_ASSERT_EQUAL(SERVER_CERT, opts.get_enable_server_cert_auth());
	}

// ----------------------------------------------------------------------
// Test the move constructor
// ----------------------------------------------------------------------

	void test_move_constructor() {
		mqtt::ssl_options opts(std::move(orgOpts));

		CPPUNIT_ASSERT_EQUAL(TRUST_STORE, opts.get_trust_store());
		CPPUNIT_ASSERT_EQUAL(KEY_STORE, opts.get_key_store());
		CPPUNIT_ASSERT_EQUAL(PRIVATE_KEY, opts.get_private_key());
		CPPUNIT_ASSERT_EQUAL(PRIVATE_KEY_PASSWORD, opts.get_private_key_password());
		CPPUNIT_ASSERT_EQUAL(ENABLED_CIPHER_SUITES, opts.get_enabled_cipher_suites());
		CPPUNIT_ASSERT_EQUAL(SERVER_CERT, opts.get_enable_server_cert_auth());

		// Check that the original was moved
		CPPUNIT_ASSERT_EQUAL(EMPTY_STR, orgOpts.get_trust_store());
		CPPUNIT_ASSERT_EQUAL(EMPTY_STR, orgOpts.get_key_store());
		CPPUNIT_ASSERT_EQUAL(EMPTY_STR, orgOpts.get_private_key());
		CPPUNIT_ASSERT_EQUAL(EMPTY_STR, orgOpts.get_private_key_password());
		CPPUNIT_ASSERT_EQUAL(EMPTY_STR, orgOpts.get_enabled_cipher_suites());
		CPPUNIT_ASSERT_EQUAL(!SERVER_CERT, orgOpts.get_enable_server_cert_auth());
	}

// ----------------------------------------------------------------------
// Test the copy assignment operator=(const&)
// ----------------------------------------------------------------------

	void test_copy_assignment() {
		mqtt::ssl_options opts;

		opts = orgOpts;

		CPPUNIT_ASSERT_EQUAL(TRUST_STORE, opts.get_trust_store());
		CPPUNIT_ASSERT_EQUAL(KEY_STORE, opts.get_key_store());
		CPPUNIT_ASSERT_EQUAL(PRIVATE_KEY, opts.get_private_key());
		CPPUNIT_ASSERT_EQUAL(PRIVATE_KEY_PASSWORD, opts.get_private_key_password());
		CPPUNIT_ASSERT_EQUAL(ENABLED_CIPHER_SUITES, opts.get_enabled_cipher_suites());
		CPPUNIT_ASSERT_EQUAL(SERVER_CERT, opts.get_enable_server_cert_auth());

		// Make sure it's a true copy, not linked to the original
		orgOpts.set_trust_store("");
		orgOpts.set_key_store("");
		orgOpts.set_private_key("");
		orgOpts.set_private_key_password("");
		orgOpts.set_enabled_cipher_suites("");
		orgOpts.set_enable_server_cert_auth(!SERVER_CERT);

		CPPUNIT_ASSERT_EQUAL(TRUST_STORE, opts.get_trust_store());
		CPPUNIT_ASSERT_EQUAL(KEY_STORE, opts.get_key_store());
		CPPUNIT_ASSERT_EQUAL(PRIVATE_KEY, opts.get_private_key());
		CPPUNIT_ASSERT_EQUAL(PRIVATE_KEY_PASSWORD, opts.get_private_key_password());
		CPPUNIT_ASSERT_EQUAL(ENABLED_CIPHER_SUITES, opts.get_enabled_cipher_suites());
		CPPUNIT_ASSERT_EQUAL(SERVER_CERT, opts.get_enable_server_cert_auth());

		// Self assignment should cause no harm
		opts = opts;

		CPPUNIT_ASSERT_EQUAL(TRUST_STORE, opts.get_trust_store());
		CPPUNIT_ASSERT_EQUAL(KEY_STORE, opts.get_key_store());
		CPPUNIT_ASSERT_EQUAL(PRIVATE_KEY, opts.get_private_key());
		CPPUNIT_ASSERT_EQUAL(PRIVATE_KEY_PASSWORD, opts.get_private_key_password());
		CPPUNIT_ASSERT_EQUAL(ENABLED_CIPHER_SUITES, opts.get_enabled_cipher_suites());
		CPPUNIT_ASSERT_EQUAL(SERVER_CERT, opts.get_enable_server_cert_auth());
	}

// ----------------------------------------------------------------------
// Test the move assignment, operator=(&&)
// ----------------------------------------------------------------------

	void test_move_assignment() {
		mqtt::ssl_options opts;

		opts = std::move(orgOpts);

		CPPUNIT_ASSERT_EQUAL(TRUST_STORE, opts.get_trust_store());
		CPPUNIT_ASSERT_EQUAL(KEY_STORE, opts.get_key_store());
		CPPUNIT_ASSERT_EQUAL(PRIVATE_KEY, opts.get_private_key());
		CPPUNIT_ASSERT_EQUAL(PRIVATE_KEY_PASSWORD, opts.get_private_key_password());
		CPPUNIT_ASSERT_EQUAL(ENABLED_CIPHER_SUITES, opts.get_enabled_cipher_suites());
		CPPUNIT_ASSERT_EQUAL(SERVER_CERT, opts.get_enable_server_cert_auth());

		// Check that the original was moved
		CPPUNIT_ASSERT_EQUAL(EMPTY_STR, orgOpts.get_trust_store());
		CPPUNIT_ASSERT_EQUAL(EMPTY_STR, orgOpts.get_key_store());
		CPPUNIT_ASSERT_EQUAL(EMPTY_STR, orgOpts.get_private_key());
		CPPUNIT_ASSERT_EQUAL(EMPTY_STR, orgOpts.get_private_key_password());
		CPPUNIT_ASSERT_EQUAL(EMPTY_STR, orgOpts.get_enabled_cipher_suites());
		CPPUNIT_ASSERT_EQUAL(!SERVER_CERT, orgOpts.get_enable_server_cert_auth());

		// Self assignment should cause no harm
		opts = std::move(opts);

		CPPUNIT_ASSERT_EQUAL(TRUST_STORE, opts.get_trust_store());
		CPPUNIT_ASSERT_EQUAL(KEY_STORE, opts.get_key_store());
		CPPUNIT_ASSERT_EQUAL(PRIVATE_KEY, opts.get_private_key());
		CPPUNIT_ASSERT_EQUAL(PRIVATE_KEY_PASSWORD, opts.get_private_key_password());
		CPPUNIT_ASSERT_EQUAL(ENABLED_CIPHER_SUITES, opts.get_enabled_cipher_suites());
		CPPUNIT_ASSERT_EQUAL(SERVER_CERT, opts.get_enable_server_cert_auth());
	}

// ----------------------------------------------------------------------
// Test set/get of the user and password.
// ----------------------------------------------------------------------

	void test_set_user() {
		mqtt::ssl_options opts;

		const std::string TRUST_STORE("trust store");
		const std::string KEY_STORE("key store");
		const std::string PRIVATE_KEY("private key");
		const std::string PRIVATE_KEY_PASSWORD("private key password");
		const std::string ENABLED_CIPHER_SUITES("cipher suite");
		const bool SERVER_CERT = false;

		opts.set_trust_store(TRUST_STORE);
		opts.set_key_store(KEY_STORE);
		opts.set_private_key(PRIVATE_KEY);
		opts.set_private_key_password(PRIVATE_KEY_PASSWORD);
		opts.set_enabled_cipher_suites(ENABLED_CIPHER_SUITES);
		opts.set_enable_server_cert_auth(SERVER_CERT);

		CPPUNIT_ASSERT_EQUAL(TRUST_STORE, opts.get_trust_store());
		CPPUNIT_ASSERT_EQUAL(KEY_STORE, opts.get_key_store());
		CPPUNIT_ASSERT_EQUAL(PRIVATE_KEY, opts.get_private_key());
		CPPUNIT_ASSERT_EQUAL(PRIVATE_KEY_PASSWORD, opts.get_private_key_password());
		CPPUNIT_ASSERT_EQUAL(ENABLED_CIPHER_SUITES, opts.get_enabled_cipher_suites());
		CPPUNIT_ASSERT_EQUAL(SERVER_CERT, opts.get_enable_server_cert_auth());
	}

// ----------------------------------------------------------------------
// Test if empty strings gives nullptr opts
// ----------------------------------------------------------------------

	void test_set_empty_strings() {
		mqtt::ssl_options opts;

		opts.set_trust_store(EMPTY_STR);
		opts.set_key_store(EMPTY_STR);
		opts.set_private_key(EMPTY_STR);
		opts.set_private_key_password(EMPTY_STR);
		opts.set_enabled_cipher_suites(EMPTY_STR);

		// Make sure the empty string represents a nullptr for C library
		MQTTAsync_SSLOptions copts = opts.get_c_struct();
		CPPUNIT_ASSERT_EQUAL(static_cast<const char*>(nullptr), static_cast<const char*>(copts.trustStore));
		CPPUNIT_ASSERT_EQUAL(static_cast<const char*>(nullptr), static_cast<const char*>(copts.keyStore));
		CPPUNIT_ASSERT_EQUAL(static_cast<const char*>(nullptr), static_cast<const char*>(copts.privateKey));
		CPPUNIT_ASSERT_EQUAL(static_cast<const char*>(nullptr), static_cast<const char*>(copts.privateKeyPassword));
		CPPUNIT_ASSERT_EQUAL(static_cast<const char*>(nullptr), static_cast<const char*>(copts.enabledCipherSuites));
	}

};

#endif		//  __mqtt_ssl_options_test_h


