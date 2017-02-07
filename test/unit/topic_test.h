// topic_test.h
// Unit tests for the topic class in the Paho MQTT C++ library.

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
 *    Guilherme M. Ferreira - changed framework from CppUnit to GTest
 *******************************************************************************/

#ifndef __mqtt_topic_test_h
#define __mqtt_topic_test_h

#include <algorithm>
#include <memory>
#include <stdexcept>

#include <gtest/gtest.h>

#include "mqtt/topic.h"

namespace mqtt {

/////////////////////////////////////////////////////////////////////////////

class topic_test : public ::testing::Test
{
protected:

	const std::string TOPIC_NAME { "topic_name" };
	mqtt::test::dummy_async_client cli;

public:
	void SetUp() {}
	void TearDown() {}
};

// ----------------------------------------------------------------------
// Test user constructor
// ----------------------------------------------------------------------

TEST_F(topic_test, test_user_constructor) {
	mqtt::topic topic{ TOPIC_NAME, cli };

	EXPECT_EQ(TOPIC_NAME, topic.get_name());
	EXPECT_EQ(TOPIC_NAME, topic.to_str());
}

// ----------------------------------------------------------------------
// Test publish with one argument
// ----------------------------------------------------------------------

TEST_F(topic_test, test_publish_1_arg) {
	mqtt::topic topic{ TOPIC_NAME, cli };

	mqtt::const_message_ptr msg_in { new mqtt::message { "message" } };

	mqtt::idelivery_token_ptr token { topic.publish(msg_in) };
	EXPECT_NE(nullptr, token);

	mqtt::const_message_ptr msg_out { token->get_message() };
	EXPECT_NE(nullptr, msg_out);

	EXPECT_EQ(msg_in->get_payload_str(), msg_out->get_payload_str());
	EXPECT_EQ(msg_in->get_qos(), msg_out->get_qos());
	EXPECT_EQ(0, msg_out->get_qos());
}

// ----------------------------------------------------------------------
// Test publish with three arguments
// ----------------------------------------------------------------------

TEST_F(topic_test, test_publish_3_arg) {
	mqtt::topic topic{ TOPIC_NAME, cli };

	std::string payload { "message" };
	int qos { 1 };

	mqtt::idelivery_token_ptr token { topic.publish(payload, qos, false) };
	EXPECT_NE(nullptr, token);

	mqtt::const_message_ptr msg_out { token->get_message() };
	EXPECT_NE(nullptr, msg_out);

	EXPECT_EQ(payload, msg_out->get_payload_str());
	EXPECT_EQ(qos, msg_out->get_qos());
}

// ----------------------------------------------------------------------
// Test publish with four arguments
// ----------------------------------------------------------------------

TEST_F(topic_test, test_publish_4_arg) {
	mqtt::topic topic{ TOPIC_NAME, cli };

	std::string payload { "message" };
	std::size_t payload_size { payload.size() };
	int qos { 2 };

	mqtt::idelivery_token_ptr token = topic.publish(payload.c_str(), payload_size, qos, false);
	EXPECT_NE(nullptr, token);

	mqtt::const_message_ptr msg_out = token->get_message();
	EXPECT_NE(nullptr, msg_out);

	EXPECT_EQ(payload, msg_out->get_payload_str());
	EXPECT_EQ(qos, msg_out->get_qos());
}

// ----------------------------------------------------------------------
// Test get name
// ----------------------------------------------------------------------

TEST_F(topic_test, test_get_name) {
	mqtt::topic topic{ TOPIC_NAME, cli };

	EXPECT_EQ(TOPIC_NAME, topic.get_name());
}

// ----------------------------------------------------------------------
// Test to string
// ----------------------------------------------------------------------

TEST_F(topic_test, test_to_str) {
	mqtt::topic topic { TOPIC_NAME, cli };

	EXPECT_EQ(TOPIC_NAME, topic.to_str());
}

/////////////////////////////////////////////////////////////////////////////
// end namespace mqtt
}

#endif //  __mqtt_topic_test_h
