#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// sensor 0-255, messwert 0-1023
int main()
{
    int SensorID, Messwert, WarnLOW, WarnHIGH, AlarmLOW, AlarmHIGH;
    char str[] = "256;1024;70;170;50;204"; // Textdatei Output muss hier sein
    const char delimiters[] = ";";
    char *token = strtok(str, delimiters);
    if (token != NULL)
    {
        SensorID = atoi(token);
        printf("SensorID: %d\n", SensorID);
    }
    if ((SensorID > 255) || (SensorID) < 0)
    {
        printf("SensorID ueberschreitete Parameter! ");
    }
    //else statt if token != null etc. 

    token = strtok(NULL, delimiters);
    if (token != NULL)
    {
        Messwert = atoi(token);
        printf("Messwert: %d\n", Messwert);
        {
            printf("Messwert uerbeschreitete Parameter! ");
        }
    }
    if (Messwert > 1023 || (Messwert) < 0)
        token = strtok(NULL, delimiters);
    if (token != NULL)
    {
        WarnLOW = atoi(token);
        printf("WarnLOW: %d\n", WarnLOW);
    }

    token = strtok(NULL, delimiters);
    if (token != NULL)
    {
        WarnHIGH = atoi(token);
        printf("WarnHIGH: %d\n", WarnHIGH);
    }

    token = strtok(NULL, delimiters);
    if (token != NULL)
    {
        AlarmLOW = atoi(token);
        printf("AlarmLOW: %d\n", AlarmLOW);
    }

    token = strtok(NULL, delimiters);
    if (token != NULL)
    {
        AlarmHIGH = atoi(token);
        printf("AlarmHIGH: %d\n", AlarmHIGH);
    }
    // atoi wird hier verwendet damit wir die char strings zu integers umwandeln
    return 0;
}