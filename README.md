# SafeBuffer

SafeBuffer is a simple, safe buffer class. All operations are safe and return their success -- e.g. a removal from an empty buffer is safe, and will simply return false.

As an added level of safety, the library performs no dynamic memory allocation, so the buffer itself should be statically allocated and passed in on construction of a SafeBuffer object.
