/*
 * SimpleTimer.h
 *
 * SimpleTimer - A timer library for Arduino.
 * Author: mromani@ottotecnica.com
 * Copyright (c) 2010 OTTOTECNICA Italy
 *
 * This library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser
 * General Public License as published by the Free Software
 * Foundation; either version 2.1 of the License, or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser
 * General Public License along with this library; if not,
 * write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 *
 */


#ifndef SIMPLETIMER_H
#define SIMPLETIMER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

typedef void (*timer_callback)(void);

class SimpleTimer {

public:
    // maximum number of timers
    const static uint8_t MAX_TIMERS = 10;

    // setTimer() constants
    const static uint8_t RUN_FOREVER = 0;
    const static uint8_t RUN_ONCE = 1;

    // constructor
    SimpleTimer();

    // this function must be called inside loop()
    void run();

    // call function f every d milliseconds
    int8_t setInterval(uint32_t d, timer_callback f);

    // call function f once after d milliseconds
    int8_t setTimeout(uint32_t d, timer_callback f);

    // call function f every d milliseconds for n times
    int8_t setTimer(uint32_t d, timer_callback f, uint8_t n);

    // destroy the specified timer
    uint8_t deleteTimer(uint8_t numTimer);

    // restart the specified timer
    void restartTimer(uint8_t numTimer);

    // returns true if the specified timer is enabled
    boolean isEnabled(uint8_t numTimer);

    // enables the specified timer
    void enable(uint8_t numTimer);

    // disables the specified timer
    void disable(uint8_t numTimer);

    // enables the specified timer if it's currently disabled,
    // and vice-versa
    void toggle(uint8_t numTimer);

    // returns the number of used timers
    uint8_t getNumTimers();

    // returns the number of available timers
    uint8_t getNumAvailableTimers() { return MAX_TIMERS - numTimers; };

private:
    // deferred call constants
    const static uint8_t DEFCALL_DONTRUN = 0;       // don't call the callback function
    const static uint8_t DEFCALL_RUNONLY = 1;       // call the callback function but don't delete the timer
    const static uint8_t DEFCALL_RUNANDDEL = 2;      // call the callback function and delete the timer

    // find the first available slot
    int8_t findFirstFreeSlot();

    // value returned by the millis() function
    // in the previous run() call
    volatile uint32_t prev_millis[MAX_TIMERS];

    // pointers to the callback functions
    timer_callback callbacks[MAX_TIMERS];

    // delay values
    uint32_t delays[MAX_TIMERS];

    // number of runs to be executed for each timer
    uint8_t maxNumRuns[MAX_TIMERS];

    // number of executed runs for each timer
    uint8_t numRuns[MAX_TIMERS];

    // which timers are enabled
    boolean enabled[MAX_TIMERS];

    // deferred function call (sort of) - N.B.: this array is only used in run()
    uint8_t toBeCalled[MAX_TIMERS];

    // actual number of timers in use
    uint8_t numTimers;
};

#endif
