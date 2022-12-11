//
// Created by oleg on 25.11.22.
//

#ifndef ASSIGNMENT_3_IMAGE_ROTATION_BMP_FUNCTIONS_H
#define ASSIGNMENT_3_IMAGE_ROTATION_BMP_FUNCTIONS_H

#include "../image/img.h"
#include "../statuses/IO_statuses.h"
#include  <stdint.h>


uint8_t bmp_padding_of(const size_t width);

enum read_status read_bmp_image(FILE *file, struct image *new_image);

enum write_status write_bmp_file(FILE *file, struct image *new_image);

#endif //ASSIGNMENT_3_IMAGE_ROTATION_BMP_FUNCTIONS_H


