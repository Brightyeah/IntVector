#include "IntVector.h"
#include <malloc.h>
#include <string.h>

IntVector *int_vector_new(size_t initial_capacity)
{
    IntVector *ic = malloc(sizeof(IntVector));
    if (ic == 0) {
        return 0;
    }
    ic->Vector = malloc(initial_capacity * sizeof(int));
    if (ic->Vector == 0) {
        free(ic);
        return 0;
    }
    ic->capacity = initial_capacity;
    return ic;
}

IntVector *int_vector_copy(const IntVector *v)
{
    IntVector *vDouble = malloc(sizeof(IntVector));
    if (vDouble == 0) {
        return 0;
    }
    vDouble->Vector = malloc(v->capacity * sizeof(int));
    if (vDouble->Vector == 0) {
        free(vDouble);
        return 0;
    }
    vDouble->size = v->size;
    vDouble->capacity = v->capacity;
    for (int i = 0; i < v->size; i++) {
        vDouble->Vector[i] = v->Vector[i];
    }
    return vDouble;
}

void int_vector_free(IntVector *v)
{
    free(v->Vector);
    free(v);
}

int int_vector_get_item(const IntVector *v, size_t index)
{
    return v->Vector[index-1];
}

void int_vector_set_item(IntVector *v, size_t index, int item)
{
    v->Vector[index-1] = item;
}

size_t int_vector_get_size(const IntVector *v)
{
    return v->size;
}

size_t int_vector_get_capacity(const IntVector *v)
{
    return v->capacity;
}

int int_vector_push_back(IntVector *v, int item)
{
    if (v->size == v->capacity) {
        v->capacity *= 2;
        int *vSave;
        vSave = realloc(v->Vector, v->capacity * sizeof(int));
        if (vSave == 0) {
            return -1;
        }
        v->Vector = vSave;
        v->size++;
        v->Vector[v->size-1] = item;
    } else if (v->size < v->capacity) {
        v->size++;
        v->Vector[v->size-1] = item; 
    }
    return 0;
}

void int_vector_pop_back(IntVector *v)
{
    if (v->size == 0) {
        return;
    } else {
        v->size--;
    }
}

int int_vector_shrink_to_fit(IntVector *v)
{
    int *vSave;
    vSave = realloc(v->Vector, v->size * sizeof(int));
    if (vSave == 0) {
        return -1;
    }
    v->Vector = vSave;
    v->capacity = v->size;
    return 0;
}

int int_vector_resize(IntVector *v, size_t new_size)
{
    if (new_size > v->size) {
        if (new_size > v->capacity) {
            int *vSave;
            vSave = realloc(v->Vector, new_size * sizeof(int));
            if (vSave == 0) {
                return -1;
            }
            v->Vector = vSave;
            v->capacity = new_size;
        }
        for (int i = v->size - 1; i < new_size; i++) {
            v->Vector[i] = 0;
        }
    } else if (new_size < v->size) {
        return int_vector_shrink_to_fit(v);
    }
    return 0;
}

int int_vector_reserve(IntVector *v, size_t new_capacity) //  12
{
    if (new_capacity > v->capacity) {
        v->Vector = realloc(v->Vector, new_capacity * sizeof(int));
        if (v->Vector == 0) {
            return -1;
        }
        v->capacity = new_capacity;
        return 0;
    }
    return 0;
}