#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Struct definieren für die Sensoren-Strings
struct SensorData {
    int Sensor;
    int Messwert;
    int WarnLOW;
    int WarnHIGH;
    int AlarmLOW;
    int AlarmHIGH;
};

int main() {
    const char delimiters[] = ";";
    char line[10000]; // 9999 max. Charaktere

    // Öffne die Datei
    FILE *file = fopen("processData.txt", "r"); // "r" ist hier Read
    if (file == NULL) {
        perror("Datei konnte nicht gefunden werden");
        return 1;
    }

    // Array definieren
    struct SensorData sensors[4] = {0}; // 4 Sensoren. Falls man die Sensorenzahl ändern wollen würde, müsste man hier anfangen
    
    // Lese die Textdatei
    while (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, delimiters);
        int currentSensor = -1; // auf -1 eingestellt sodass kein sensor gescannt wird

        
        while (token != NULL) {
            if (currentSensor == -1) { // dann beginne mit dem ersten Token, SensorID...
                int sensorID = atoi(token);
                if (sensorID >= 0 && sensorID <= 255) {
                    currentSensor = sensorID - 1; //..hier
                    sensors[currentSensor].Sensor = sensorID;
                } else {
                    printf("Sensor-Parameter ueberschritten: %d ", sensorID);
                    break; 
                }
            } else {
                // nachdem currentSensor umgestellt wird, beginne mit den Messwerten des Sensors (sensor[currentSensor])
                int messwert = atoi(token);
                
                
                if (messwert >= 0 && messwert <= 1023) {
                    sensors[currentSensor].Messwert = messwert;
                    sensors[currentSensor].WarnLOW = atoi(strtok(NULL, delimiters));
                    sensors[currentSensor].WarnHIGH = atoi(strtok(NULL, delimiters));
                    sensors[currentSensor].AlarmLOW = atoi(strtok(NULL, delimiters));
                    sensors[currentSensor].AlarmHIGH = atoi(strtok(NULL, delimiters));
                } else {
                    printf("Sensor %d : Messwert-Parameter ueberschritten (%d\n)", currentSensor + 1, messwert);
                    break;
                }
            }
            token = strtok(NULL, delimiters);
        }
    }

    // Datei schließen
    fclose(file);

    // Prints, im for loop
    for (int i = 0; i < 4; ++i) {
        printf("Sensor %d: SensorID=%d, Latest Messwert=%d, WarnLOW=%d, WarnHIGH=%d, AlarmLOW=%d, AlarmHIGH=%d\n",
               i + 1,
               sensors[i].Sensor,
               sensors[i].Messwert,
               sensors[i].WarnLOW,
               sensors[i].WarnHIGH,
               sensors[i].AlarmLOW,
               sensors[i].AlarmHIGH);
    }

    return 0;
}
