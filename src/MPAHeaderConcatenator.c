////////////////////////////////////////
// MPA file concatenator by OmDRetro  //
//                                    //
//Code is based on my "NameChangeArgs"//
//  Updated: 8/01/2024                //
////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h> // for access
#include <stdint.h>

#define BUFFER_SIZE 1024
#define MAX_FILES 1024

struct main_h {
    uint32_t size;
};

void main_f(char path[], struct main_h *head, const char *out){
    //
    FILE *i_header = fopen(path, "rb");
	if(!i_header) {
		fclose(i_header);
		printf("\nUnable to find: \n %s \n\n", path);
	} else {
		//
		FILE *o_file = fopen(out, "wb");
        fseek(i_header, 0, SEEK_END);
        head->size = ftell(i_header)+4;
		fwrite(head, 1, sizeof(*head), o_file);
		fclose(i_header);
		fclose(o_file);
	}
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct main_h head;
    FILE *fp_list, *fp_in, *fp_out;
    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    char filename[100];
    char full_path[260];

    dir = opendir(".\\Input\\");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    fp_list = fopen("hdatlist.lst", "w");
    if (fp_list == NULL) {
        perror("fopen");
        closedir(dir);
        return 1;
    }

    /////////////////////////////////////CREATE LIST OF HDAT
    //
    char filenames[MAX_FILES][100];
    int file_count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".hdat") != NULL || strstr(entry->d_name, ".HDAT") != NULL) {
            strcpy(filenames[file_count], entry->d_name);
            file_count++;
        }
    }

    for (int i = 0; i < file_count - 1; i++) {
        for (int j = 0; j < file_count - i - 1; j++) {
            if (strcmp(filenames[j], filenames[j + 1]) > 0) {
                printf("Swapping: %s and %s\n", filenames[j], filenames[j + 1]);
                char temp[100];
                strcpy(temp, filenames[j]);
                strcpy(filenames[j], filenames[j + 1]);
                strcpy(filenames[j + 1], temp);
            }
        }
    }

    for (int i = 0; i < file_count; i++) {
        fprintf(fp_list, "%s\n", filenames[i]);
    }

    closedir(dir);
    fclose(fp_list);

    /////////////////////////////////////END LIST OF HDAT

    // Concatenate files based on the list
    fp_list = fopen("hdatlist.lst", "r");
    if (fp_list == NULL) {
        perror("fopen");
        return 1;
    }

    fp_out = fopen("output1.tmp", "wb");
    if (fp_out == NULL) {
        perror("fopen");
        fclose(fp_list);
        return 1;
    }

    while (fgets(filename, sizeof(filename), fp_list) != NULL) {
        filename[strcspn(filename, "\n")] = '\0';
        sprintf(full_path, ".\\Input\\%s", filename);
        printf("Full path: %s\n", full_path);

        if (access(full_path, F_OK) == 0) {
            fp_in = fopen(full_path, "rb");
            if (fp_in == NULL) {
                perror("fopen");
                fclose(fp_list);
                fclose(fp_out);
                return 1;
            }

            while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, fp_in)) > 0) {
                fwrite(buffer, 1, bytes_read, fp_out);
            }

            fclose(fp_in);
        } else {
            fprintf(stderr, "Error: File %s not found\n", full_path);
        }


    }

    fclose(fp_list);
    fclose(fp_out);

    main_f(".\\output1.tmp", &head, ".\\output0.tmp");


    ///////////////////////
    ////////////////MPA LIST TIME
    // Create the list of .txt files
    dir = opendir(".\\Input\\");

    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    fp_list = fopen("mpalist.lst", "w");
    if (fp_list == NULL) {
        perror("fopen");
        closedir(dir);
        return 1;
    }


    file_count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".mpa") != NULL || strstr(entry->d_name, ".MPA") != NULL) {
            strcpy(filenames[file_count], entry->d_name);
            file_count++;
        }
    }


    for (int i = 0; i < file_count - 1; i++) {
        for (int j = 0; j < file_count - i - 1; j++) {
            if (strcmp(filenames[j], filenames[j + 1]) > 0) {
                printf("Swapping: %s and %s\n", filenames[j], filenames[j + 1]);
                char temp[100];
                strcpy(temp, filenames[j]);
                strcpy(filenames[j], filenames[j + 1]);
                strcpy(filenames[j + 1], temp);
            }
        }
    }


    for (int i = 0; i < file_count; i++) {
        fprintf(fp_list, "%s\n", filenames[i]);
    }

    closedir(dir);
    fclose(fp_list);


    fp_list = fopen("mpalist.lst", "r");
    if (fp_list == NULL) {
        perror("fopen");
        return 1;
    }

    fp_out = fopen("output2.tmp", "wb");
    if (fp_out == NULL) {
        perror("fopen");
        fclose(fp_list);
        return 1;
    }

    while (fgets(filename, sizeof(filename), fp_list) != NULL) {
        filename[strcspn(filename, "\n")] = '\0';
        sprintf(full_path, ".\\Input\\%s", filename);
        printf("Full path: %s\n", full_path);

        if (access(full_path, F_OK) == 0) {
            fp_in = fopen(full_path, "rb");
            if (fp_in == NULL) {
                perror("fopen");
                fclose(fp_list);
                fclose(fp_out);
                return 1;
            }

            while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, fp_in)) > 0) {
                fwrite(buffer, 1, bytes_read, fp_out);
            }

            fclose(fp_in);
        } else {
            fprintf(stderr, "Error: File %s not found\n", full_path);
        }


    }

    fclose(fp_list);
    fclose(fp_out);

    return 0;
}
