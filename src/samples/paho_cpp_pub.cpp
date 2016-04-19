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

#include <chrono>
#include <iostream>
#include <string>
#include <thread>	// For sleep

#include "mqtt/client.h"

const std::string DFLT_ADDRESS("tcp://localhost:1883");
const std::string DFLT_CLIENTID("StdinPublisher");
const std::string TOPIC("hello");

const mqtt::QoS QOS = mqtt::QoS::at_least_once;
const long TIMEOUT = 10000L;
volatile int toStop = 0;

/////////////////////////////////////////////////////////////////////////////

/**
 * A class to handle signals
 */
class signal_handler
{
public:
	static void handle_signal(int signum)
	{
		signal(signum, handler);
	}

private:
	static void handler(int sig)
	{
		signal(SIGINT, NULL);

		toStop = 1;
	}

};

/////////////////////////////////////////////////////////////////////////////

/**
 * A callback class for use with the main MQTT client.
 */
class callback : public virtual mqtt::callback
{
public:
	virtual void connection_lost(const std::string& cause)
	{
		std::cout << "\nConnection lost" << std::endl;
		if (!cause.empty())
			std::cout << "\tcause: " << cause << std::endl;
	}

	// We're not subscribed to anything, so this should never be called.
	virtual void message_arrived(const std::string& topic, mqtt::message_ptr msg) {}

	virtual void delivery_complete(mqtt::idelivery_token_ptr tok)
	{
		std::cout << (tok ? tok->get_message_id() : -1) << "... OK" << std::endl;
	}
};

/////////////////////////////////////////////////////////////////////////////

/**
 * A base action listener.
 */
class action_listener : public virtual mqtt::iaction_listener
{
protected:
	virtual void on_failure(const mqtt::itoken& tok)
	{
		std::cout << "\n\tListener: Failure on token: " 
			<< tok.get_message_id() << std::endl;
	}

	virtual void on_success(const mqtt::itoken& tok)
	{
		std::cout << "\n\tListener: Success on token: " 
			<< tok.get_message_id() << std::endl;
	}
};

/////////////////////////////////////////////////////////////////////////////

/**
 * A derived action listener for publish events.
 */
class delivery_action_listener : public action_listener
{
	bool done_;

	virtual void on_failure(const mqtt::itoken& tok)
	{
		action_listener::on_failure(tok);
		done_ = true;
	}

	virtual void on_success(const mqtt::itoken& tok)
	{
		action_listener::on_success(tok);
		done_ = true;
	}

public:
	delivery_action_listener() : done_(false) {}

	bool is_done() const
	{
		return done_;
	}
};

/////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	std::string address  = (argc > 1) ? std::string(argv[1]) : DFLT_ADDRESS;
	std::string clientID = (argc > 2) ? std::string(argv[2]) : DFLT_CLIENTID;

	mqtt::client client(address, clientID);

	callback cb;
	client.set_callback(cb);

	signal_handler::handle_signal(SIGINT);
	signal_handler::handle_signal(SIGTERM);

	mqtt::connect_options connOpts;
	connOpts.set_keep_alive_interval(20);
	connOpts.set_clean_session(true);

	try {
		std::cout << "Connecting..." << std::flush;
		client.connect(connOpts);
		std::cout << "OK" << std::endl;

		while (!toStop) {
			std::cout << "Message payload: " << std::flush;
			std::string payload;
			std::getline(std::cin, payload);

			std::cout << "Sending message: " << std::flush;
			mqtt::message_ptr pubmsg = std::make_shared<mqtt::message>(payload);
			pubmsg->set_qos(QOS);
			client.publish(TOPIC, pubmsg);
		}

		// Disconnect
		std::cout << "Disconnecting..." << std::flush;
		client.disconnect();
		std::cout << "OK" << std::endl;

	} catch (const mqtt::exception& exc) {
		std::cerr << "Error: " << exc.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
