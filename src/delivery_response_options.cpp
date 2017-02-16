// delivery_response_options.cpp

#include "mqtt/delivery_response_options.h"

namespace mqtt {

/////////////////////////////////////////////////////////////////////////////

delivery_response_options::delivery_response_options()
		: opts_(MQTTAsync_responseOptions_initializer)
{
	opts_.onSuccess = &delivery_token::on_success;
	opts_.onFailure = &delivery_token::on_failure;
}

delivery_response_options::delivery_response_options(delivery_token* tok)
		: delivery_response_options()
{
	set_context(tok);
}

/////////////////////////////////////////////////////////////////////////////
// end namespace 'mqtt'
}
