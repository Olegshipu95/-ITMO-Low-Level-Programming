#include "bmp/bmp_functions.h"
#include "image/img.h"
#include "image/rotate.h"
#include "messages/messages.h"
#include "operations/connect.h"
#include "statuses/IO_statuses.h"
#include <stdio.h>


int main(int argc, char **argv) {//1ый аргумент - имя выполняемого файла, 2-input file,3-output file
    puts(messages[WELCOME]);
    if (argc != 3) {//кол-во аргументов.
        fprintf(stderr, "%s", messages[NOT_THE_RIGHT_NUMBER_OF_ARGS]);
        return 1;
    }
    const char *const input_file_name = argv[1];
    FILE *input_file = NULL;
    enum open_file_status fileStatus = open_file(&input_file, input_file_name, connect_messages[OPEN]);
    if (fileStatus != OPEN_OK) {
        fprintf(stderr, "%s", messages[PROBLEM_IN_READING]);
        return 1;
    }
    puts("file opened");
    fprintf(stderr, "%s", "file opened\n");

    struct image initial_image = {0};//Получим значения после выполнения следующей функции
    enum read_status read = read_bmp_image(input_file, &initial_image);
    if (read != READ_OK) {
        clear_img_heap(&initial_image);
        fprintf(stderr, "%s", messages[FATAL_ERROR]);
        fprintf(stderr, "%s", "\n");
        return 1;
    }
    puts("success read");
    fprintf(stderr, "%s", "file read.\n");
    int close = fclose(input_file);
    fprintf(stderr, "%d", close);
    if (close != 0) {
        fprintf(stderr, "%s", "Can not close input file.");
        clear_img_heap(&initial_image);
        return 1;
    }
    puts("success close the first file");
    fprintf(stderr, "%s", "file close\n");
    FILE *new_file = NULL;
    const char *const output_file_name = argv[2];
    fileStatus = open_file(&new_file, output_file_name, connect_messages[WRITE]);
    if (fileStatus != OPEN_OK) {
        fprintf(stderr, "%s", messages[PROBLEM_IN_READING]);
    }
    struct image new_image = rotate(&initial_image);
    clear_img_heap(&initial_image);
    enum write_status writeStatus = write_bmp_file(new_file, &new_image);
    if (writeStatus != WRITE_OK) {
        fprintf(stderr, "%s", messages[FATAL_ERROR]);
    }
    clear_img_heap(&new_image);
    if (fclose(new_file) != 0) {
        fprintf(stderr, "Can not close output file.");
        return 1;
    }
    return 0;
}
