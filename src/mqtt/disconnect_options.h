/////////////////////////////////////////////////////////////////////////////
/// @file disconnect_options.h
/// Implementation of the class 'disconnect_options'
/// @date 26-Aug-2016
/////////////////////////////////////////////////////////////////////////////

#ifndef __mqtt_disconnect_options_h
#define __mqtt_disconnect_options_h

extern "C" {
	#include "MQTTAsync.h"
}

#include <chrono>

#include "mqtt/token.h"

namespace mqtt {

/////////////////////////////////////////////////////////////////////////////

/**
 * Options for disconnecting from an MQTT broker.
 */
class disconnect_options
{
	MQTTAsync_disconnectOptions opts_;

public:
	/**
	 * Create an empty delivery response object.
	 */
	disconnect_options();
	/**
	 * Creates disconnect options tied to the specific delivery token.
	 * @param timeout The timeout to disconnect
	 * @param tok A token to be used as the context.
	 */
	disconnect_options(int timeout, token* tok);
	/**
	 * Creates disconnect options tied to the specific delivery token.
	 * @param timeout The timeout to disconnect
	 * @param tok A token to be used as the context.
	 */
	template <class Rep, class Period>
	disconnect_options(const std::chrono::duration<Rep, Period>& timeout, token* tok)
	: disconnect_options{static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(timeout).count()), tok} {
	}
	/**
	 * Returns the underlying Paho MQTT C struct
	 * @return MQTTAsync_disconnectOptions
	 */
	MQTTAsync_disconnectOptions& get_c_struct() {
		return opts_;
	}
	/**
	 * Sets the timeout for disconnecting. 
	 * This allows for any remaining in-flight messages to be delivered. 
	 * @param timeout The timeout (in milliseconds).
	 */
	void set_timeout(int timeout) { opts_.timeout = timeout; } // TODO 35.2.1
	/**
	 * Sets the timeout for disconnecting.
	 * This allows for any remaining in-flight messages to be delivered.
	 * @param timeout The timeout (any unit).
	 */
	template <class Rep, class Period>
	void set_timeout(const std::chrono::duration<Rep, Period>& timeout) {
		set_timeout(static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(timeout).count()));
	}
	/**
	 * Gets the timeout used for disconnecting. 
	 * @return The timeout for disconnecting (in milliseconds).
	 */
	int get_timeout() const { return opts_.timeout; } // TODO 35.2.1
	/**
	 * Sets the callback context to a delivery token. 
	 * @param tok The delivery token to be used as the callback context.
	 */
	void set_context(token* tok);

	/**
	 * Gets the callback context to a delivery token.
	 * @return The delivery token to be used as the callback context.
	 */
	token* get_context();

};

/////////////////////////////////////////////////////////////////////////////
// end namespace 'mqtt'
}

#endif		// __mqtt_disconnect_options_h

