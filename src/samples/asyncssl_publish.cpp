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
 *    Guilherme M. Ferreira - initial implementation
 *******************************************************************************/

#include <cstdlib>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>	// For sleep

#include "mqtt/async_client.h"
#include "cert.h"

/////////////////////////////////////////////////////////////////////////////

const std::string DFLT_ADDRESS("ssl://localhost:18885");
const std::string DFLT_CLIENTID("AsyncSSLPublish");
const std::string TOPIC("hello");

const char* PAYLOAD1 = "Hello World!";
const char* PAYLOAD2 = "Hi there!";
const char* PAYLOAD3 = "Is anyone listening?";
const char* PAYLOAD4 = "Someone is always listening.";

const int  QOS = 1;
const long TIMEOUT = 10000L;

/**
 * A callback class for use with the main MQTT client.
 */
class callback : public virtual mqtt::callback
{
public:
	virtual void connection_lost(const std::string& cause) {
		std::cout << "\nConnection lost" << std::endl;
		if (!cause.empty())
			std::cout << "\tcause: " << cause << std::endl;
	}

	// We're not subscribed to anything, so this should never be called.
	virtual void message_arrived(const std::string& topic, mqtt::const_message_ptr msg) {

	}

	virtual void delivery_complete(mqtt::idelivery_token_ptr tok) {
		std::cout << "Delivery complete for token: "
			<< (tok ? tok->get_message_id() : -1) << std::endl;
	}
};

int main(int argc, char* argv[])
{
	std::cout << "Initializing..." << std::endl;

	std::string address  = (argc > 1) ? std::string(argv[1]) : DFLT_ADDRESS;
	std::string clientID = (argc > 2) ? std::string(argv[2]) : DFLT_CLIENTID;
	mqtt::async_client client(address, clientID);

	mqtt::connect_options connOpts;
	connOpts.set_keep_alive_interval(20);
	connOpts.set_clean_session(true);
	connOpts.set_user_name("testuser");
	connOpts.set_password("testpassword");

	mqtt::ssl_options sslopts;
	sslopts.set_enable_server_cert_auth(true);
	sslopts.set_trust_store(CERT); // file of certificates trusted by client
	connOpts.set_ssl_options(sslopts);

	callback cb;
	client.set_callback(cb);

	std::cout << "...OK" << std::endl;

	try {
		// Connect
		std::cout << "\nConnecting..." << std::endl;
		mqtt::itoken_ptr conntok = client.connect(connOpts);
		std::cout << "Waiting for the connection..." << std::endl;
		conntok->wait_for_completion();
		std::cout << "...OK" << std::endl;

		std::cout << "\nSending message..." << std::endl;
		mqtt::message_ptr pubmsg = mqtt::make_message(PAYLOAD1);
		pubmsg->set_qos(QOS);
		client.publish(TOPIC, pubmsg)->wait_for_completion(TIMEOUT);
		std::cout << "...OK" << std::endl;

		std::vector<mqtt::idelivery_token_ptr> toks = client.get_pending_delivery_tokens();
		if (!toks.empty())
			std::cout << "Error: There are pending delivery tokens!" << std::endl;

		// Disconnect
		std::cout << "\nDisconnecting..." << std::endl;
		conntok = client.disconnect();
		conntok->wait_for_completion();
		std::cout << "...OK" << std::endl;
	}
	catch (const mqtt::exception& exc) {
		std::string error{exc.what()};
		std::cerr << "...Error: " << error << std::endl;
		return 1;
	}

 	return 0;
}
