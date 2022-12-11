//
// Created by oleg on 25.11.22.
//

#include "bmp.h"
#include "bmp_functions.h"
#include <stddef.h>
#define BfType 19778
#define BfReserved 0
#define BiSize 40
#define BiPlanes 1
#define BiBitCount 24
#define BiCompression 0
#define BiXPelsPerMeter 0
#define BiYPelsPerMeter 0
#define BiClrUsed 0
#define BiClrImportant 0

static inline enum read_status read_pixels(FILE *const restrict input, struct image *const restrict image) {
    for (size_t i = 0; i < image->height; i++) {
        if (fread(image->data + i * image->width, sizeof(struct pixel), image->width, input) != image->width) {
            return READ_ERROR_DATA;
        }
        if (fseek(input, bmp_padding_of(image->width), SEEK_CUR) != 0) {
            return READ_ERROR_DATA;
        }
    }
    return READ_OK;
}

uint8_t bmp_padding_of(const size_t width) {//подсчет padding'a между пикселями.
    uint8_t res = width * sizeof(struct pixel) % 4;
    if (!res)return 0;
    else {
        return 4 - res;//у нас 4 байта. Если занято меньше 4ех, то мусор = 4-res.
    }
}

enum read_status bmp_read_header(FILE *const restrict file, struct bmp_header *header) {
    if (fread(header, sizeof(struct bmp_header), 1, file) != 1) {
        return ERROR_IN_READING_HEADER;
    }
    return READ_OK;
    //читаем из файла 1 элемент sizeof(struct bmp_header).
}

enum read_status read_bmp_image(FILE *const restrict file, struct image *const restrict new_image) {
    struct bmp_header header = {0};
    if (bmp_read_header(file, &header) != READ_OK) {
        return ERROR_IN_READING_HEADER;
    }
    *new_image = allocate_image(header.biWidth, header.biHeight);//выделяем память
    return read_pixels(file, new_image);
}


static struct bmp_header create_new_header(struct image *const restrict image) {
    size_t size_of_image = (sizeof(struct pixel) * image->width + bmp_padding_of(image->width)) * image->height;
    struct bmp_header header = {
            .bfType = BfType,
            .bfileSize = sizeof(struct bmp_header) + size_of_image,
            .bfReserved = BfReserved,
            .bOffBits = sizeof(struct bmp_header),
            .biSize = BiSize,
            .biWidth = image->width,
            .biHeight = image->height,
            .biPlanes = BiPlanes,
            .biBitCount = BiBitCount,
            .biCompression = BiCompression,
            .biSizeImage = size_of_image,
            .biXPelsPerMeter = BiXPelsPerMeter,
            .biYPelsPerMeter = BiYPelsPerMeter,
            .biClrUsed = BiClrUsed,
            .biClrImportant = BiClrImportant
    };
    return header;
}

static enum write_status bmp_write_header(FILE *const restrict file, struct image *const restrict new_image) {
    struct bmp_header new_header = create_new_header(new_image);
    size_t items_num = fwrite(&new_header, sizeof(struct bmp_header), 1, file);
    return items_num == 1 ? WRITE_OK : WRITE_ERROR;
}

static enum write_status write_pixels(FILE *const file, const struct image *const image) {
    for (size_t i = 0; i < image->height; i++) {
        if (fwrite(image->data + i * image->width, sizeof(struct pixel), image->width, file) != image->width)
            return WRITE_ERROR_DATA;
        if (fseek(file, bmp_padding_of(image->width), SEEK_CUR) != 0) return WRITE_ERROR_DATA;
    }
    return WRITE_OK;
}

enum write_status write_bmp_file(FILE *const restrict file, struct image *const restrict new_image) {
    enum write_status status = bmp_write_header(file, new_image);
    if (status != WRITE_OK) return status;
    return write_pixels(file, new_image);
}
