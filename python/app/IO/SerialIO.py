from serial import Serial
from threading import Thread
import time
import queue
from app.IO.InterfaceIO import InterfaceIO
from app.controller.Controller import config

class SerialIO(InterfaceIO):
    currentValue = 0
    messageQueue = queue.Queue()

    def __init__(self, onNewMessage):
        super().__init__(onNewMessage)

    
    def listen(self ):
        t = Thread(target=self.listen_runtime, args=[self.messageQueue, self.readQueue])
        t.start()

    def listen_runtime(self, messageQueue: queue.Queue, readQueue: queue.Queue):
        # Initialize the serial connection
        with Serial(config.serialPort, config.baudRate, timeout=0.1) as ser:
            while True:
                line = ser.readline().decode('utf-8').strip()
                
                if line.isdigit():
                    number = int(line)
                    if 0 <= number <= 100:
                        readQueue.put(number)
                time.sleep(0.1)
                while not messageQueue.empty():
                    message = f"{messageQueue.get()}"
                    ser.write(message.encode("utf-8"))


    def sendMessage(self, message):
        self.messageQueue.put(message)


