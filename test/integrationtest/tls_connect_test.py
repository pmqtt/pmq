from subprocess import Popen, PIPE
import paho.mqtt.client as paho
import sys
import time


def on_connect_test(client, userdata, flags, rc):
    sys.exit(0)

broker="127.0.0.1"
port=1883
mqtt = paho.Client('IT-1')
mqtt.tls_set(ca_certs='../../certificate/ca.crt', certfile='../../certificate/client.crt', keyfile='../../certificate/client.key')
mqtt.tls_insecure_set(True)
mqtt.connect(broker,port)
mqtt.on_connect = on_connect_test
mqtt.loop_forever()
