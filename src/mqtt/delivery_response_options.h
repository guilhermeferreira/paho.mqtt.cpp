/////////////////////////////////////////////////////////////////////////////
/// @file delivery_response_options.h
/// Implementation of the class 'delivery_response_options'
/// @date 25-Jan-2017
/////////////////////////////////////////////////////////////////////////////

#ifndef __mqtt_delivery_response_options_h
#define __mqtt_delivery_response_options_h

extern "C" {
	#include "MQTTAsync.h"
}

#include "mqtt/delivery_token.h"

namespace mqtt {

/////////////////////////////////////////////////////////////////////////////
//							delivery_response_options
/////////////////////////////////////////////////////////////////////////////

/**
 * The response options for asynchronous calls targeted at delivery.
 * Each of these objects is tied to a specific delivery_token.
 */
class delivery_response_options
{
	/** The underlying C structure */
	MQTTAsync_responseOptions opts_;

	/** The client has special access */
	friend class async_client;

public:
	/**
	 * Create an empty delivery response object.
	 */
	delivery_response_options();
	/**
	 * Creates a response object tied to the specific delivery token.
	 * @param dtok A delivery token to be used as the context.
	 */
	delivery_response_options(delivery_token* dtok);
	/**
	 * Sets the callback context to a delivery token.
	 * @param tok The delivery token to be used as the callback context.
	 */
	void set_context(delivery_token* dtok) {
		opts_.context = dtok;
	}

	/**
	 * Synchronize the token's (context) message ID with the message ID from
	 * delivery_response_options. Because the delivery_response_options's message
	 * ID is updated by the Paho MQTT C right after the message is sent, but the
	 * token's message ID is updated only after the response arrives.
	 */
	void update_message_id();
};

/////////////////////////////////////////////////////////////////////////////
// end namespace 'mqtt'
}

#endif		// __mqtt_delivery_response_options_h
