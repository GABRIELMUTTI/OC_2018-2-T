#include "../include/instance.h"
#include "../include/solution.h"
#include "../include/instance_loader.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
    Instance* instance = malloc(sizeof(Instance));
    loadInstance(&instance, "/home/gabriel/Documents/ufrgs/courses/oc/trab/instances/cmb01");
    
    return 0;
}
