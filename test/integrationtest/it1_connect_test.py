#it-1 tested is possible to connect to the message broker on port 1883

from subprocess import Popen, PIPE
import paho.mqtt.client as paho
import sys
import time


process = Popen(['../../PMQ'], stdout=PIPE, stderr=PIPE)
time.sleep(1)
def on_connect_test(client, userdata, flags, rc):
    process.kill()
    sys.exit(0)

broker="127.0.0.1"
port=1883
mqtt = paho.Client('IT-1')
mqtt.connect(broker,port)
mqtt.on_connect = on_connect_test
mqtt.loop_forever()
