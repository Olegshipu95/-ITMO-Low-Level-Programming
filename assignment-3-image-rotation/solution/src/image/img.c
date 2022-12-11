//
// Created by oleg on 25.11.22.
//

#include "img.h"


struct image allocate_image(const size_t width,const size_t height) {
    struct pixel *all_pixels = malloc(sizeof(struct pixel) * height * width);
    return (struct image) {.width = width, .height=height, .data=all_pixels};
}

void clear_img_heap(struct image * restrict image) {
    free(image->data);
}
