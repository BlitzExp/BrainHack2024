#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <json/json.h> // Asegúrate de tener la biblioteca jsoncpp instalada

// Función callback para escribir los datos recibidos en un string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* buffer) {
    size_t totalSize = size * nmemb;
    buffer->append((char*)contents, totalSize);
    return totalSize;
}

int main(void) {
    CURL* curl;
    CURLcode res;

    // Inicializar CURL
    curl_global_init(CURL_GLOBAL_ALL);

    // Crear un bucle infinito para esperar mensajes del servidor
    while (true) {
        // Inicializar CURL
        curl = curl_easy_init();
        if (!curl) {
            std::cerr << "Error: No se pudo inicializar CURL." << std::endl;
            return 1;
        }

        // Configurar la URL del servidor Flask
        std::string url = "http://127.0.0.1:8080/send_message";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Configurar el método GET
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);

        // Variable para almacenar la respuesta del servidor
        std::string response_data;

        // Configurar la función de callback para escribir los datos en 'response_data'
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        // Realizar la solicitud
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // Decodificar el JSON
            Json::Value root;
            Json::CharReaderBuilder builder;
            std::istringstream iss(response_data);
            std::string errs;
            if (!Json::parseFromStream(builder, iss, &root, &errs)) {
                std::cerr << "Error al parsear JSON: " << errs << std::endl;
            } else {
                // Verificar si existe el campo 'message' en el JSON
                if (root.isMember("message")) {
                    std::string message = root["message"].asString();
                    std::cout << "Mensaje recibido del servidor: " << message << std::endl;
                } else {
                    std::cerr << "El JSON recibido no contiene el campo 'message'." << std::endl;
                }
            }
        }

        // Limpiar CURL para la próxima iteración
        curl_easy_cleanup(curl);

        // Esperar un tiempo antes de realizar la próxima solicitud
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    // No se llegará aquí, pero se limpia CURL globalmente
    curl_global_cleanup();

    return 0;
}