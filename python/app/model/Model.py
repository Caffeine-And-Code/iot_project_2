import time
from multiprocessing import Process
from random import randint
from app.IO.InterfaceIO import InterfaceIO

class Model:

    def __init__(self, sendMessage, serialIO: InterfaceIO):
        self.sendMessage = sendMessage
        self.serialIO = serialIO

    def onNewMessage(self, message):
        while not self.serialIO.readQueue.empty():
            line:str = self.serialIO.readQueue.get()
            self.sendMessage(line)
                
                


    def onNewSerialMessage(self, message):
        return

    