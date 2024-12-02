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
        self.running = True

    def listen(self):
        self.t = Thread(target=self.listen_runtime, args=[self.messageQueue, self.readQueue])
        self.running = True
        self.t.start()
    
    def formatMessage(self,message):
        # format of the message => valueW or valueT or errorW or errorT
        if "ET" in message:
            return {"errorTemp": "ERROR"}
        elif "EW" in message:
            return {"errorFluid": "ERROR"}
        elif "W" in message:
            return {"fluidLevel": message[:-1]}
        elif "T" in message:
            return {"temperature": message[:-1]}
        

    def listen_runtime(self, messageQueue: queue.Queue, readQueue: queue.Queue):
        # Initialize the serial connection
        with Serial(config.serialPort, config.baudRate, timeout=0.1) as ser:
            while self.running:
                line = ser.readline().decode('utf-8').strip()
                if line and line != "W" and line != "T":
                    readQueue.put(self.formatMessage(line))
                while not messageQueue.empty():
                    message = f"{messageQueue.get()}"
                    ser.write(message.encode("utf-8"))
    
    
        
                    
    def close(self):
        self.running = False
        self.messageQueue = queue.Queue()
        self.t.join()

    def sendMessage(self, message):
        self.messageQueue.put(message)


