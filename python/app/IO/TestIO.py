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

    def listen_runtime(self, readQueue: queue.Queue, wait: int):
        while self.running:
            readQueue.put(randint(0,100) + "W")
            readQueue.put(randint(-20, 51) + "T")
            time.sleep(wait)
    
    def close(self):
        self.running = False
        self.messageQueue = queue.Queue()
        self.t.join()

    def sendMessage(self, message):
        print(f"IO: {message}")