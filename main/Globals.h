/*
 
 Copyright (c) 2017 Joel Parker
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is furnished
 to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 Early code inspired by the espressif example entitled tcp_udp_perf
 
 */


#ifndef Globals_h
#define Globals_h


#define PORT_NUMBER 6789
#define BUFLEN 512

#define RT_MOTOR_GPIO_1 26 // Speed
#define RT_MOTOR_GPIO_2 25 // Direction

#define LT_MOTOR_GPIO_3 33 // Speed
#define LT_MOTOR_GPIO_4 32 // Direction

#define WATER_GPIO_5 27 // Water Valve


#endif /* Globals_h */
