#ifndef _H_KERNEL_UTILS 
#define _H_KERNEL_UTILS 

typedef unsigned int k_size_t;
typedef unsigned char k_byte;

void * kmemcpy(void * dest, const void * src, const k_size_t size) {
	for(k_size_t i = 0; i < size; ++i) {
		((char *)dest)[i] = ((char *)src)[i];
	}
	return dest;
}

void * kmemset(void * dest, const k_byte val, const k_size_t size) {
	for(k_size_t i = 0; i < size; ++i) {
		((char *)dest)[i] = val;
	}

	return dest;
}

#endif 