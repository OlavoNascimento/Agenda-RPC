#include <stdio.h>

#include "addsub.h"

/* implementa��o da fun��o add */
int *add_1_svc(operands *argp, struct svc_req *rqstp) {
    static int result;

    printf("Recebi chamado: add %d %d\n", argp->x, argp->y);
    result = argp->x + argp->y;
    return (&result);
}

/* implementa��o da fun��o sub */
int *sub_1_svc(operands *argp, struct svc_req *rqstp) {
    static int result;

    printf("Recebi chamado: sub %d %d\n", argp->x, argp->y);
    result = argp->x - argp->y;
    return (&result);
}
