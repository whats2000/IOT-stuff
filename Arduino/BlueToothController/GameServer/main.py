from websocket_server import WebsocketServer
import threading
import serial

# Set up the serial port and baud rate
serial_port = 'COM7'
baud_rate = 38400

# Function to send data to all connected clients
def send_to_all_clients(client, server, message):
    server.send_message_to_all(message)

# Callback when a new client connects
def new_client(client, server):
    print(f"New client connected: {client['id']}")

# Callback when a client disconnects
def client_left(client, server):
    print(f"Client disconnected: {client['id']}")

# Read data from serial and send to clients
def read_serial_data(server):
    try:
        ser = serial.Serial(serial_port, baud_rate, timeout=1)
        print(f"Connected to {serial_port} at baud rate {baud_rate}")
    except serial.SerialException as e:
        print(f"Unable to connect to {serial_port}: {e}")
        return

    try:
        while True:
            if ser.inWaiting() > 0:
                received_data = ser.readline().decode('utf-8').rstrip()
                print("Received data:", received_data)
                server.send_message_to_all(received_data)
    except KeyboardInterrupt:
        print("Serial communication terminated")
        ser.close()

# Create a WebSocket server
server = WebsocketServer(host='127.0.0.1', port=9001)
server.set_fn_new_client(new_client)
server.set_fn_client_left(client_left)

# Start the server in a separate thread
threading.Thread(target=server.run_forever).start()

# Read data from serial in the main thread
read_serial_data(server)
