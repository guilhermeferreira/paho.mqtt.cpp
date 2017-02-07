// token_test.h
// Unit tests for the token class in the Paho MQTT C++ library.

/*******************************************************************************
 * Copyright (c) 2016 Guilherme M. Ferreira <guilherme.maciel.ferreira@gmail.com>
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
 *    Guilherme M. Ferreira - initial implementation and documentation
 *    Frank Pagliughi - additional tests. Made this test a friend of token.
 *    Guilherme M. Ferreira - changed framework from CppUnit to GTest
 *******************************************************************************/

#ifndef __mqtt_token_test_h
#define __mqtt_token_test_h

#include <algorithm>
#include <memory>
#include <stdexcept>

#include <gtest/gtest.h>

#include "mqtt/token.h"
#include "dummy_async_client.h"
#include "dummy_action_listener.h"

namespace mqtt {

/////////////////////////////////////////////////////////////////////////////

class token_test : public ::testing::Test
{
protected:
	mqtt::test::dummy_async_client cli;

	MQTTAsync_connectOptions& get_c_struct(mqtt::connect_options& opts) {
		return opts.opts_;
	}

	MQTTAsync_disconnectOptions& get_c_struct(mqtt::disconnect_options& opts) {
		return opts.opts_;
	}

	MQTTAsync_responseOptions& get_c_struct(mqtt::response_options& opts) {
		return opts.opts_;
	}

	static void on_success(void* tokObj, MQTTAsync_successData* rsp) {
		token::on_success(tokObj, rsp);
	}

