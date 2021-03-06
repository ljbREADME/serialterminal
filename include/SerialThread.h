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
#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QThread>
#include <babcode.h>


class SerialThread : public QThread
{
    Q_OBJECT
public:
    SerialThread(uint8_t* pBuffer, uint32_t pSize);

    bool stop();
    void setActiveControlLine(bool a);

    static Uart uart;
signals:
    void charReceived(int,int);
     void controlState(bool,bool,bool,bool,bool,bool);
protected:
    void run();

private:
    uint8_t*  mBuffer;
    uint32_t  mBufferSize;
    bool    mRun;
    bool    mActiveControlLine;
    bool    mStopped;
};

#endif // SERIALTHREAD_H
