//
// Created by oleg on 25.11.22.
//

#ifndef IMAGE_TRANSFORMER_IO_STATUSES_H
#define IMAGE_TRANSFORMER_IO_STATUSES_H

enum open_file_status {
    OPEN_OK = 0,
    OPEN_ERROR
};

enum close_file_status {
    CLOSE_OK = 0,
    CLOSE_ERROR
};

enum read_status {
    READ_OK = 0,
    READ_ERROR,
    ERROR_IN_READING_HEADER,
    READ_ERROR_DATA,
};

enum write_status{
    WRITE_OK = 0,
    WRITE_ERROR,
    ERROR_IN_WRITE_HEADER,
    WRITE_ERROR_DATA,
};

#endif //IMAGE_TRANSFORMER_IO_STATUSES_H
