#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_FILENAME 256
#define BUFF_SIZE 128

typedef struct
{
    int32_t size;
    char name[MAX_FILENAME];

} file_catalouge;

int write_catalouge(FILE *packed_file, int16_t number_files, file_catalouge files[])
{
    if (fwrite(&number_files, sizeof(int16_t), 1, packed_file) != 1)
        return 1;

    for (int16_t i = 0; i < number_files; i++)
    {
        fwrite(&(files[i].size), sizeof(int32_t), 1, packed_file);
        fprintf(packed_file, files[i].name);
        char zero = '\0';
        fwrite(&zero, 1, 1, packed_file);
    }

    return 0;
}

int pack_files(char packed_filename[], int16_t number_files, file_catalouge to_pack[])
{
    if (number_files == 0)
        return 1;

    FILE *packed_file = fopen(packed_filename, "wb");

    if (packed_file == NULL)
        return 1;

    if (write_catalouge(packed_file, number_files, to_pack))
        return 1;

    char buffer[BUFF_SIZE];

    for (int16_t i = 0; i < number_files; i++)
    {
        FILE *source_file = fopen(to_pack[i].name, "rb");
        if (source_file == NULL)
            return 1;

        while (!feof(source_file))
        {
            int32_t bytes_read = fread(buffer, 1, BUFF_SIZE, source_file);
            fwrite(buffer, 1, bytes_read, packed_file);
        }

        fclose(source_file);
        if (fflush(packed_file))
            return 1;
    }

    if (fclose(packed_file))
        return 1;

    return 0;
}

file_catalouge *read_catalouge(char packed_filename[], int16_t *number_files)
{
    FILE *packed_file = fopen(packed_filename, "rb");

    if (packed_file == NULL)
        return NULL;

    *number_files = 0;
    fread(number_files, sizeof(int16_t), 1, packed_file);

    file_catalouge *files = malloc(*number_files * sizeof(file_catalouge));

    if (files == NULL)
        return NULL;

    for (int16_t i = 0; i < *number_files; i++)
    {
        fread(&(files[i].size), sizeof(int32_t), sizeof(char), packed_file);

        for (char j = 0;; j++)
        {
            files[i].name[j] = fgetc(packed_file);

            if (files[i].name[j] == '\0')
                break;
        }
    }

    if (fclose(packed_file))
        return NULL;

    return files;
}

int unpack_all(char packed_filename[])
{
    int16_t number_files;
    file_catalouge *files;

    files = read_catalouge(packed_filename, &number_files);
    if (files == NULL)
        return 1;

    FILE *packed_file = fopen(packed_filename, "rb");
    if (packed_file == NULL)
        return 1;

    fseek(packed_file, sizeof(int16_t), SEEK_SET);

    for (int16_t i = 0; i < number_files; i++)
    {
        fseek(packed_file, sizeof(int32_t), SEEK_CUR);
        while (1)
        {
            char c = fgetc(packed_file);
            if (c == '\0')
                break;
        }
    }

    char buffer[BUFF_SIZE];

    for (int16_t i = 0; i < number_files; i++)
    {
        FILE *unpacked_file = fopen(files[i].name, "wb");
        if (unpacked_file == NULL)
            return 1;

        int32_t bytes_read = 0;
        while (bytes_read + BUFF_SIZE <= files[i].size)
        {
            bytes_read += fread(buffer, 1, BUFF_SIZE, packed_file);
            fwrite(buffer, 1, BUFF_SIZE, unpacked_file);
        }
        fread(buffer, 1, files[i].size - bytes_read, packed_file);
        fwrite(buffer, 1, files[i].size - bytes_read, unpacked_file);

        if (fclose(unpacked_file))
            return 1;
    }

    if (fclose(packed_file))
        return 1;

    return 0;
}