	static void on_failure(void* tokObj, MQTTAsync_failureData* rsp) {
		token::on_failure(tokObj, rsp);
	}

public:
	void SetUp() {}
	void TearDown() {}
};

// ----------------------------------------------------------------------
// Test user constructor (iasync_client)
// ----------------------------------------------------------------------

TEST_F(token_test, test_user_constructor_client) {
	mqtt::token tok{ cli };
	EXPECT_EQ(0, tok.get_message_id());
	EXPECT_EQ(dynamic_cast<mqtt::iasync_client*>(&cli), tok.get_client());
	EXPECT_EQ(static_cast<void*>(nullptr), tok.get_user_context());
	EXPECT_EQ(static_cast<mqtt::iaction_listener*>(nullptr), tok.get_action_callback());
	EXPECT_FALSE(tok.is_complete());
	EXPECT_EQ(0, static_cast<int>(tok.get_topics().size()));
}

// ----------------------------------------------------------------------
// Test user constructor (iasync_client, MQTTAsync_token)
// ----------------------------------------------------------------------

TEST_F(token_test, test_user_constructor_client_token) {
	MQTTAsync_token id {2};
	mqtt::token tok{ cli, id };
	EXPECT_EQ(id, tok.get_message_id());
	EXPECT_EQ(dynamic_cast<mqtt::iasync_client*>(&cli), tok.get_client());
	EXPECT_EQ(static_cast<void*>(nullptr), tok.get_user_context());
	EXPECT_EQ(static_cast<mqtt::iaction_listener*>(nullptr), tok.get_action_callback());
	EXPECT_FALSE(tok.is_complete());
	EXPECT_EQ(0, static_cast<int>(tok.get_topics().size()));
}

// ----------------------------------------------------------------------
// Test user constructor (iasync_client, string)
// ----------------------------------------------------------------------

TEST_F(token_test, test_user_constructor_client_string) {
	std::string topic { "topic" };
	mqtt::token tok{ cli, topic };
	EXPECT_EQ(0, tok.get_message_id());
	EXPECT_EQ(dynamic_cast<mqtt::iasync_client*>(&cli), tok.get_client());
	EXPECT_EQ(static_cast<void*>(nullptr), tok.get_user_context());
	EXPECT_EQ(static_cast<mqtt::iaction_listener*>(nullptr), tok.get_action_callback());
	EXPECT_FALSE(tok.is_complete());
	EXPECT_EQ(1, static_cast<int>(tok.get_topics().size()));
	EXPECT_EQ(topic, tok.get_topics()[0]);
}

// ----------------------------------------------------------------------
// Test user constructor (iasync_client, vector<string>)
// ----------------------------------------------------------------------

TEST_F(token_test, test_user_constructor_client_vector) {
	std::vector<std::string> topics { "topic1", "topic2" };
	mqtt::token tok{ cli, topics };
	EXPECT_EQ(0, tok.get_message_id());
	EXPECT_EQ(dynamic_cast<mqtt::iasync_client*>(&cli), tok.get_client());
	EXPECT_EQ(static_cast<void*>(nullptr), tok.get_user_context());
	EXPECT_EQ(static_cast<mqtt::iaction_listener*>(nullptr), tok.get_action_callback());
	EXPECT_FALSE(tok.is_complete());
	EXPECT_EQ(2, static_cast<int>(tok.get_topics().size()));
	EXPECT_EQ(topics[0], tok.get_topics()[0]);
	EXPECT_EQ(topics[1], tok.get_topics()[1]);
}

// ----------------------------------------------------------------------
// Test on success with data
// ----------------------------------------------------------------------

TEST_F(token_test, test_on_success_with_data) {
	mqtt::token tok{ cli };

	constexpr int MESSAGE_ID = 12;
	MQTTAsync_successData data = {
			.token = MESSAGE_ID,
	};

	EXPECT_FALSE(tok.is_complete());
	token_test::on_success(&tok, &data);
	EXPECT_TRUE(tok.is_complete());
	EXPECT_EQ(MESSAGE_ID, tok.get_message_id());
}

// ----------------------------------------------------------------------
// Test on success without data
// ----------------------------------------------------------------------

TEST_F(token_test, test_on_success_without_data) {
	mqtt::token tok{ cli };

	EXPECT_FALSE(tok.is_complete());
	token_test::on_success(&tok, nullptr);
	EXPECT_TRUE(tok.is_complete());
}

// ----------------------------------------------------------------------
// Test on failure with data
// ----------------------------------------------------------------------

TEST_F(token_test, test_on_failure_with_data) {
	mqtt::token tok{ cli };

	EXPECT_FALSE(tok.is_complete());
	constexpr int MESSAGE_ID = 12;
	MQTTAsync_failureData data = {
			.token = MESSAGE_ID,
			.code = 13,
			.message = nullptr,
	};
	token_test::on_failure(&tok, &data);
	EXPECT_TRUE(tok.is_complete());
	EXPECT_EQ(MESSAGE_ID, tok.get_message_id());
}

// ----------------------------------------------------------------------
// Test on failure without data
// ----------------------------------------------------------------------

TEST_F(token_test, test_on_failure_without_data) {
	mqtt::token tok{ cli };

	EXPECT_FALSE(tok.is_complete());
	token_test::on_failure(&tok, nullptr);
	EXPECT_TRUE(tok.is_complete());
	EXPECT_EQ(0, tok.get_message_id());
}

// ----------------------------------------------------------------------
// Test set callbacks
// ----------------------------------------------------------------------

TEST_F(token_test, test_action_callback) {
	mqtt::test::dummy_action_listener listener;
	mqtt::token tok{ cli };
	tok.set_action_callback(listener);
	EXPECT_EQ(dynamic_cast<mqtt::iaction_listener*>(&listener), tok.get_action_callback());

	EXPECT_FALSE(listener.on_success_called);
	token_test::on_success(&tok, nullptr);
	EXPECT_TRUE(listener.on_success_called);

	EXPECT_FALSE(listener.on_failure_called);
	token_test::on_failure(&tok, nullptr);
	EXPECT_TRUE(listener.on_failure_called);
}

// ----------------------------------------------------------------------
// Test wait for completion on success case
// ----------------------------------------------------------------------

TEST_F(token_test, test_wait_for_completion_success) {
	mqtt::token tok{ cli };

	// NOTE: Make sure the complete flag is already true and the return
	// code (rc) is MQTTASYNC_SUCCESS, so the token::wait_for_completion()
	// returns immediately. Otherwise we will get stuck in a single thread
	// that can't change the complete flag.
	EXPECT_FALSE(tok.is_complete());
	token_test::on_success(&tok, nullptr);
	EXPECT_TRUE(tok.is_complete());
	tok.wait_for_completion();
}

// ----------------------------------------------------------------------
// Test wait for completion on failure case
// ----------------------------------------------------------------------

TEST_F(token_test, test_wait_for_completion_failure) {
	mqtt::token tok{ cli };

	// NOTE: Make sure the complete flag is already true and the return
	// code (rc) is MQTTASYNC_FAILURE, so the token::wait_for_completion()
	// returns immediately. Otherwise we will get stuck in a single thread
	// that can't change the complete flag.
	EXPECT_FALSE(tok.is_complete());
	constexpr int MESSAGE_ID = 12;
	MQTTAsync_failureData data = {
			.token = MESSAGE_ID,
			.code = MQTTASYNC_FAILURE,
			.message = nullptr,
	};
	token_test::on_failure(&tok, &data);
	EXPECT_TRUE(tok.is_complete());
	EXPECT_EQ(MESSAGE_ID, tok.get_message_id());
	try {
		tok.wait_for_completion();
	}
	catch (mqtt::exception& ex) {
		EXPECT_EQ(MQTTASYNC_FAILURE, ex.get_reason_code());
	}
}

// ----------------------------------------------------------------------
// Test wait for completion on success due timeout case
// ----------------------------------------------------------------------

TEST_F(token_test, test_wait_for_completion_timeout_success) {
	mqtt::token tok{ cli };

	EXPECT_FALSE(tok.is_complete());
	token_test::on_success(&tok, nullptr);

	// timeout == 0
	EXPECT_TRUE(tok.is_complete());
	tok.wait_for_completion(0);

	// timeout > 0
	EXPECT_TRUE(tok.is_complete());
	tok.wait_for_completion(10);

	// timeout < 0
	EXPECT_TRUE(tok.is_complete());
	tok.wait_for_completion(-10);
}

// ----------------------------------------------------------------------
// Test wait for completion on failure due timeout case
// ----------------------------------------------------------------------

TEST_F(token_test, test_wait_for_completion_timeout_failure) {
	mqtt::token tok{ cli };

	// timeout == 0
	// NOTE: This test must be performed BEFORE invoking the
	// on_failure() callback. Because complete_ must be false.
	EXPECT_FALSE(tok.is_complete());
	try {
		tok.wait_for_completion(0);
	}
	catch (mqtt::exception& ex) {
		EXPECT_EQ(MQTTASYNC_FAILURE, ex.get_reason_code());
	}

	// timeout > 0
	// NOTE: This test must be performed BEFORE invoking the
	// on_failure() callback. Because we will make
	// condition_variable::wait_for() to fail.
	EXPECT_FALSE(tok.is_complete());
	try {
		tok.wait_for_completion(10);
	}
	catch (mqtt::exception& ex) {
		EXPECT_EQ(MQTTASYNC_FAILURE, ex.get_reason_code());
	}

	EXPECT_FALSE(tok.is_complete());
	constexpr int MESSAGE_ID = 12;
	MQTTAsync_failureData data = {
			.token = MESSAGE_ID,
			.code = MQTTASYNC_FAILURE,
			.message = nullptr,
	};
	token_test::on_failure(&tok, &data);

	// timeout < 0
	EXPECT_TRUE(tok.is_complete());
	try {
		tok.wait_for_completion(-10);
	}
	catch (mqtt::exception& ex) {
		EXPECT_EQ(MQTTASYNC_FAILURE, ex.get_reason_code());
	}
}

/////////////////////////////////////////////////////////////////////////////
// end namespace mqtt
}

#endif //  __mqtt_token_test_h
