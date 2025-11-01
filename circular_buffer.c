/*******************************************************************************
circular buffer implementation
*******************************************************************************/
#include <stdlib.h>	 /*	malloc, free	*/
#include <unistd.h>	 /* ssize_t, size_t */
#include <stddef.h>	 /*	offsetof		*/
#include <string.h>	 /* memcpy			*/
#include <assert.h>  /*	assert			*/
#include "cbuffer.h"

#define FAILURE			-1
#define WRITE_I(b)	((b->read_i + b->size) % b->capacity)
#define MIN(a, b)		((a < b) ? a : b) 

struct cbuffer
{
	size_t capacity;
	size_t read_i; /* read_i */
	size_t size;  	 /* write_i = read_i + size */
	char arr[1];
};


/*******************************************************************************
desc: 		creates an empty circular buffer with capacity in bytes.
ret val: 	pointer to cbuffer 	| on success
		 	NULL 				| on failure
*******************************************************************************/
cbuffer_t *cbuffer_create(size_t capacity)
{
	cbuffer_t *cbuf = (cbuffer_t *)malloc(offsetof(cbuffer_t, arr) + capacity);
	if(!cbuf)
	{
		return NULL;
	}
	
	cbuf->capacity = capacity;
	cbuf->read_i = 0;
	cbuf->size = 0;
	
	return cbuf;
}

/*******************************************************************************
desc: deletes cbuffer
*******************************************************************************/
void cbuffer_destroy(cbuffer_t *cbuffer)
{
	assert(NULL != cbuffer);
	
	free(cbuffer);
	cbuffer = NULL;
}


/*******************************************************************************
desc: returns number of free bytes.
O(1)
*******************************************************************************/
size_t cbuffer_freespace(const cbuffer_t *cbuffer)
{
	assert(NULL != cbuffer);
	
	return cbuffer->capacity - cbuffer->size;
}


/*******************************************************************************
desc: returns number of occupied bytes.
O(1)
*******************************************************************************/
size_t cbuffer_size(const cbuffer_t *cbuffer)
{
	assert(NULL != cbuffer);
	
	return cbuffer->size;
}

/*******************************************************************************
desc:    	reads up to n_bytes from cbuffer into dest.
ret val: 	number of bytes read 	| on success
			-1 						| on error
O(n)
*******************************************************************************/
ssize_t cbuffer_read(cbuffer_t *cbuffer, void *dest, size_t n_bytes)
{
	char *dest_char = dest;
	size_t i = 0, ret = 0;
	size_t read_len = 0; 
	
	assert(NULL != cbuffer);
	assert(NULL != dest);
	
	read_len = MIN(n_bytes, cbuffer->size);
	
	if(read_len == 0)
	{
		return FAILURE;
	}
	
	ret = read_len;
	while(0 < read_len)
	{
		i = cbuffer->read_i;
		*dest_char = cbuffer->arr[i];
		++dest_char;
		--cbuffer->size;
		--read_len;
		cbuffer->read_i = ((cbuffer->read_i + 1) % cbuffer->capacity) ;
	}
	
	return ret;
}

/*******************************************************************************
desc:    	write up to n_bytes from src into cbuffer.
ret val: 	number of bytes written | on success
			-1 						| on fail, if cbuffer is full
O(n)
*******************************************************************************/
ssize_t cbuffer_write(cbuffer_t *cbuffer, const void *src, size_t n_bytes)
{
	const char *src_char = src;
	size_t i = 0, ret = 0;
	size_t write_len = 0; 
	
	assert(NULL != cbuffer);
	assert(NULL != src);
	
	write_len = MIN(n_bytes, CBufferFreeSpace(cbuffer));
	
	/*	cbuffer is full, cannot push more. */
	if(write_len == 0)
	{
		return FAILURE;
	}

	/*	we assume that we will write this much into the buffer. */
	ret = write_len;
	
	while( 0 < write_len)
	{
		i = WRITE_I(cbuffer);	
		cbuffer->arr[i] = *src_char;
		++src_char;
		++cbuffer->size;
		--write_len;
	}
	
	return ret;
}

/*******************************************************************************
desc: 		is cbuffer empty.
ret val:   	true 	| on 1
			false	| on 0
O(1)
*******************************************************************************/
int cbuffer_isempty(const cbuffer_t *cbuffer)
{
	assert(NULL != cbuffer);
	
	return (0 == cbuffer->size);
}














