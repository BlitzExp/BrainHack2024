import UnicornPy
import numpy as np
from sklearn import datasets
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy import stats
import requests

# Función para encontrar la función más cercana basada en la pendiente.
def encontrar_funcion_global(funciones_regresion):
    diferencias = {nombre: 0 for nombre in pendientes_predefinidas.keys()}
    conteo_funciones = {nombre: 0 for nombre in pendientes_predefinidas.keys()}

    # Calcular la suma de diferencias absolutas de las pendientes para cada función.
    for canal, valores in funciones_regresion.items():
        pendiente_actual = valores['pendiente']
        for nombre_funcion, pendientes in pendientes_predefinidas.items():
            if canal in pendientes:  # Asegurarse de que el canal está en las pendientes predefinidas.
                diferencia = abs(pendientes[canal] - pendiente_actual)
                diferencias[nombre_funcion] += diferencia
                conteo_funciones[nombre_funcion] += 1

    # Normalizar las diferencias por el número de canales para cada función.
    for nombre_funcion in diferencias:
        if conteo_funciones[nombre_funcion] > 0:
            diferencias[nombre_funcion] /= conteo_funciones[nombre_funcion]

    # Encontrar la función con la menor diferencia media.
    funcion_cercana = min(diferencias, key=diferencias.get)
    return funcion_cercana

pendientes_swing = {
    "E1": 0.1877644398587976,
    "E2": 0.2392321068072029,
    "E3": -1.1530945079807153,
    "E4": -6.150735353786465,
    "E5": 0.25160346825122176,
    "E6": 0.263647541146612,
    "E7": 0.24045395554670868,
    "E8": 0.25715495997213667
}

pendientes_derecha = {
    "E1": 0.21754460385171207,
    "E2": 0.16304518423201902,
    "E3": -0.48664268504927594,
    "E4": -3.9433296348357296,
    "E5": 0.14581237815019418,
    "E6": 0.07670460187887178,
    "E7": 0.1320641588383265,
    "E8": 0.08681473280575877
}

pendientes_izquierda = {
    "E1": 0.1106139304053834,
    "E2": 0.0812463895155559,
    "E3": -0.51508949836126,
    "E4": -3.0759961821769948,
    "E5": 0.07810462182555084,
    "E6": 0.018406234574195685,
    "E7": 0.04568641733323461,
    "E8": 0.021110538457884066
}

pendientes_arriba = {
    "E1": 0.05853122349260431,
    "E2": 0.03587221850805246,
    "E3": -0.48840923324621965,
    "E4": -2.4714625156222483,
    "E5": 0.03331556354939266,
    "E6": 0.03486698598633076,
    "E7": 0.02774928409264526,
    "E8": 0.02212221934968255
}

pendientes_abajo = {
    "E1": 0.04154264617710029,
    "E2": 0.04227058715668291,
    "E3": -0.425381681050638,
    "E4": -2.040975203446072,
    "E5": 0.040310184565975155,
    "E6": 0.058486990272381516,
    "E7": 0.04662200915075342,
    "E8": 0.04393670835341996
}

pendientes_predefinidas = {
    "Inclinar": pendientes_swing,
    "Derecha": pendientes_derecha,
    "Izquierda": pendientes_izquierda,
    "Abajo": pendientes_abajo,
    "Arriba": pendientes_arriba
}

def main():
    # Specifications for the data acquisition.
    #-------------------------------------------------------------------------------------
    TestsignaleEnabled = False
    FrameLength = 1
    AcquisitionDurationInSeconds = 3
    DataFile = "data.csv"
    
    headers = ["E1", "E2", "E3", "E4", "E5", "E6", "E7", "E8", "AccelX", "AccelY", "AccelZ", "GyroX", "GyroY", "GyroZ", "Battery", "Sample", "UwU"]

    print("Unicorn Acquisition Example")
    print("---------------------------")
    print()

    try:
        # Get available devices.
        #-------------------------------------------------------------------------------------

        # Get available device serials.
        deviceList = UnicornPy.GetAvailableDevices(True)

        if len(deviceList) <= 0 or deviceList is None:
            raise Exception("No device available.Please pair with a Unicorn first.")

        # Print available device serials.
        print("Available devices:")
        i = 0
        for device in deviceList:
            print("#%i %s" % (i,device))
            i+=1

        # Request device selection.
        print()
        deviceID = int(input("Select device by ID #"))
        if deviceID < 0 or deviceID > len(deviceList):
            raise IndexError('The selected device ID is not valid.')

        # Open selected device.
        #-------------------------------------------------------------------------------------
        print()
        print("Trying to connect to '%s'." %deviceList[deviceID])
        device = UnicornPy.Unicorn(deviceList[deviceID])
        print("Connected to '%s'." %deviceList[deviceID])
        print()

        # Create a file to store data.
        file = open(DataFile, "wb")

        # Initialize acquisition members.
        #-------------------------------------------------------------------------------------
        numberOfAcquiredChannels= device.GetNumberOfAcquiredChannels()
        configuration = device.GetConfiguration()

        # Print acquisition configuration
        print("Acquisition Configuration:")
        print("Sampling Rate: %i Hz" %UnicornPy.SamplingRate)
        print("Frame Length: %i" %FrameLength)
        print("Number Of Acquired Channels: %i" %numberOfAcquiredChannels)
        print("Data Acquisition Length: %i s" %AcquisitionDurationInSeconds)
        print()

        # Allocate memory for the acquisition buffer.
        receiveBufferBufferLength = FrameLength * numberOfAcquiredChannels * 4
        receiveBuffer = bytearray(receiveBufferBufferLength)

