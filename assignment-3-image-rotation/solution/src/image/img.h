//
// Created by oleg on 25.11.22.
//

#ifndef IMAGE_TRANSFORMER_IMG_H
#define IMAGE_TRANSFORMER_IMG_H

#include <malloc.h>
#include <stdint.h>


struct __attribute__((packed)) pixel {
    uint8_t b, g, r;
};


struct image {
    size_t width, height;
    struct pixel *data;
};


struct image allocate_image(const size_t width,const size_t height);//выделение памяти

void clear_img_heap(struct image *image);

#endif //IMAGE_TRANSFORMER_IMG_H
