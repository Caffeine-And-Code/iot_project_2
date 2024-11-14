from app.IO.InterfaceIO import InterfaceIO
import queue
from threading import Thread
import time
from random import randint

class TestIO(InterfaceIO):
    
    def __init__(self, onNewMessage, newMessageWait = 10):
        super().__init__(onNewMessage)
        self.newMessageWait = newMessageWait

    def listen(self):
        t = Thread(target=self.listen_runtime, args=[self.readQueue, self.newMessageWait])
        t.start()

    def listen_runtime(self, readQueue: queue.Queue, wait: int):
        while True:
            readQueue.put({"fluidLevel": 50, "temperature": randint(-20, 51)})
            time.sleep(wait)
        

    def sendMessage(self, message):
        print(f"IO: {message}")