#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "variable.h"
#include "neuron.h"
#include "math_util.h"
#include "layer.h"
#include "bitmap/bitmap.h"
#include "dataset.h"
#include "mlp.h"


//int main() {
//    int count = 100;
//    dataset* moons_dataset = dataset_make_moons(count, 0.1f);
//    variable*** X = moons_dataset->X;
//
//    layer* layer = layer_initialize(2, 16, false);
////    for (int i = 0; i < moons_dataset->count; i++) {
//    variable** inputs = X[0];
//    variable** layer_act = layer_activate(layer, inputs);
//    for (int j = 0; j < 16; j++) {
//        variable_print(layer_act[j]);
//        variable_free(layer_act[j]);
//    }
//    free(layer_act);
////    }
//
//    layer_free(layer);
//    dataset_free(moons_dataset);
//    return 0;
//}

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
    dataset* moons_dataset = dataset_make_moons(count, 0.1f);

    int layer_outputs[3] = {16, 16, 1};
    mlp* mlp = mlp_initialize(2, layer_outputs, 3);
    printf("mlp initialized\n");
    mlp_print(mlp);

    mlp_result* results = mlp_activate(mlp, moons_dataset);
    printf("mlp activated\n");

    dataset* final_result = results->final_result;
    variable*** final_X = final_result->X;
    float* final_values = results->final_values;
    printf("final_output count: %d\n", final_result->count);
    printf("final_output length: %d\n", final_result->input_length);

    variable* minx = dataset_min(final_result, 0);
    variable* miny = dataset_min(final_result, 1);

    printf("min (%f, %f)\n", minx->value, miny->value);

    variable* maxx = dataset_max(final_result, 0);
    variable* maxy = dataset_max(final_result, 1);

    printf("max (%f, %f)\n", maxx->value, maxy->value);

    float x_diff = maxx->value - minx->value;
    float y_diff = maxy->value - miny->value;

    printf("%d\n", maxy->value > miny->value);

    variable** losses = malloc(count * sizeof(variable*));
    for (int i = 0; i < count; i++) {
        variable** data_point = final_result->X[i];
        variable* x = data_point[0];
        variable* y = data_point[1];

        int px = (x->value + 1) * (width / x_diff);
        int py = (y->value + 0.5) * (height / y_diff);

        //px += (width / 2);
        //py += (height / 2);

        point p = {px, py};

        int class = final_result->y[i];
        if (class > 0) {
            bitmap_circle(bitmap, p, 3, red);
        } else {
            bitmap_circle(bitmap, p, 3, blue);
        }

        variable* v_y = variable_initialize_fresh("v_y", -moons_dataset->y[i]);
        variable* score = variable_initialize_fresh("score", results->final_values[i]);
        variable* loss_score = variable_mul("loss_score", score, v_y);
        variable* one = variable_initialize_fresh("one", 1.f);
        variable* loss = variable_add("loss_sum",
                                       one,
                                       loss_score);
        variable_free(v_y);
        variable_free(score);
        variable_free(loss_score);
        variable_free(one);
        losses[i] = loss;
    }

    variable* data_loss = variable_initialize_fresh("data_loss", 0);
    for (int i = 0; i < count; i++) {
        variable* temp_data_loss = data_loss;
        variable* loss = losses[i];
        data_loss = variable_add("data_loss", data_loss, loss);
        if (i < count - 1) {
            variable_free(temp_data_loss);
        }
    }

    printf("data_loss:\n");
    variable_print(data_loss);

    int correct = 0;
    for (int i = 0; i < count; i++) {
        int class = final_result->y[i];
        int true_class = moons_dataset->y[i];
        correct += (class == true_class);
    }
    float accuracy = (float) correct / count;
    printf("accuracy: %f\n", accuracy);

    variable_first_backward(data_loss);
    variable_print(data_loss);

    bitmap_save(bitmap, "test.bmp");
    printf("file generated\n");

    mlp_result_free(results);

    dataset_free(moons_dataset);
    bitmap_free(bitmap);
    mlp_free(mlp);
    return 0;
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
