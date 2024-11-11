import time
from multiprocessing import Process
from random import randint
from app.IO.InterfaceIO import InterfaceIO

class Model:
    number = 0

    def __init__(self, sendMessage, serialIO: InterfaceIO):
        self.sendMessage = sendMessage
        self.serialIO = serialIO

    def onNewMessage(self, message):
        while not self.serialIO.readQueue.empty():
            self.number = self.serialIO.readQueue.get()
        self.sendMessage(self.number)
        self.serialIO.sendMessage("Hello Serial")

    def onNewSerialMessage(self, message):
        return

    