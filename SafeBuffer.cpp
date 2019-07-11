/*
 *  SafeBuffer.cpp
 *  File implementing a simple, interrupt-safe character buffer for Arduino
 *  Author: Alex St. Clair
 *  July 2019
 */

#include "SafeBuffer.h"
#include "wiring.h" // for arduino interrupt functions