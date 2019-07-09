#ifndef H_SIGPRO_GENERATE_H
#define H_SIGPRO_GENERATE_H

#include <stdlib.h>

#include "common.h"

typedef struct
{
    int32_t id;
} signal_t;

typedef enum
{
    CONSTANT,
    SINE,
    SAWTOOTH
} signal_type_t;

typedef struct
{
    signal_type_t type;
    double amplitude;
    double timestep;
    double frequency;
    double vshift;
    double hshift;
} signal_attr_t;

typedef struct
{
    double amplitude;
    double timestamp;
} signal_data_t;

typedef void (*sig_gen_cb)(signal_t *signal, signal_data_t data);

err_t signal_generate(signal_t *sighandle, signal_attr_t sigattr, sig_gen_cb callback);

#endif
