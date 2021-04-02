#ifndef DYNARRAY_H
#define DYNARRAY_H

#ifndef DYNARRAY_H_INCREMENT
#define DYNARRAY_H_INCREMENT 50
#endif

typedef struct dynarr dynarr;

struct dynarr {
	void *actual;
	size_t size;
	size_t e_size;
	size_t occupied;
	size_t increment;
	void (*mem_callback)(dynarr *);
};

dynarr dynarr_init_full(size_t e_size, size_t increment, void (*mem_callback)(dynarr *));
dynarr dynarr_init(size_t element_size);
void *dynarr_push(dynarr *array, void *data);
void *dynarr_get(dynarr *array, size_t *size);
void *dynarr_compact(dynarr *array);
void dynarr_free(dynarr *array);

#endif
