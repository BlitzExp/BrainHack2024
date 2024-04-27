from flask import Flask, jsonify, request
import requests

app = Flask(__name__)

@app.route('/')
def root():
    return "Home"

@app.route('/receive_data', methods=['POST'])
def receive_data():
    data = request.json  # Obtener los datos enviados por el cliente
    # Aquí puedes procesar los datos si es necesario antes de enviarlos a C++
    
    # Puedes imprimir los datos recibidos para verificarlos
    print("Datos recibidos en Python:", data)
    
    # Ejemplo de cómo procesar los datos y enviar una respuesta
    # Puedes ajustar esta lógica según tus necesidades
    processed_data = {"message": "Webi wabo"}
    
    # Retorna la respuesta en formato JSON
    return jsonify(processed_data)

if __name__ == '__main__':
    app.run(host='127.0.0.1', port=8080)