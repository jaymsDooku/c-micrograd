#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "variable.h"
#include "neuron.h"
#include "math_util.h"
#include "layer.h"
#include "bitmap/bitmap.h"
#include "dataset.h"



int main() {
    int height = 600;
    int width = 600;
    bitmap* bitmap = bitmap_initialize(width, height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * 3;
            bitmap->image[index + 2] = (unsigned char) (y * 255 / height);
            bitmap->image[index + 1] = (unsigned char) (x * 255 / width);
            bitmap->image[index] = (unsigned char) ((x + y) * 255 / (height + width));
        }
    }

    color red = {255, 87, 51};
    color blue = {51, 219, 255};

    int count = 100;
    //dataset* dataset = dataset_random(count, 2);
    dataset* dataset = dataset_make_moons(count);

    variable* minx = dataset_min(dataset, 0);
    variable* miny = dataset_min(dataset, 1);

    printf("min (%f, %f)\n", minx->value, miny->value);

    variable* maxx = dataset_max(dataset, 0);
    variable* maxy = dataset_max(dataset, 1);

    printf("max (%f, %f)\n", maxx->value, maxy->value);

    float x_diff = maxx->value - minx->value;
    float y_diff = maxy->value - miny->value;

    printf("%d", maxy->value > miny->value);

    for (int i = 0; i < count; i++) {
        variable** data_point = dataset->X[i];
        variable* x = data_point[0];
        variable* y = data_point[1];

        int px = (x->value + 1) * (width / x_diff);
        int py = (y->value + 0.5) * (height / y_diff);

        //px += (width / 2);
        //py += (height / 2);

        point p = {px, py};

        int class = dataset->y[i];
        if (class) {
            bitmap_circle(bitmap, p, 3, red);
        } else {
            bitmap_circle(bitmap, p, 3, blue);
        }
    }

    bitmap_save(bitmap, "test.bmp");
    printf("file generated");

    dataset_free(dataset);
    bitmap_free(bitmap);
}

//int main() {
//    variable* a = variable_initialize_fresh("a", 3);
//    variable* b = variable_initialize_fresh("b", 5);
//
//    variable* f = variable_exp("f", a, b);
//    variable* g = variable_relu("g", f);
//
////    variable* children[2] = {a , b};
////    variable* c = variable_initialize("c", a->value + b->value, children, 2, ADD);
////    variable* c = variable_add("c", a, b);
////    variable* d = variable_mul("d", a, c);
//
//    // y = a + b
//    // dy/da = 1
//    // y = 2a
//    //
//    //variable_first_backward(c);
//    //variable_first_backward(d);
//    //variable_first_backward(f);
//    variable_first_backward(g);
//
//    variable_print(a);
//    variable_print(b);
////    variable_print(c);
////    variable_print(d);
//    variable_print(f);
//    variable_print(g);
//
//    variable_free(a);
//    variable_free(b);
////    variable_free(c);
////    variable_free(d);
//    variable_free(f);
//    variable_free(g);
//
//    variable** inputs = malloc(10 * sizeof(variable*));
//    for (int i = 0; i < 10; i++) {
//        char input_name[10];
//        snprintf(input_name, 10, "%s%d", "input", i);
//        float value = randf(-1, 1);
//        inputs[i] = variable_initialize_fresh(input_name, value);
//        printf("%f, ", value);
//    }
//    printf("\n");
//
//    neuron* n1 = neuron_initialize(10, false);
//    neuron_print(n1);
//
//    variable* act = neuron_activate(n1, inputs);
//    variable_print(act);
//    variable_free(act);
//
//    neuron_free(n1);
//
//    layer* layer = layer_initialize(10, 10, false);
//    variable** layer_act = layer_activate(layer, inputs);
//    for (int i = 0; i < 10; i++) {
//        variable_print(layer_act[i]);
//        variable_free(layer_act[i]);
//    }
//    free(layer_act);
//    layer_free(layer);
//
//    for (int i = 0; i < 10; i++) {
//        variable_free(inputs[i]);
//    }
//    free(inputs);
//
//    return 0;
//}
