# PMQ: MQTT Message Broker and Message bus


PMQ will be a high-performance, distributed MQTT message broker and message bus. 

PMQ implements the MQTT 3.1 and 3.1.1 specifiaction with qualaty of service 1.

### Roadmap
* REST API to configure and manage PMQ Message Broker
* Support QOS 2
* Support MQTT 5
* Support WILL messages
* Support Wildcard subscriptions
* Support Authentification -  **Finished!**
* Support TLS - **Finished!**
* Support for Websockets

### Contribution
Everybody is welcome!

### Releated projects
* eclipse mosquitto https://github.com/eclipse/mosquitto
* vernemq https://github.com/vernemq/vernemq

### Building PMQ

Note: PMQ requires 
* BOOST 1.65 or newer 
* microsofts cpprestsdk

```shell
$ cd $PMQ
$ cmake .
$ make
```
#### Troubleshooting
On MAC OS X I have discovered, that buiding PMQ with cpprestsdk is a little bit difficult.
If you see this error message from cmake
```shell
Could NOT find OpenSSL, try to set the path to OpenSSL root folder in the
  system variable OPENSSL_ROOT_DIR (missing: OPENSSL_INCLUDE_DIR)
```
Try to call cmake with this command
```shell
$cmake -DOPENSSL_ROOT_DIR=[PATH TO OPENSSL_ROOT_DIR e.g  /usr/local/Cellar/openssl/1.0.2p/]
```

### Starting PMQ

Once you've successfully built PMQ, you can start the server with the following
commands:

```shell
$ cd $PMQ/
$ ./PMQ
```
PMQ will start on port 1883

### Starting PMQ with TLS support
```shell
$ cd $PMQ/
$ ./PMQ  --tls-certificat [server certificat] --tls-private-key [private key file] --tls-dh-file [Diffie file]
```

### Starting PMQ with permited anonymous connection
```
$ ./PMQ --anyonymous-login false
```
Now the server allows only connection with user name and password.
To set a user and password, you have to use the REST interface.
The REST interface is callable for example by curl with this command
```
curl -d '{"user":"pmqtt", "password":"test1"}' -H 'Content-Type: application/json' -X POST http://localhost:1884/rest/api/v0.1/create_user
```

### Backlog



