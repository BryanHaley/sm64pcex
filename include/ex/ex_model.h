#ifndef EX_MODEL_H
#define EX_MODEL_H

#include "ex/ex_mesh.h"

typedef struct 
{
    int num_meshes;
    ex_mesh_t** meshes;
} ex_model_t;

#endif