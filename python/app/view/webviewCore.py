from PyQt5.QtCore import QObject, pyqtSlot, pyqtSignal


class Bridge(QObject):
    sendToJs = pyqtSignal(str)

    def __init__(self, onReceiveFromJs):
        super().__init__()
        self.onReceiveFromJs = onReceiveFromJs
        

    @pyqtSlot(str)
    def receiveFromJs(self, message):
        self.onReceiveFromJs(message)