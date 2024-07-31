////////////////////////////////////////
// MPAC ROM packing tool by OmDRetro  //
//                                    //
//Code is based on my "NameChangeArgs"//
//  Updated: 8/01/2024                //
////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    FILE *file1, *file2, *file3, *output_file;
    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    // Open input files
    file1 = fopen("output0.tmp", "rb");
    if (file1 == NULL) {
        perror("Error opening 1st dependency");
        fclose(file1);
        return 1;
    }
    file2 = fopen("output1.tmp", "rb");
    if (file2 == NULL) {
        perror("Error opening 2nd dependency");
        fclose(file2);
        return 1;
    }

    file3 = fopen("output2.tmp", "rb");
    if (file3 == NULL) {
        perror("Error opening 3rd dependency");
        fclose(file3);
        return 1;
    }

    // Open output file
    output_file = fopen(".\\Output\\ALBUM.MPAC", "wb");
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(file1);
        fclose(file2);
        fclose(file3);
        return 1;
    }

    // Copy contents of file1 to output file
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file1)) > 0) {
        fwrite(buffer, 1, bytes_read, output_file);
    }

    // Copy contents of file2 to output file
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file2)) > 0) {
        fwrite(buffer, 1, bytes_read, output_file);
    }

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file3)) > 0) {
        fwrite(buffer, 1, bytes_read, output_file);
    }

    // Close files
    fclose(file1);
    fclose(file2);
    fclose(file3);
    fclose(output_file);

    return 0;
}
