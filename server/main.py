from flask import Flask, jsonify, request
import socket

app = Flask(__name__)

# Lista para almacenar las conexiones de clientes
client_connections = []

receivedMessage = None

@app.route('/')
def root():
    return "Home"

@app.route('/receive_data', methods=['POST'])
def receive_data():
    global receivedMessage

    data = request.json  # Obtener los datos enviados por el cliente
    # Aquí puedes procesar los datos si es necesario antes de enviarlos a C++
    receivedMessage = data.get('message', 'No se encontró mensaje')

    # Puedes imprimir los datos recibidos para verificarlos
    print("Datos recibidos en Python:", receivedMessage)
    
    return jsonify({"status": "OK"})

@app.route('/send_message', methods=['GET'])
def send_message():
    global receivedMessage
    if receivedMessage:
        return jsonify({"message": receivedMessage})
    else:
        return jsonify({"message": "No se ha recibido informacion"})

def run_server():
    # Iniciar el servidor Flask
    app.run(host='127.0.0.1', port=8080)

    # Crear un socket para escuchar las conexiones TCP
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('127.0.0.1', 8081))
    server_socket.listen(5)

    print("Servidor en ejecución. Esperando conexiones...")

    # Ciclo para manejar las conexiones entrantes
    while True:
        client_socket, client_address = server_socket.accept()
        print("Conexión establecida con el cliente:", client_address)
        client_connections.append(client_socket)

        # Manejar la conversación con el cliente
        while True:
            message = client_socket.recv(1024).decode()
            if message.lower() == "quit":
                break
            print("Mensaje del cliente:", message)
        
        # Cerrar la conexión con el cliente
        client_socket.close()
        print("Conexión con el cliente cerrada.")

    # Cerrar el socket del servidor
    server_socket.close()

if __name__ == '__main__':
    run_server()