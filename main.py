from flask import Flask, render_template, jsonify
import serial
import threading
import time

# Configura la tua porta seriale
SERIAL_PORT = 'COM3'  # o '/dev/ttyUSB0' su Linux
BAUD_RATE = 9600

app = Flask(__name__)
#TODO: delete the comment to enable the serial port
#ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)

# Variabile globale per memorizzare i dati seriali
serial_data = ""

# Funzione per leggere i dati dalla porta seriale
def read_serial():
    global serial_data
    while True:
        if ser.in_waiting > 0:
            serial_data = ser.readline().decode('utf-8').strip()
            print(f"Dato letto dalla seriale: {serial_data}")
        time.sleep(0.1)

# Avvia il thread per la lettura seriale
#TODO: Disabilita il thread per ora, per evitare problemi con la seriale
#thread = threading.Thread(target=read_serial)
#thread.daemon = True
#thread.start()

# Route per la pagina principale
@app.route('/')
def index():
    return render_template('index.html')

# Endpoint API per ottenere i dati seriali
@app.route('/api/data')
def get_data():
    return jsonify({"data": serial_data})

if __name__ == '__main__':
    app.run(debug=True)
