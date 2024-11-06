from app.view.webview import WebViewBuilder
from PyQt5.QtCore import pyqtSignal
import os

class View:

    def __init__(self, onNewMessage):
        self.onNewMessageCallback = onNewMessage
        self.webviewBuilder = WebViewBuilder()
        self.rendered = pyqtSignal()

    def render(self):
        self.webviewBuilder.setTitle("IOT Project 2")
        self.webviewBuilder.setUrlFromLocalFile(os.path.abspath("public/templates/index.html"))
        self.webviewBuilder.setOnNewMessage(self.onNewMessage)
        self.webviewBuilder.render()


    def onNewMessage(self, message):
        self.onNewMessageCallback(message)

    def sendMessage(self, message):
        self.webviewBuilder.sendMessage(message)