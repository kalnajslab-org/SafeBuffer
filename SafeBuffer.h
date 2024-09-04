/*
 *  SafeBuffer.h
 *  File defining a simple, safe character buffer
 *  Author: Alex St. Clair
 *  July 2019
 */
 
#ifndef SAFEBUFFER_H
#define SAFEBUFFER_H

#include <stdint.h>

class SafeBuffer {
public:
    // constructor and destructor (the object must be passed an allocated buffer)
	SafeBuffer(uint8_t * buf_pointer, uint16_t buf_size);
	~SafeBuffer() { };

    // size checks
    uint16_t NumElements();
	bool IsEmpty();
	bool IsFull();

    // buffer additions and subtractions
    bool Push(uint8_t item);
	bool Pop(uint8_t * item);
    bool Peek(uint8_t * item);

    // empty the buffer
    void Clear();

private:
	uint16_t buffer_size;  // maximum allocated size
    uint16_t num_elements; // current number of elements

	uint16_t head; // pop from here
	uint16_t tail; // push to here

	uint8_t * buffer; // pointer to the preallocated buffer passed in at construction

};

#endif /* SAFEBUFFER_H */
