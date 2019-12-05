/*
The MIT License (MIT)

Copyright (c) 2016 British Broadcasting Corporation.
This software is provided by Lancaster University by arrangement with the BBC.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

/**
  * Class definition for a MicroBitEvent
  *
  * It represents a common event that is generated by the various components on the micro:bit.
  */
#include "MicroBitConfig.h"
#include "MicroBitEvent.h"
#include "MicroBitSystemTimer.h"
#include "EventModel.h"

EventModel* EventModel::defaultEventBus = NULL;

/**
  * Constructor.
  *
  * @param src The id of the MicroBit Component that generated the event e.g. MICROBIT_ID_BUTTON_A.
  *
  * @param value A component specific code indicating the cause of the event.
  *
  * @param mode Optional definition of how the event should be processed after construction (if at all):
  *                 CREATE_ONLY: MicroBitEvent is initialised, and no further processing takes place.
  *                 CREATE_AND_FIRE: MicroBitEvent is initialised, and its event handlers are immediately fired (not suitable for use in interrupts!).
  *
  * @code
  * // Create and launch an event using the default configuration
  * MicrobitEvent evt(id,MICROBIT_BUTTON_EVT_CLICK);
  *
  * // Create an event only, do not fire onto an EventModel.
  * MicrobitEvent evt(id,MICROBIT_BUTTON_EVT_CLICK,CREATE_AND_FIRE);
  * @endcode
  */
MicroBitEvent::MicroBitEvent(uint16_t source, uint16_t value, MicroBitEventLaunchMode mode)
{
    this->source = source;
    this->value = value;
    this->timestamp = system_timer_current_time_us();

    if(mode != CREATE_ONLY)
        this->fire();
}

/**
  * Default constructor - initialises all values, and sets timestamp to the current time.
  */
MicroBitEvent::MicroBitEvent()
{
    this->source = 0;
    this->value = 0;
    this->timestamp = system_timer_current_time_us();
}

/**
  * Fires this MicroBitEvent onto the Default EventModel, or a custom one!
  */
void MicroBitEvent::fire()
{
	if(EventModel::defaultEventBus)
		EventModel::defaultEventBus->send(*this);
}


/**
  * Constructor.
  * Create a new MicroBitEventQueueItem.
  *
  * @param evt The event to be queued.
  */
MicroBitEventQueueItem::MicroBitEventQueueItem(MicroBitEvent evt)
{
    this->evt = evt;
	this->next = NULL;
}