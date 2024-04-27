#include <stdio.h>
#include <curl/curl.h>

int main(void)
{
    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json"); // Establecer el encabezado Content-Type
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8080/receive_data");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"key\": \"value\"}");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, -1L);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); // Establecer los encabezados personalizados

        /* Forcing HTTP/3 will make the connection fail if the server isn't
           accessible over QUIC + HTTP/3 on the given host and port.
           Consider using CURLOPT_ALTSVC instead! */
        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_3);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* always cleanup */
        curl_slist_free_all(headers); // Liberar la lista de encabezados
        curl_easy_cleanup(curl);
    }
    return 0;
}