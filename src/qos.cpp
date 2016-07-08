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
 *******************************************************************************/

#include "mqtt/qos.h"

#include "mqtt/exception.h"

namespace mqtt {

/////////////////////////////////////////////////////////////////////////////

void validate_qos(QoS qos) {
	if ((static_cast<int>(qos) < 0) || (2 < static_cast<int>(qos)))
		throw mqtt::exception(MQTTASYNC_BAD_QOS);
}

std::ostream& operator<<(std::ostream& os, QoS qos) {
	int iqos = static_cast<int>(qos);
	os << iqos;
	return os;
}

/////////////////////////////////////////////////////////////////////////////

} // end namespace mqtt

