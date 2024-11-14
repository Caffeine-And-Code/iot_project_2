from app.config.Config import Config
config = Config()

from app.view.view import View
from app.model.Model import Model
from app.IO import TestIO, SerialIO


class Controller:

    def __init__(self):
        self.view = View(self.onNewMessage)
        if config.useVirtualSerial:
            self.serialIO = TestIO.TestIO(self.onNewSerialMessage)
        else:
            self.serialIO = SerialIO.SerialIO(self.onNewSerialMessage)
        self.model = Model(self.sendMessage, self.serialIO)
        self.serialIO.listen()

    def start(self):
        self.view.render()
        # stop

    def onNewMessage(self, message):
        self.model.onNewMessage(message)
        return
    
    def onNewSerialMessage(self, message):
        self.model.onNewSerialMessage(message)
    
    def sendMessage(self, message):
        self.view.sendMessage(message)
        return
    
    def sendMessageToSerial(self, message):
        self.serialIO.sendMessage(message)