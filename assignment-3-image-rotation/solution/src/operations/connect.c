//
// Created by oleg on 25.11.22.
//

#include "connect.h"


const char *const connect_messages[] = {
        [WRITE]="wb",
        [OPEN]="rb"
};

enum open_file_status open_file(FILE **const restrict file, const char *const restrict file_name, const char * const restrict mode) {
    *file = fopen(file_name, mode);
    if (*file) return OPEN_OK;//return 1 if success
    else return OPEN_ERROR;
}

enum close_file_status close_file(FILE *const restrict file) {
    if (fclose(file)) {//returns 0 if closed
        return CLOSE_ERROR;
    }
    return CLOSE_OK;
}
