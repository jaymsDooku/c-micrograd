//
// Created by james on 17/07/2023.
//

#ifndef C_MICROGRAD_BITMAP_H
#define C_MICROGRAD_BITMAP_H

typedef struct {
    unsigned char** image[3];
    int width;
    int height;
} bitmap;

void bitmap_save(bitmap* bitmap, char* file_name);
bitmap* bitmap_initialize(unsigned char** image[3], int width, int height, char* name);
void bitmap_free(bitmap* bitmap);

#endif //C_MICROGRAD_BITMAP_H
