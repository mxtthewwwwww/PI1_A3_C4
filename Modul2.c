#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LINE_LENGTH 396

//Eine Struktur namens "SensorDaten" wird definiert, um die Sensor Daten zu speichern.
typedef struct {
    int sensorID;
    int messwert;
    int warnungLow;
    int warnungHigh;
    int alarmLow;
    int alarmHigh;
} SensorDaten;

//Die Funktion "SensorDatenUntersuchen" wird definiert, um die Sensor Daten zu untersuchen.
void SensorDatenUntersuchen(FILE *file) {
SensorDaten *SensorDatenArray = NULL; //Array zur Speicherung der Sensor Daten.
    int anzahlDerSensoren = 0; // Anzahl der Sensore definieren.

// Zähler für die 4 Bedingungen.
    int zähleWarnungHigh =0;
    int zähleAlarmHigh =0;
    int zähleWarnungLow =0;
    int zähleAlarmLow =0;

// Eine Zeile, um die Daten aus der Datei zu lesen. 
char line[MAX_LINE_LENGTH];

//Einlesen aus der Datei (fgets liest eine Zeile aus der Datei und speichert diese in der Variable "line").
while (fgets(line, sizeof(line), file) != NULL){


//Tokenisierung der Zeile mit Semikolon als Trennzeichen (mit der Funktion "strtok").
char *token = strtok(line, ";"); 

// Extrahieren der Werte und Zuweisen der Werte in die erzeugten SensorDaten-Objekte.
    SensorDaten sensorDaten;
    sensorDaten.sensorID = atoi(token);
    token = strtok(NULL, ";");
    sensorDaten.messwert = atoi(token);
    token = strtok(NULL, ";");
    sensorDaten.warnungLow = atoi(token);
    token = strtok(NULL, ";");
    sensorDaten.warnungHigh = atoi(token);
    token = strtok(NULL, ";");
    sensorDaten.alarmLow = atoi(token);
    token = strtok(NULL, ";");
    sensorDaten.alarmHigh = atoi(token);
    token = strtok(NULL, ";");

//Inkrementierung der Anzahl der Sensoren.
    anzahlDerSensoren++;

//Dynamische Vergrößerung des SensorDatenArrays mit realloc.
    SensorDatenArray =realloc(SensorDatenArray, anzahlDerSensoren * sizeof(SensorDaten));

//Sensor Daten im Array speichern.
    SensorDatenArray[anzahlDerSensoren -1]  = sensorDaten;


// eine Debugging-Ausgabe, um sicherzustellen, dass die eingelesenen Daten korrekt sind.
printf("SensorID: %d, Messwert: %d, WarnungLow: %d, WarnungHigh: %d, AlarmLow: %d, AlarmHigh: %d\n",
       sensorDaten.sensorID, sensorDaten.messwert, sensorDaten.warnungLow,
       sensorDaten.warnungHigh, sensorDaten.alarmLow, sensorDaten.alarmHigh);


// Überprüfung der Bedingungen und Inkrementierung entsprechender Zähler.
if (sensorDaten.messwert >= sensorDaten.warnungHigh && sensorDaten.messwert <= sensorDaten.alarmHigh) {
    zähleWarnungHigh ++;
    printf("Bedingung 1 erfüllt\n"); //Debugging-Ausgabe innerhalb der Bedingung um zu überprüfen ob diese Bedingungen auch erfüllt werden.
   
    } else if (sensorDaten.messwert >= sensorDaten.alarmHigh) {
        zähleAlarmHigh ++;
        printf("Bedingung 2 erfüllt\n");

    } else if (sensorDaten.messwert <= sensorDaten.warnungLow && sensorDaten.messwert >= sensorDaten.alarmLow) {
        zähleWarnungLow ++;
        printf("Bedingung 3 erfüllt\n");

    } else if (sensorDaten.messwert <= sensorDaten.alarmLow) {
        zähleAlarmLow ++;
        printf("Bedingung 4 erfüllt\n");
    }

}

// Ausgabe der Ergebnisse.
printf("Die Anzahl Messungen größer gleich als WarnungHigh und kleiner gleich als AlarmHigh, beträgt: %d\n", zähleWarnungHigh);
printf("Die Anzahl Messungen größer gleich als AlarmHigh, beträgt: %d\n", zähleAlarmHigh);
printf("Die Anzahl Messungen kleiner gleich als WarnungLow und größer gleich als AlarmLow, beträgt: %d\n", zähleWarnungLow);
printf("Die Anzahl Messungen kleiner gleich als AlarmLow, beträgt: %d\n", zähleAlarmLow);


// (dynamisch allokierte) Speicher freigeben.
free(SensorDatenArray);
}

//Hauptfunktion main
int main()
{
    //Lesezugriff durchs Öffnen der Datei.
    FILE *file = fopen("processData.txt", "r");
    if (file == NULL)
        {
        printf("Fehler beim Öffnen der Datei");
        return 1;
        }

// Funktion wird ausgerufen um die Sensor Daten zu analysieren.
SensorDatenUntersuchen(file);

//Schließen der Datei.
fclose(file);

return 0;

}
