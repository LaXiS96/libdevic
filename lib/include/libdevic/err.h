#pragma once

typedef int32_t devic_err_t;

#define DEVIC_OK 0

#define DEVIC_ERR_INVALID_ARG -1
#define DEVIC_ERR_INVALID_STATE -2
#define DEVIC_ERR_NOT_SUPPORTED -3
#define DEVIC_ERR_TIMEOUT -4
#define DEVIC_ERR_BUSY -5
#define DEVIC_ERR_NO_MEMORY -6
#define DEVIC_ERR_IO -7
#define DEVIC_ERR_NOT_FOUND -8
#define DEVIC_ERR_PERMISSION -9

/** Returns the error if not OK */
#define devic_err_return(v)    \
    {                          \
        devic_err_t err = (v); \
        if (err != DEVIC_OK)   \
            return err;        \
    }

#define devic_err_goto(v, label) \
    {                            \
        err = (v);               \
        if (err != DEVIC_OK)     \
            goto label;          \
    }
