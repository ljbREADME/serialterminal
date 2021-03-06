/*
The MIT License (MIT)

Copyright (c) 2013 Baptiste Burles, Sylvain Fay-Chatelard

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include <QtCore/QDebug>

#include "../include/SerialThread.h"


Uart SerialThread::uart;

SerialThread::SerialThread(uint8_t *pBuffer, uint32_t pSize)
{
    mBuffer = pBuffer;
    mBufferSize = pSize;
    mRun = false;
}

void SerialThread::setActiveControlLine(bool a)
{
    mActiveControlLine = a;
}

bool SerialThread::stop()
{
    mRun = false;
    return mStopped;
}

void SerialThread::run()
{
    mRun = true;
    mStopped = false;

    uint8_t data;
    uint32_t t;
    uint32_t end;
    uint32_t iterator = 0;
    uint32_t iteratorGui = 0;

    while ( mRun == true )
    {
        t = getTicks();
        end = t + 9; // refresh rate: 120Hz

        while ( t < end)
        {
            if ( getByteFromUARTNoWait(&uart, &data) == UART_OK)
            {
                mBuffer[iterator] = data;
                iterator++;
                if ( iterator >= mBufferSize)
                {
                    iterator=0;
                }
            }
            else
            {
                QThread::msleep(1);
            }

            t = getTicks();
        }


        if (mActiveControlLine==true)
        {
            emit controlState(UARTisDSRset(&uart),UARTisDTRset(&uart),UARTisRTSset(&uart),UARTisCTSset(&uart),UARTisDCDset(&uart),UARTisRNGset(&uart));
        }

        if (iteratorGui != iterator)
        {
            emit charReceived(iteratorGui,iterator);

            iteratorGui=iterator;
            if (iteratorGui >= mBufferSize)
            {
                iteratorGui = 0;
            }
        }
    }

    mStopped = true;
}
