// disconnect_options.cpp

#include "mqtt/disconnect_options.h"

namespace mqtt {

/////////////////////////////////////////////////////////////////////////////

disconnect_options::disconnect_options() 
		: opts_(MQTTAsync_disconnectOptions_initializer) 
{
}

disconnect_options::disconnect_options(int timeout, token_ptr tok)
		: disconnect_options()
{
	set_timeout(timeout);
	set_context(tok);
}

void disconnect_options::set_context(token_ptr tok)
{
	opts_.context = tok.get();

	if (tok) {
		opts_.onSuccess = &token::on_success;
		opts_.onFailure = &token::on_failure;
	}
	else {
		opts_.onSuccess = nullptr;
		opts_.onFailure = nullptr;
	}
}

/////////////////////////////////////////////////////////////////////////////
// end namespace 'mqtt'
}

