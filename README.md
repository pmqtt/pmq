# PMQ: MQTT Message Broker and Message bus


PMQ will be a high-performance, distributed MQTT message broker and message bus. 

PMQ implements the MQTT 3.1 and 3.1.1 specifiaction with qualaty of service 1.

### Roadmap
* REST API to configure and manage PMQ Message Broker
* Support QOS 2
* Support MQTT 5
* Support Authentification
* Support TLS
* Support for Websockets

### Contribution
Everybody is welcome!

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

