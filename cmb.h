
// Defines a problem instance.
typedef struct instance_s
{
    unsigned int k;
    unsigned int numVertices;
    unsigned int* graph;
    unsigned int* weights;
    
} Instance;

// Defines a solution to a instance;
typedef struct solution_s
{
    unsigned int* coloration;
    
} Solution;

Instance* newInstance(unsigned int k, unsigned int numVertices, unsigned int* graph, unsigned int* weights);
void destroyInstance(Instance* instance);
int checkFactibility(Instance* instance, Solution* solution);
