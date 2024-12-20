from app.IO.InterfaceIO import InterfaceIO
import queue
from threading import Thread
import time
from random import randint

class TestIO(InterfaceIO):
    
    def __init__(self, onNewMessage, newMessageWait = 10):
        super().__init__(onNewMessage)
        self.newMessageWait = newMessageWait
        self.running = True

    def listen(self):
        self.t = Thread(target=self.listen_runtime, args=[self.readQueue, self.newMessageWait])
        self.t.start()
        
    def formatMessage(self,message):
        # format of the message => valueW or valueT or errorW or errorT
        if "ET" == message:
            return {"errorTemp": "ERROR"}
        elif "EW" == message:
            return {"errorFluid": "ERROR"}
        elif "W" in message:
            return {"fluidLevel": message[:-1]}
        elif "T" in message:
            return {"temperature": message[:-1]}

    def listen_runtime(self, readQueue: queue.Queue, wait: int):
        while self.running:
            readQueue.put(self.formatMessage("EW"))
            readQueue.put(self.formatMessage("ET"))
            print(self.formatMessage(str(randint(0,100))+"W"))
            print(self.formatMessage(str(randint(-20, 51))+"T"))
            print(self.formatMessage("ET"))
            print(self.formatMessage("EW"))
            
            
            time.sleep(wait)
    
    def close(self):
        self.running = False
        self.messageQueue = queue.Queue()
        self.t.join()

    def sendMessage(self, message):
        print(f"IO: {message}")