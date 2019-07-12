/*
 *  SafeBuffer.cpp
 *  File implementing a simple, safe character buffer
 *  Author: Alex St. Clair
 *  July 2019
 */

#include "SafeBuffer.h"

SafeBuffer::SafeBuffer(uint8_t * buf_pointer, uint16_t buf_size)
{
    buffer = buf_pointer;
    buffer_size = buf_size;
    num_elements = 0;
    head = 0;
    tail = 0;
}

uint16_t SafeBuffer::NumElements()
{
    return num_elements;
}

bool SafeBuffer::IsEmpty()
{
    return num_elements == 0;
}

bool SafeBuffer::IsFull()
{
    return num_elements == buffer_size;
}

bool SafeBuffer::Push(uint8_t item)
{
    bool success = false;

    if (IsFull()) {
        success = false;
    } else {
        buffer[tail] = item;
        tail = (tail + 1) % buffer_size;
        num_elements++;
        success = true;
    }
    
    return success;
}

bool SafeBuffer::Peek(uint8_t * item)
{
    bool success = false;

    if (IsEmpty()) {
        success = false;
    } else {
        *item = buffer[head];
        success = true;
    }
    
    return success;
}

bool SafeBuffer::Pop(uint8_t * item)
{
    bool success = false;
    
    if (IsEmpty()) {
        success = false;
    } else {
        *item = buffer[head];
        head = (head + 1) % buffer_size;
        num_elements--;
        success = true;
    }
    
    return success;
}

void SafeBuffer::Clear()
{
    num_elements = 0;
    tail = head;
}