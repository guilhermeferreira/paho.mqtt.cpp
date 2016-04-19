/*******************************************************************************
 * Copyright (c) 2016 Guilherme Ferreira <guilherme.maciel.ferreira@gmail.com>
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
 *    Guilherme Maciel Ferreira - initial implementation and documentation
 *******************************************************************************/

#include <cstdlib>
#include <csignal>
#include <cstring>
#include <cctype>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "mqtt/client.h"

const std::string DFLT_ADDRESS("tcp://localhost:1883");
const std::string DFLT_CLIENTID("StdoutSubcriber");
const std::string TOPIC("hello");

const mqtt::QoS QOS = mqtt::QoS::at_least_once;
const long TIMEOUT = 10000L;
volatile int toStop = 0;

void finish_handler(int sig)
{
	signal(SIGINT, NULL);
	toStop = 1;
}

/////////////////////////////////////////////////////////////////////////////

class action_listener : public virtual mqtt::iaction_listener
{
	std::string name_;

	virtual void on_failure(const mqtt::itoken& tok)
	{
		std::cout << name_ << " failure";
		if (tok.get_message_id() != 0)
			std::cout << " (token: " << tok.get_message_id() << ")" << std::endl;
		std::cout << std::endl;
	}

	virtual void on_success(const mqtt::itoken& tok)
	{
		std::cout << name_ << " success";
		if (tok.get_message_id() != 0)
			std::cout << " (token: " << tok.get_message_id() << ")" << std::endl;
		if (!tok.get_topics().empty())
			std::cout << "\ttoken topic: '" << tok.get_topics()[0] << "', ..." << std::endl;
		std::cout << std::endl;
	}

public:
	action_listener(const std::string& name) : name_(name) {}
};

/////////////////////////////////////////////////////////////////////////////

class callback : public virtual mqtt::callback,
					public virtual mqtt::iaction_listener

{
	int nretry_;
	mqtt::client& cli_;
	action_listener& listener_;

	void reconnect()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		mqtt::connect_options connOpts;
		connOpts.set_keep_alive_interval(20);
		connOpts.set_clean_session(true);

		try {
			cli_.connect(connOpts);
		}
		catch (const mqtt::exception& exc) {
			std::cerr << "Error: " << exc.what() << std::endl;
			exit(1);
		}
	}

	// Re-connection failure
	virtual void on_failure(const mqtt::itoken& tok)
	{
		std::cout << "Reconnection failed." << std::endl;
		if (++nretry_ > 5)
			exit(1);
		reconnect();
	}

	// Re-connection success
	virtual void on_success(const mqtt::itoken& tok)
	{
		std::cout << "Reconnection success" << std::endl;;
		cli_.subscribe(TOPIC, QOS);
	}

	virtual void connection_lost(const std::string& cause)
	{
		std::cout << "\nConnection lost" << std::endl;
		if (!cause.empty())
			std::cout << "\tcause: " << cause << std::endl;

		std::cout << "Reconnecting." << std::endl;
		nretry_ = 0;
		reconnect();
	}

	virtual void message_arrived(const std::string& topic, mqtt::message_ptr msg) {
		std::cout << "Message arrived" << std::endl;
		std::cout << "\ttopic: '" << topic << "'" << std::endl;
		std::cout << "\t'" << msg->to_str() << "'\n" << std::endl;
	}

	virtual void delivery_complete(mqtt::idelivery_token_ptr token) {}

public:
	callback(mqtt::client& cli, action_listener& listener)
				: nretry_(0), cli_(cli), listener_(listener) {}
};

/////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	std::string address  = (argc > 1) ? std::string(argv[1]) : DFLT_ADDRESS;
	std::string clientID = (argc > 2) ? std::string(argv[2]) : DFLT_CLIENTID;

	mqtt::client client(address, clientID);
	action_listener subListener("Subscription");

	callback cb(client, subListener);
	client.set_callback(cb);

	mqtt::connect_options connOpts;
	connOpts.set_keep_alive_interval(20);
	connOpts.set_clean_session(true);

	try {
		std::cout << "Connecting..." << std::flush;
		client.connect(connOpts);
		std::cout << "OK" << std::endl;

		std::cout << "Subscribing to topic " << TOPIC << "\n"
			<< "for client " << clientID
			<< " using QoS" << QOS << "\n\n" << std::endl;
		client.subscribe(TOPIC, QOS);

		std::cout << "Press Ctrl+C to quit\n" << std::endl;
		while (!toStop)
			;

		std::cout << "Unsubscribing from topic " << TOPIC
			<< "\n\n" << std::endl;
		client.unsubscribe(TOPIC);

		std::cout << "Disconnecting..." << std::flush;
		client.disconnect();
		std::cout << "OK" << std::endl;
	}
	catch (const mqtt::exception& exc) {
		std::cerr << "Error: " << exc.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
