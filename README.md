
# PMQ: MQTT Message Broker and Message bus


PMQ will be a high-performance, distributed MQTT broker (aka. message broker ) and message bus. 

PMQ implements the MQTT 3.1, 3.1.1 specifiaction with qualaty of service 1 and shared subscription from MQTT 5

### Feature
#### Distributed configuration 
With PMQ it is possible to distribute configurations. 
Imagine that you have to configure many microservices and they do not have a REST interface.
In this case, the distribution of configurations via PMQ can be helpful. Configurations are transferred in JSON format 
and defined as YAML.The configuration is organized hierarchically. The hierarchy is three-level global, General for a client family and Specific for a single client. 

### Roadmap
* REST API to configure and manage PMQ Message Broker
* Distribute configuration to broker clients **Finished** 
* Support QOS 2
    * [x] QOS 2 receiver case
    * [ ] QOS 2 sender case
* Support MQTT 5
    * [x] shared subscription **Finished**
* Support WILL messages **Finished**
* Support Wildcard subscriptions **Finished**
    * [x] \# Wildcard (Multi level Wildcard) 
    * [x] \+ Wildcard (Single level Wildcard)
* Support Authentification: Client authentificate server -  **Finished!**
* Support Authentification: Server authentificate client -  **Finished!**
* Support TLS - **Finished!**
* Support for Websockets

### Contribution
Everybody is welcome!
If you want to start developing for this project, you can use the development 
docker container. 
To generate the image, use follow command
```
$ cd dockerfiles/dev_image
$ docker build -t pmqtt/dev_test .
```
After generation you can use the container
```
$ docker run --it -v[path to pmq]:/pmq pmqtt/dev_test /bin/bash
```
or use the docker image from https://hub.docker.com
```
$ docker pull pmqtt/dev
$ docker run -it -v[path to pmq]:/pmq pmqtt/dev /bin/bash
```


### Releated projects
* eclipse mosquitto https://github.com/eclipse/mosquitto
* vernemq https://github.com/vernemq/vernemq

### Building PMQ

Note: PMQ requires 
* BOOST 1.65 or newer 
* microsofts cpprestsdk
* yaml-cpp

```shell
$ cd $PMQ
$ cmake .
$ make
$ sh run_test.sh
```

#### Troubleshooting
On MAC OS X I have recognized that building PMQ with cpprestsdk is a little bit difficult.
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
PMQ will start on port 1883. It is also possible to start PMQ with a configuration file
```
$ ./PMQ -c configuration.yaml
```

### Starting PMQ with TLS support
```shell
$ cd $PMQ/
$ ./PMQ  --tls-certificat [server certificat] --tls-private-key [private key file] --tls-dh-file [Diffie file]
```

### Starting PMQ with permited anonymous connection
```
$ ./PMQ --anonymous-login false
```
Now the server allows only connection with user name and password.
To set a user and password, you have to use the REST interface.
The REST interface is callable for example by curl with this command
```
$ curl -d '{"user":"pmqtt", "password":"test1"}' -H 'Content-Type: application/json' -X POST http://localhost:1884/rest/api/v0.1/create_user
```
### Show all connected clients with will messages
To see all clients with it's will messages and will topics, 
use the REST API of PMQ. For example, to show the clients
with curl, use the following command
```
$ curl http://localhost:1884/rest/api/v0.1/get_will_messages
```

### How to, distribute configuration
```shell
$ ./PMQ  --client-configuration-file configuration.yaml
```
The format of the configuration file must look like this
````yaml
# General configuration for all clients
GLOBAL:
- PROXY 127.0.0.14:8888
- NTP 127.0.0.15:8177

# General configuration for a client family
MACHINE_SERVICE_01:
- CONNECTION 192.168.0.133

# Specific configuration for a client
MACHINE_SERVICE_01/02:
- PORT 2001

MACHINE_SERVICE_01/03:
- PORT 2002
````
To subscribe for the configuration, you have to use the special topic $CONFIG_MODULE/[YAML RULE].
For example with mosquitto_sub:
```shell
$ mosquitto_sub -t '$CONFIG_MODULE/MACHINE_SERVICE_01/02'
```
You will received from PMQ this message:
```JSON
{
  "GLOBAL":
  {
    "PROXY":"127.0.0.14:8888",
    "NTP":"127.0.0.15:8177"
  },
  "GENERAL":
  {
    "CONNECTION":"192.168.0.133"
  },
  "SPECIFIC":
  {
    "PORT":"2001"
  }
}
```


