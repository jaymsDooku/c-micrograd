//
// Created by James Leaver on 12/07/2023.
//

#ifndef C_MICROGRAD_VARIABLE_H
#define C_MICROGRAD_VARIABLE_H

#define FOREACH_OP(OP) \
    OP(ADD) \
    OP(MUL) \
    OP(NOP) \
    OP(EXP) \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

typedef enum OP_ENUM {
    FOREACH_OP(GENERATE_ENUM)
} OP_ENUM;

static const char *OP_STRING[] = {
        FOREACH_OP(GENERATE_STRING)
};

struct grad_function;

typedef struct variable {
    char* name;
    float value;
    float grad;

    struct variable* children[2];

    OP_ENUM op;

    struct grad_function* grad_function;
} variable;

void variable_first_backward(variable* variable);
void variable_backward(variable* variable);
variable* variable_mul(char* name, variable* a, variable* b);
variable* variable_add(char* name, variable* a, variable* b);
variable* variable_exp(char* name, variable* a, variable* b);
void variable_print(variable* variable);
variable* variable_initialize_fresh(char* name, float value);
variable* variable_initialize(char* name, float value, variable* a, variable* b, OP_ENUM op);
void variable_free(variable* variable);

#endif //C_MICROGRAD_VARIABLE_H