# Create a file to store data.
        with open(DataFile, "w", newline='') as file:
            # Write the headers first
            file.write(','.join(headers) + '\n')

            # Start data acquisition.
            # -------------------------------------------------------------------------------------
            device.StartAcquisition(TestsignaleEnabled)
            print("Data acquisition started.")

            # Calculate number of get data calls.
            numberOfGetDataCalls = int(AcquisitionDurationInSeconds * UnicornPy.SamplingRate / FrameLength)

            # Limit console update rate to max. 25Hz or slower to prevent acquisition timing issues.
            consoleUpdateRate = max(int((UnicornPy.SamplingRate / FrameLength) / 25), 1)
            print("Data calls: ", numberOfGetDataCalls)
            # Acquisition loop.
            # -------------------------------------------------------------------------------------
            while(True) :
                for i in range(0, numberOfGetDataCalls):
                    # Receives the configured number of samples from the Unicorn device and writes it to the acquisition buffer.
                    device.GetData(FrameLength, receiveBuffer, receiveBufferBufferLength)

                    # Convert receive buffer to numpy float array
                    data = np.frombuffer(receiveBuffer, dtype=np.float32, count=numberOfAcquiredChannels * FrameLength)
                    data = data / 1  # Assuming you need to scale the data
                    data = np.reshape(data, (FrameLength, numberOfAcquiredChannels))

                    # Write data to file, ensuring proper formatting.
                    np.savetxt(file, data, delimiter=',', fmt='%.3f')

                    # Update console to indicate that the data acquisition is running.
                    if i % consoleUpdateRate == 0:
                        print('.', end='', flush=True)


                df = pd.read_csv('data.csv')
                print(df.head(10))

                print(df.columns)
                df.info()
                dft=df[['E1','E2','E3','E4','E5','E6','E7','E8',]]
                dft
                for col in dft.columns:
                    Q1 = df[col].quantile(0.25)
                    Q3 = df[col].quantile(0.75)
                    IQR = Q3 - Q1


                    low = Q1-1.5*IQR
                    high = Q3+1.5*IQR

                    # incorrects = dft[(dft[col] < low) | (dft[col] > high)].index

                    # dft.loc[incorrects, col] = np.nan

                dft.interpolate(method = 'linear', limit_direction='backward')

                df2=dft[dft.index > 500]

                # Diccionario para almacenar las funciones de regresión.
                funciones_regresion = {}

                # Ahora, para cada conjunto de datos 'Ei', haremos una regresión y graficaremos.
                for i in range(1, 9):
                    canal = f'E{i}'
                    df1 = df2[[canal]].dropna()  # Eliminar NaNs.
                    
                    # Obtener los índices y los valores para la regresión.
                    x_valores = df1.index.to_numpy()
                    y_valores = df1[canal].to_numpy()
                    
                    # Realizar la regresión lineal.
                    pendiente, interseccion, r_valor, p_valor, std_err = stats.linregress(x_valores, y_valores)
                    
                    # Almacenar la función de regresión en el diccionario.
                    funciones_regresion[canal] = {'pendiente': pendiente}
                    
                    # Definir una función de regresión lineal.
                    def estimar_y(x, pendiente, interseccion):
                        return pendiente * x + interseccion
                    
                    # Graficar los puntos originales y la línea de ajuste.
                    # plt.figure(figsize=(5, 3))
                    # plt.scatter(x_valores, y_valores, color='red', label='Datos originales')
                    # plt.plot(x_valores, estimar_y(x_valores, pendiente, interseccion), label='Ajuste lineal', color='blue')
                    # plt.title(f'Regresión para {canal}')
                    # plt.xlabel('Índice')
                    # plt.ylabel(canal)
                    # plt.grid(True)
                    # plt.legend()
                    # plt.show()
                print("Funciones regresion: ", funciones_regresion)
                # Ahora, después de calcular las funciones de regresión para cada canal:
                funcion_detectada = encontrar_funcion_global(funciones_regresion)
                print(f"La función más cercana detectada es: {funcion_detectada}")

                consume_api(funcion_detectada)
                # print("Funciones regresion:", funciones_regresion)

            # Stop data acquisition.
            # -------------------------------------------------------------------------------------
            device.StopAcquisition()
            print("\nData acquisition stopped.")

        # Close device.
        # -------------------------------------------------------------------------------------
        del device
        print("Disconnected from Unicorn")

    except UnicornPy.DeviceException as e:
        print(e)
    except Exception as e:
        print("An unknown error occured. %s" %e)

    input("\n\nPress ENTER key to exit")

def consume_api(message):
    # URL de tu API corregida
    api_url = 'http://10.43.44.106:8080/receive_data'  # Asegúrate de que el puerto y la ruta sean correctos

    # Datos para enviar a la API
    data = {'message': message}

    # Realizar la solicitud a la API
    try:
        response = requests.post(api_url, json=data)

        # Verificar si la solicitud fue exitosa
        if response.status_code == 200:
            print('Mensaje enviado correctamente al servidor Flask')
        else: 
            print('Error al enviar el mensaje al servidor Flask:', response.status_code, response.text)
    except requests.exceptions.RequestException as e:
        print('Error al conectar con el servidor Flask:', str(e))

#execute main
main()