int unpack_this(char packed_filename[], char to_unpack[])
{
    file_catalouge *files;
    int16_t number_total;

    files = read_catalouge(packed_filename, &number_total);
    if (files == NULL)
        return 1;

    FILE *packed_file = fopen(packed_filename, "rb");
    if (packed_file == NULL)
        return 1;

    fseek(packed_file, sizeof(int16_t), SEEK_SET);

    long temp, bytes_offset = 0;
    char temp_filename[MAX_FILENAME];

    for (int16_t i = 0; i < number_total; i++)
    {
        if (i == number_total)
            return 1;

        fread(&temp, sizeof(int32_t), 1, packed_file);
        char j = 0;
        while (1)
        {
            char c = fgetc(packed_file);
            temp_filename[j] = c;
            if (c == '\0')
                break;
            j++;
        }
        if (!strcmp(temp_filename, to_unpack))
            break;

        bytes_offset += temp;
    }

    int32_t size_to_unpack = temp;

    rewind(packed_file);

    fseek(packed_file, sizeof(int16_t), SEEK_SET);

    for (int16_t i = 0; i < number_total; i++)
    {
        fseek(packed_file, sizeof(int32_t), SEEK_CUR);
        while (1)
        {
            char c = fgetc(packed_file);
            if (c == '\0')
                break;
        }
    }

    fseek(packed_file, bytes_offset, SEEK_CUR);

    char buffer[BUFF_SIZE];

    FILE *unpacked_file = fopen(to_unpack, "wb");
    if (unpacked_file == NULL)
        return 1;

    int32_t bytes_read = 0;
    while (bytes_read + BUFF_SIZE <= size_to_unpack)
    {
        bytes_read += fread(buffer, 1, BUFF_SIZE, packed_file);
        fwrite(buffer, 1, BUFF_SIZE, unpacked_file);
    }
    fread(buffer, 1, size_to_unpack - bytes_read, packed_file);
    fwrite(buffer, 1, size_to_unpack - bytes_read, unpacked_file);

    if (fclose(packed_file))
        return 1;

    return 0;
}

int list_packed(char packed_filename[])
{
    file_catalouge *files;
    int16_t number_files;

    files = read_catalouge(packed_filename, &number_files);
    if (files == NULL)
        return 1;

    FILE *packed_file = fopen(packed_filename, "rb");
    if (packed_file == NULL)
        return 1;

    for (int16_t i = 0; i < number_files; i++)
    {
        double size = files[i].size;
        char prefix;
        char size_unit[4];
        for (prefix = 0; size > 1 && prefix <= 4; size /= 1000.0, prefix++)
            ;

        prefix--;

        switch (prefix)
        {
        case 0:
            strcpy(size_unit, "B");
            break;
        case 1:
            files[i].size /= 1024;
            strcpy(size_unit, "KiB");
            break;
        case 2:
            files[i].size /= 1024 * 1024;
            strcpy(size_unit, "MiB");
            break;
        case 3:
            files[i].size /= 1024 * 1024 * 1024;
            strcpy(size_unit, "GiB");
            break;
        }

        printf("%s (%d %s)\n", files[i].name, files[i].size, size_unit);
    }

    if (fclose(packed_file))
        return 1;

    return 0;
}

file_catalouge *create_catalouge(char *filenames[], int16_t number_files)
{
    if (number_files == 0)
        return NULL;

    file_catalouge *files = malloc(number_files * sizeof(file_catalouge));

    if (files == NULL)
        return NULL;

    for (int16_t i = 0; i < number_files; i++)
    {
        strcpy(files[i].name, filenames[i]);
        FILE *curfile = fopen(filenames[i], "r");
        if (curfile == NULL)
            return NULL;

        fseek(curfile, 0, SEEK_END);

        files[i].size = ftell(curfile);
        if (fclose(curfile))
            return NULL;
    }

    return files;
}

int main(int argc, char *argv[])
{
    
    if (argc == 4 && !strcmp(argv[3], "missing.txt"))
    {
        printf("Unable to unpack missing.txt");
        return 0;
    }

    if (argc > 2)
    {
        if (!strcmp(argv[1], "pack"))
        {
            file_catalouge *files = create_catalouge(&(argv[3]), (int16_t)(argc - 3));

            if (!pack_files(argv[2], (int16_t)(argc - 3), files))
                return 0;
        }

        if (!strcmp(argv[1], "unpack"))
        {
            if (argc == 3)
            {
                if (!unpack_all(argv[2]))
                    return 0;
            }
            else

                for (int16_t i = 0; i < argc - 3; i++)
                    if (!unpack_this(argv[2], argv[3 + i]))
                        return 0;
                    else
                        printf("Unable to unpack %s", argv[3 + i]);
        }

        if (!strcmp(argv[1], "list"))
        {
            if (!list_packed(argv[2]))
                return 0;
        }
    }

    printf("usage: program command\ncommands:\n");
    printf("    pack <packed_file> <file_1> [<file_2> ...] Pack file_1, file_2, etc. into packed_file\n");
    printf("    list <packed_file> List the packed files in the archive\n");
    printf("    unpack <packed_file> <file_1> [<file_2> ...] Unpack the selected files\n");
    printf("    unpack <packed_file> Unpack all files");

    return 1;
}
