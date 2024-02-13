#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME_BUFFER 20
#define CHARACTER_BUFFER 128

typedef struct
{
    unsigned day, month, year, hour, minute, second;
} measurement_time_imp;

typedef struct
{
    unsigned day, month, year, hour, minute, second;
} measurement_time_hun;

typedef struct
{
    measurement_time_imp date;
    double temperature_fahrenheit;
} measurement_imp;

typedef struct
{
    measurement_time_hun date;
    double temperature_celsius;
} measurement_hun;

measurement_time_hun date_imp2hun(measurement_time_imp date_imp)
{
    measurement_time_hun date_hun;

    date_hun.year = date_imp.year;
    date_hun.month = date_imp.month;
    date_hun.day = date_imp.day;
    date_hun.hour = date_imp.hour;
    date_hun.minute = date_imp.minute;
    date_hun.second = date_imp.second;

    return date_hun;
}

measurement_hun *measurements_imp2hun(measurement_imp *measurements_imp, size_t size_measurements_imp, size_t *size_measurements_hun)
{
    *size_measurements_hun = size_measurements_imp;

    measurement_hun *measurements_hun = malloc(*size_measurements_hun * sizeof(measurement_imp));

    for (size_t i = 0; i < size_measurements_imp; i++)
    {
        measurements_hun[i].date = date_imp2hun(measurements_imp[i].date);
        measurements_hun[i].temperature_celsius = (measurements_imp[i].temperature_fahrenheit - 32.00) * (5.0 / 9.0);
    }

    return measurements_hun;
}

measurement_imp *read_measurements(FILE *fimp, size_t *size_measurements)
{
    *size_measurements = 0;

    char buffer[CHARACTER_BUFFER] = {0};
    while (fgets(buffer, CHARACTER_BUFFER, fimp) != NULL)
    {
        if (strstr(buffer, "MEASUREMENT_TIME"))
            *size_measurements += 1;
    }
    rewind(fimp);

    measurement_imp *measurements = malloc(*size_measurements * sizeof(measurement_imp));

    size_t i = 0;
    while (i < *size_measurements)
    {
        fgets(buffer, CHARACTER_BUFFER, fimp);

        if (buffer[0] == '\n')
            continue;

        if (sscanf(buffer, "MEASUREMENT_TIME %d/%d/%d %d:%d:%d", &measurements[i].date.day, &measurements[i].date.month, &measurements[i].date.year,
                   &measurements[i].date.hour, &measurements[i].date.minute, &measurements[i].date.second) != 6)
            return NULL;

        fgets(buffer, CHARACTER_BUFFER, fimp);
        if (sscanf(buffer, "TEMPERATURE %lfF", &measurements[i].temperature_fahrenheit) != 1)
            return NULL;

        i++;
    }

    return measurements;
}

void destroy(measurement_imp *measurements_imp, measurement_hun *measurements_hun)
{
    free(measurements_imp);
    free(measurements_hun);

    measurements_imp = NULL;
    measurements_hun = NULL;
}

int main()
{
    char imp_filename[CHARACTER_BUFFER] = {0};
    char hun_filename[CHARACTER_BUFFER] = {0};

    scanf("%s %s", &imp_filename, &hun_filename);

    FILE *f_imp = fopen(imp_filename, "r");
    if (f_imp == NULL)
        return 1;

    FILE *f_hun = fopen(hun_filename, "w");
    if (f_hun == NULL)
        return 1;

    size_t size_measurements_imp;
    size_t size_measurements_hun;

    measurement_imp *measurements_imp = read_measurements(f_imp, &size_measurements_imp);
    if (measurements_imp == NULL)
        return 1;

    measurement_hun *measurements_hun = measurements_imp2hun(measurements_imp, size_measurements_imp, &size_measurements_hun);
    if (measurements_hun == NULL)
        return 1;

    for (size_t i = 0; i < size_measurements_hun; i++)
    {
        fprintf(f_hun, "MERESI_IDO %04d.%02d.%02d %02d.%02d.%02d\n"
                       "HOMERSEKLET %.1fC",
                measurements_hun[i].date.year, measurements_hun[i].date.month, measurements_hun[i].date.day,
                measurements_hun[i].date.hour, measurements_hun[i].date.minute, measurements_hun[i].date.second,
                measurements_hun[i].temperature_celsius);
        fprintf(f_hun, "\n");
    }

    fclose(f_imp);
    fclose(f_hun);

    destroy(measurements_imp, measurements_hun);

    return 0;
}
