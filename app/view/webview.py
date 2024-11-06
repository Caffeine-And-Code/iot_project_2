import sys
from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5.QtCore import QUrl
from PyQt5.QtWebEngineWidgets import QWebEngineView
from PyQt5.QtWebChannel import QWebChannel

from app.view.webviewCore import Bridge

class WebViewBuilder:

    def __init__(self):
        self.url = ""
        self.title = ""
        self.geometry = {"ax":100, "ay":100, "aw":800, "ah":600 }
        self.onNewMessage = lambda x: print(x)
        self.jsListenFunction = "receiveMessageFromPython"
        self.window = None
        self.browser = None
        self.initialized = False

    def setUrlFromLocalFile(self, url):
        self.url = QUrl.fromLocalFile(url)
        return self
    
    def setTitle(self, title):
        self.title = title
        return self
    
    def setSize(self, ax, ay, aw, ah):
        self.geometry = {"ax":ax, "ay":ay, "aw":aw, "ah":ah }
        return self
    
    def setOnNewMessage(self, onNewMessage):
        self.onNewMessage = onNewMessage
        return self
    
    def setJSListenFunction(self, jsListenFunction):
        self.jsListenFunction = jsListenFunction
        return self
    
    def render(self):
        app = QApplication(sys.argv)
        window = QMainWindow()
        window.setWindowTitle(self.title)
        window.setGeometry(self.geometry.get("ax"), self.geometry.get("ay"), self.geometry.get("aw"),self.geometry.get("ah"))
        
        bridge = Bridge(self.onNewMessage)
        bridge.sendToJs.connect(self.sendMessage)

        channel = QWebChannel()
        channel.registerObject("bridge", bridge)

        browser = QWebEngineView()
        browser.setUrl(self.url)
        browser.page().setWebChannel(channel)

        window.setCentralWidget(browser)
        window.show()

        self.window = window
        self.browser = browser
        self.initialized = True
        
        sys.exit(app.exec_())

        return self
    
    def sendMessage(self, message):
        if self.initialized:
            self.browser.page().runJavaScript(f"{self.jsListenFunction}({message})")
    
