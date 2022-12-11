//
// Created by oleg on 25.11.22.
//

#include "rotate.h"
struct image rotate(struct image* const restrict old_image){
    struct image new = allocate_image(old_image->height, old_image->width);
    for (size_t i = 0; i < old_image->height; i++) {
        for (size_t j = 0; j < old_image->width; j++) {
            new.data[old_image->height * j + old_image->height - i - 1] = old_image->data[old_image->width * i + j];
        }
    }
    return new;
}
