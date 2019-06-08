# PMQ: MQTT Message Broker and Message bus


PMQ will be a high-performance, distributed MQTT message broker and messagebus. 

PMQ implements the MQTT 3.1 and 3.1.1 specifiaction with qualatiy of service 1.

### Roadmap
* Support QOS 2
* Support MQTT 5
* Support Authentification
* Support TLS
* Support for Websockets

### Contribution
Everybody is welcome!

### Building PMQ

Note: PMQ requires BOOST 1.65 or newer.


```shell
$ cd $PMQ
$ cmake .
$ make
```    

### Starting PMQ

Once you've successfully built PMQ, you can start the server with the following
commands:

```shell
$ cd $PMQ/
$ ./PMQ
```

