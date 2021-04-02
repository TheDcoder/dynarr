#include <stdlib.h>
#include <string.h>
#include "dynarr.h"

void *dynarr_nomen(dynarr *array) {
	if (array->mem_callback) array->mem_callback(array);
	return NULL;
}

dynarr dynarr_init_full(size_t e_size, size_t increment, void (*mem_callback)(dynarr *)) {
	return (dynarr){
		.actual = NULL,
		.size = 0,
		.e_size = e_size,
		.occupied = 0,
		.increment = increment,
		.mem_callback = mem_callback,
	};
}

dynarr dynarr_init(size_t element_size) {
	return dynarr_init_full(element_size, DYNARRAY_H_INCREMENT, NULL);
}

void *dynarr_push(dynarr *array, void *data) {
	if (array->occupied == array->size) {
		// Array is full
		// Increase size
		size_t new_real_size = (array->size + array->increment) * array->e_size;
		void *new_actual = realloc(array->actual, new_real_size);
		if (!new_actual) return dynarr_nomen(array);
		array->actual = new_actual;
		array->size += array->increment;
	}
	
	// Copy data
	char *charr = (char *) array->actual;
	memcpy(charr + array->occupied++ * array->e_size, data, array->e_size);
	
	return array->actual;
}

void *dynarr_get(dynarr *array, size_t *size) {
	if (size) *size = array->occupied;
	return array->actual;
}

void *dynarr_compact(dynarr *array) {
	void *new_actual = realloc(array->actual, array->occupied * array->e_size);
	if (!new_actual) return dynarr_nomen(array);
	array->actual = new_actual;
	array->size = array->occupied;
	return array->actual;
}

void dynarr_free(dynarr *array) {
	free(array->actual);
	array->actual = NULL;
	array->occupied = 0;
}
