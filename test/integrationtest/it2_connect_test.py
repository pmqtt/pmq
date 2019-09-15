#it-2 tested is possible to connect multiple times to the message broker on port 1883

from subprocess import Popen, PIPE
import paho.mqtt.client as paho
import sys
import time

broker="127.0.0.1"
port=1883

process = Popen(['../../PMQ'], stdout=PIPE, stderr=PIPE)
time.sleep(1)
mqtt = paho.Client('IT-2')
mqtt.loop_start()
mqtt.connect(broker,port)

loop = 1

def on_connect_test(client, userdata, flags, rc):
    global loop
    mqtt.disconnect()
    mqtt.loop_stop()
    print 'disconnect loop 1'
    loop += 1


mqtt.on_connect = on_connect_test
while loop == 1 :
    time.sleep(1)
    continue
print 'test 2'

mqtt2 = paho.Client('IT-2')
mqtt2.loop_start()
mqtt2.connect(broker,port)


def on_connect_test2(client, userdata, flags, rc):
    global loop
    print "on connect test2"
    mqtt2.disconnect()
    mqtt2.loop_stop()
    loop += 1

mqtt2.on_connect = on_connect_test2

while loop == 2 :
    time.sleep(1)
    continue
print "test 3"
mqtt3 = paho.Client('IT-2')
mqtt3.loop_start()
mqtt3.connect(broker,port)

def on_connect_test3(client, userdata, flags, rc):
    global loop
    print "on connect test3"
    loop += 1
 #   process.kill()

mqtt3.on_connect = on_connect_test3
while loop == 3:
    time.sleep(1)
    continue
print 'end_loop'
mqtt3.loop_stop()
sys.exit(0)
process.kill()