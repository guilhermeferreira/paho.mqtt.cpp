# Generates the keys and certificates used for testing SSL features
# of Paho MQTT C++.

BASESUBJ="/C=GB/ST=Derbyshire/L=Derby/O=Mosquitto Project/OU=Sample"

# Certificate Authority
openssl req -out ca.crt -keyout ca.key -new -x509 -days 3650 -extensions v3_ca -subj "${BASESUBJ}/CN=Root CA/" 

# Valid server key and certificate.
openssl genrsa -out server.key 2048
openssl req -out server.csr -key server.key -new -subj "${BASESUBJ}/CN=localhost/"
openssl x509 -out server.crt -in server.csr -req -CA ca.crt -CAkey ca.key -CAcreateserial -days 3650

# Valid client key and certificate.
openssl genrsa -out client.key 2048
openssl req -out client.csr -key client.key -new -config openssl.cnf -subj "${BASESUBJ}/CN=test client/"
openssl x509 -out client.crt -in client.csr -req -CA ca.crt -CAkey ca.key -CAcreateserial -days 3650

# Generate mosquitto.conf
cat mosquitto.conf.template | sed 's|%PWD%|'"$PWD"'|g' > mosquitto.conf

# Generate certificate.h
cat cert.h.template | sed 's|%PWD%|'"$PWD"'|g' > cert.h