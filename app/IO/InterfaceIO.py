import queue

class InterfaceIO:
    readQueue = queue.Queue()
    def __init__(self, onNewMessage):
        self.onNewMessage = onNewMessage

    def listen(self):
        pass

    def sendMessage(self, message):
        pass