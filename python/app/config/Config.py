from dotenv import load_dotenv
import os

class Config:
    initialized = True
    debug = False
    serialPort = ""
    baudRate = 0
    useVirtualSerial = False

    def __init__(self):
        load_dotenv()
        self.debug = os.getenv("DEBUG") or False
        self.serialPort = os.getenv("SERIAL_PORT") or "COM17"
        self.baudRate = os.getenv("BAUD_RATE") or 9600
        self.useVirtualSerial = os.getenv("USE_VIRTUAL_SERIAL") or False