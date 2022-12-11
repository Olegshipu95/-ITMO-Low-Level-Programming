//
// Created by oleg on 25.11.22.
//

#ifndef IMAGE_TRANSFORMER_CONNECT_H
#define IMAGE_TRANSFORMER_CONNECT_H

#include "../image/img.h"
#include "../statuses/IO_statuses.h"

enum modes {
    READ,
    WRITE,
    OPEN
};

enum read_status read_file(FILE **file, const char *file_name);

enum open_file_status open_file(FILE **file, const char *file_name, const char *mode);

enum close_file_status close_file(FILE *file);

extern const char *const connect_messages[];
#endif //IMAGE_TRANSFORMER_CONNECT_H
