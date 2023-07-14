#include <stdio.h>

#include "variable.h"

int main() {
    variable* a = variable_initialize_fresh("a", 3);
    variable* b = variable_initialize_fresh("b", 5);

    variable* f = variable_exp("f", a, b);

//    variable* children[2] = {a , b};
//    variable* c = variable_initialize("c", a->value + b->value, children, 2, ADD);
//    variable* c = variable_add("c", a, b);
//    variable* d = variable_mul("d", a, c);

    // y = a + b
    // dy/da = 1
    // y = 2a
    //
    //variable_first_backward(c);
    //variable_first_backward(d);
    variable_first_backward(f);

    variable_print(a);
    variable_print(b);
//    variable_print(c);
//    variable_print(d);
    variable_print(f);

    variable_free(a);
    variable_free(b);
//    variable_free(c);
//    variable_free(d);
    variable_free(f);
    return 0;
}
