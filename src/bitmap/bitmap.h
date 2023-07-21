//
// Created by james on 17/07/2023.
//

#ifndef C_MICROGRAD_BITMAP_H
#define C_MICROGRAD_BITMAP_H

typedef struct {
    int x;
    int y;
} point;

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} color;

typedef struct {
    unsigned char* image;
    int image_size;
    int width;
    int height;
} bitmap;

void bitmap_rectangle(bitmap* bitmap, point p1, point p2, color color);
void bitmap_circle(bitmap* bitmap, point p, int radius, color color);

unsigned char* bitmap_file_header(bitmap* bitmap, int stride);
unsigned char* bitmap_info_header(bitmap* bitmap);
void bitmap_save(bitmap* bitmap, char* file_name);
bitmap* bitmap_initialize(int width, int height);
void bitmap_free(bitmap* bitmap);

#endif //C_MICROGRAD_BITMAP_H
