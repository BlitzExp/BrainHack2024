import requests
import time

def consume_api(message):
    # URL de tu API
    api_url = 'http://10.43.44.106:8080//receive_data'

    # Datos para enviar a la API
    data = {'message': message}

    # Realizar la solicitud a la API
    response = requests.post(api_url, json=data)

    # Verificar si la solicitud fue exitosa
    if response.status_code == 200:
        print('Mensaje enviado correctamente al servidor Flask')
    else:
        print(response)
        print('Error al enviar el mensaje al servidor Flask')




def main():
    # Bucle infinito para enviar mensajes al servidor
    while True:
        # Solicitar al usuario que ingrese un mensaje
        message = input("Ingrese su mensaje: ")
        consume_api(message)
        time.sleep(5)  # Esperar 5 segundos antes de enviar el próximo mensaje

if __name__ == '__main__':
    main()