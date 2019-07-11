# SafeBuffer

SafeBuffer is a simple Arduino library for an interrupt-safe buffer. Its designed purpose is interrupt-driven serial communication. All critical operations are made thread safe by disabling interrupts. All operations also return their success -- e.g. a removal from an empty buffer is safe, and will simply return false.

As an added level of safety, the library performs no dynamic memory allocation, so the buffer itself should be statically allocated and passed in on construction of a SafeBuffer object.
