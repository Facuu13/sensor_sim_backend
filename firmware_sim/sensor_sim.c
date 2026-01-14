#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

struct sensor
{   
    int device_id;
    // status: 0 = OK, 1 = ERROR
    int status;
    // valor: sensor reading value
    float valor;
    // bateria: battery level percentage
    float bateria;
    // secuencia: reading sequence number
    int secuencia;
    // tipo de sensor: 0 = temperature, 1 = humidity, 2 = pressure
    int tipo_sensor;
};


// Function to simulate sensor reading
int simulate_sensor_reading(struct sensor *sensor) {
    if (sensor == NULL) {
        return -1; // error: null pointer
    }

    // Simulate reading based on sensor type
    switch (sensor->tipo_sensor) {
        case 0: // temperature sensor
            sensor->valor = (rand() % 4000) / 100.0; // simulate temperature between 0.00 to 40.00
            break;
        case 1: // humidity sensor
            sensor->valor = (rand() % 10000) / 100.0; // simulate humidity between 0.00% to 100.00%
            break;
        case 2: // pressure sensor
            sensor->valor = (rand() % 200000) / 100.0; // simulate pressure between 0.00 to 2000.00 hPa
            break;
        default:
            return -2; // error: unknown sensor type
    }

    // Simulate battery drain
    sensor->bateria -= (rand() % 5); // decrease battery by up to 5%
    if (sensor->bateria < 0) {
        sensor->bateria = 0;
        sensor->status = 1; // set status to ERROR if battery is depleted
    } else {
        sensor->status = 0; // set status to OK
    }

    // Increment sequence number
    sensor->secuencia += 1;

    return 0; // success
}

// Function to print sensor status
const char* status_str(int status) {
    switch (status) {
        case 0:
            return "OK";
        case 1:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

// Function to print sensor type
const char* tipo_sensor_str(int tipo_sensor) {
    switch (tipo_sensor) {
        case 0:
            return "Temperature";
        case 1:
            return "Humidity";
        case 2:
            return "Pressure";
        default:
            return "Unknown";
    }
}

void emit_json(const struct sensor* s){
    if (s == NULL) {
        return;
    }
    printf("{\"device_id\": %d, \"status\": \"%s\", \"valor\": %.2f, \"bat\": %.2f, \"seq\": %d, \"tipo_sensor\": \"%s\", \"timestamp\": %ld}\n",
           s->device_id,
           status_str(s->status),
           s->valor,
           s->bateria,
           s->secuencia,
           tipo_sensor_str(s->tipo_sensor),
           time(NULL));
    fflush(stdout);
}

int main() {
    struct sensor temp_sensor;
    temp_sensor.tipo_sensor = 0; // temperature sensor
    struct sensor humidity_sensor;
    humidity_sensor.tipo_sensor = 1; // humidity sensor

    // Initialize sensors
    temp_sensor.device_id = 1;
    temp_sensor.status = 0;
    temp_sensor.valor = 0.0;
    temp_sensor.bateria = 100.0;
    temp_sensor.secuencia = 0;

    humidity_sensor.device_id = 2;
    humidity_sensor.status = 0;
    humidity_sensor.valor = 0.0;
    humidity_sensor.bateria = 100.0;
    humidity_sensor.secuencia = 0;

    // Simulate readings y enviar JSON output cada 2 segundos
    srand(time(NULL)); // seed for random number generation

    for (int i = 0; i < 10; i++) {
        simulate_sensor_reading(&temp_sensor);
        simulate_sensor_reading(&humidity_sensor);
        sleep(2);
        emit_json(&temp_sensor);
        emit_json(&humidity_sensor);

    }
    return 0;
}