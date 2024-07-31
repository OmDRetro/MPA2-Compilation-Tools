////////////////////////////////////////
//  MPA Header Generator by OmDRetro  //
//                                    //
//Code is based on my "NameChangeArgs"//
//  Updated: 8/01/2024                //
////////////////////////////////////////


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#define MAX_PATH 1024

struct mpa2_minih{
    uint32_t f_size;
    char songtitle[41];
    uint8_t term0,term1,term2;
    uint32_t term3;
};

void mpa2_f(char path[], struct mpa2_minih *head, char *out){
    uint8_t pathlen = strlen(path);
    char filetitle[41];
    head->term0 = 0x3B;
    head->term1 = 0x2D;
    head->term2 = 0x2D;

    char *dir_sep = strrchr(path, '\\');

    if (dir_sep == NULL) {
        dir_sep = path;
    } else {
        dir_sep++;
    }

    char *f_end = strrchr(dir_sep, '.');
    if (f_end == NULL || strcasecmp(path + pathlen - 4, ".mpa")) {
        printf("\nERROR: Not a Music Player Advance file\n\n");
        return;
    }

    strncpy(head->songtitle, dir_sep, f_end - dir_sep);
    strncpy(filetitle, dir_sep, f_end - dir_sep);
    head->songtitle[f_end - dir_sep] = '\0';

    strcat(out,filetitle);
    strcat(out,".hdat");


    FILE *input_file = fopen(path, "rb");
    fseek(input_file,1,SEEK_END);
    head->term3 = (ftell(input_file) - 1);

	if(!input_file) {
		fclose(input_file);
		printf("\nUnable to find: \n %s \n\n", path);
	} else {
	    FILE *o_file = fopen(out, "wb");
        head->f_size = 44;
		fwrite(head, 1, sizeof(*head), o_file);
		fclose(input_file);
		fclose(o_file);
	}

}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [-h] input_file\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-h") == 0) {
        printf("\nMPA Header Generator by OmDRetro:\n\nThis program creates the necessary headers for each MPA file.\n\nSimply invoke this executable and pass the MPA file as an argument \n\nUsage: {ThisBinaryFile}.exe [-h] input_file\n\n");
        return 0;
    }

    struct mpa2_minih head;

    char path[MAX_PATH];
    strncpy(path, argv[1], MAX_PATH - 1);
    path[MAX_PATH - 1] = '\0';

    char *last_slash = strrchr(path, '\\');
    if (last_slash != NULL) {
        *last_slash = '\0';
    }

    strcat(path,"\\");

    mpa2_f(argv[1], &head,path);

    return 0;
}
