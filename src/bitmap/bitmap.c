//
// Created by James Leaver on 21/07/2023.
//

#include "bitmap.h"

#include <stdio.h>
#include <stdlib.h>

void circle_midpoint_algorithm(bitmap* bitmap, point p, int radius, color color) {
    int x = radius, y = 0;

    bitmap_set(bitmap, p, color);

    if (radius > 0) {
        point p1 = {p.x + x, p.y - y};
        point p2 = {p.x + y, p.y + x};
        point p3 = {p.x - y, p.y + x};
        bitmap_set(bitmap, p1, color);
        bitmap_set(bitmap, p2, color);
        bitmap_set(bitmap, p3, color);
    }

    int P = 1 - radius;
    while (x > y) {
        y++;

        if (P <= 0) {
            P = P + 2*y + 1;
        } else {
            x--;
            P = P + 2*y - 2*x + 1;
        }

        if (x < y) {
            break;
        }

        point p1 = {p.x + x, p.y + y};
        point p2 = {p.x - x, p.y + y};
        point p3 = {p.x + x, p.y - y};
        point p4 = {p.x - x, p.y - y};
        bitmap_set(bitmap, p1, color);
        bitmap_set(bitmap, p2, color);
        bitmap_set(bitmap, p3, color);
        bitmap_set(bitmap, p4, color);

        if (x != y) {
            point p5 = {p.x + y, p.y + x};
            point p6 = {p.x - y, p.y + x};
            point p7 = {p.x + y, p.y - x};
            point p8 = {p.x - y, p.y - x};
            bitmap_set(bitmap, p5, color);
            bitmap_set(bitmap, p6, color);
            bitmap_set(bitmap, p7, color);
            bitmap_set(bitmap, p8, color);
        }
    }
}

void circle_brute_force_algorithm(bitmap* bitmap, point p, int radius, color color) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x*x + y*y <= radius*radius) {
                point p1 = {p.x + x, p.y + y};
                bitmap_set(bitmap, p1, color);
            }
        }
    }
}

void bitmap_rectangle(bitmap* bitmap, point p1, point p2, color color) {

}

void bitmap_circle(bitmap* bitmap, point p, int radius, color color) {
    //circle_midpoint_algorithm(bitmap, p, radius, color);
    circle_brute_force_algorithm(bitmap, p, radius, color);
}

void bitmap_set(bitmap* bitmap, point p, color color) {
    int x = p.x;
    int y = p.y;
    int width = bitmap->width;
    int height = bitmap->height;
    int index = (y * width + x) * 3;
    if (index < 0 || index > (bitmap->image_size - 3)) {
        return;
    }
    bitmap->image[index + 2] = (unsigned char) color.r;
    bitmap->image[index + 1] = (unsigned char) color.g;
    bitmap->image[index] = (unsigned char) color.b;
}

const int BYTES_PER_PIXEL = 3; /// red, green, & blue
const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;

unsigned char* bitmap_file_header(bitmap* bitmap, int stride) {
    int height = bitmap->height;
    int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);

    static unsigned char fileHeader[] = {
            0,0,     /// signature
            0,0,0,0, /// image file size in bytes
            0,0,0,0, /// reserved
            0,0,0,0, /// start of pixel array
    };

    fileHeader[ 0] = (unsigned char)('B');
    fileHeader[ 1] = (unsigned char)('M');
    fileHeader[ 2] = (unsigned char)(fileSize      );
    fileHeader[ 3] = (unsigned char)(fileSize >>  8);
    fileHeader[ 4] = (unsigned char)(fileSize >> 16);
    fileHeader[ 5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

    return fileHeader;
}

unsigned char* bitmap_info_header(bitmap* bitmap) {
    int width = bitmap->width;
    int height = bitmap->height;
    static unsigned char infoHeader[] = {
            0,0,0,0, /// header size
            0,0,0,0, /// image width
            0,0,0,0, /// image height
            0,0,     /// number of color planes
            0,0,     /// bits per pixel
            0,0,0,0, /// compression
            0,0,0,0, /// image size
            0,0,0,0, /// horizontal resolution
            0,0,0,0, /// vertical resolution
            0,0,0,0, /// colors in color table
            0,0,0,0, /// important color count
    };

    infoHeader[ 0] = (unsigned char)(INFO_HEADER_SIZE);
    infoHeader[ 4] = (unsigned char)(width      );
    infoHeader[ 5] = (unsigned char)(width >>  8);
    infoHeader[ 6] = (unsigned char)(width >> 16);
    infoHeader[ 7] = (unsigned char)(width >> 24);
    infoHeader[ 8] = (unsigned char)(height      );
    infoHeader[ 9] = (unsigned char)(height >>  8);
    infoHeader[10] = (unsigned char)(height >> 16);
    infoHeader[11] = (unsigned char)(height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL*8);

    return infoHeader;
}

void bitmap_save(bitmap* bitmap, char* file_name) {
    int width = bitmap->width;
    int widthInBytes = width * BYTES_PER_PIXEL;

    unsigned char padding[3] = {0, 0, 0};
    int paddingSize = (4 - (widthInBytes) % 4) % 4;

    int stride = (widthInBytes) + paddingSize;

    FILE* imageFile = fopen(file_name, "wb");

    unsigned char* fileHeader = bitmap_file_header(bitmap, stride);
    fwrite(fileHeader, 1, FILE_HEADER_SIZE, imageFile);

    unsigned char* infoHeader = bitmap_info_header(bitmap);
    fwrite(infoHeader, 1, INFO_HEADER_SIZE, imageFile);

    int i;
    for (i = 0; i < bitmap->height; i++) {
        fwrite(bitmap->image + (i*widthInBytes), BYTES_PER_PIXEL, width, imageFile);
        fwrite(padding, 1, paddingSize, imageFile);
    }

    fclose(imageFile);
}

bitmap* bitmap_initialize(int width, int height) {
    bitmap* result = malloc(sizeof(bitmap));
    result->image_size = height * width * 3;
    result->image = malloc(sizeof(unsigned char) * result->image_size);
    for (int i = 0; i < result->image_size; i++) {
        result->image[i] = 0;
    }
    result->width = width;
    result->height = height;
    return result;
}

void bitmap_free(bitmap* bitmap) {
    free(bitmap);
}

