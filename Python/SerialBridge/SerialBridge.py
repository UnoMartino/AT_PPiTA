import serial
import threading
# import PySimpleGUI as sg

bridgeActive = False
serialPort = 'COM18'
baudRate = 115200

def serialWatcher():
    global bridgeActive

    data = serialPort.read()
    while bridgeActive:
        data = serialPort.read()
        print(data.decode(errors='replace'), end='', flush=True)
        
def startSerialBridge(port, baud):
    global serialPort, bridgeActive
    ok = True
    bridgeActive = True

    try:
        serialPort = serial.Serial(port, baud)
    except serial.SerialException:
        ok = False

    if ok:
        serialPort.timeout = 0.4
        watcherThread = threading.Thread(target=serialWatcher)
        watcherThread.start()
    return ok

def stopSerialBridge():
    global serialPort, bridgeActive
    bridgeActive = False
    del serialPort

def sendData(data):
    global serialPort
    serialPort.write(data.encode())



# layout = [  [sg.Text("Serial Bridge")],
#             [sg.Multiline(disabled=True, size=(50, 10), key='output')],
#             [sg.Button('Start', key="-START-"), sg.Button('Stop', key="-STOP-")] ]

if __name__ == '__main__':

    # window = sg.Window('Serial Bridge', layout)

    startSerialBridge(serialPort, baudRate)

    print("Serial bridge started. Type '/exit' to stop the bridge.")
    print("Type '/start' to restart the bridge.")

    while True:
        # event = window.read()
        data = input()
        if data == '/exit':
            stopSerialBridge()
        elif not bridgeActive and data == '/start':
            startSerialBridge(serialPort, baudRate)
        else:
            sendData(data)
        

            



