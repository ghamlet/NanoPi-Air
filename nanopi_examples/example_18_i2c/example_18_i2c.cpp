//-------------------------------------------------------------------------

#include <array>
#include <chrono>
#include <cmath>
#include <csignal>
#include <cstring>
#include <exception>
#include <iostream>
#include <memory>
#include <thread>
#include <system_error>



#include "OledFont8x8.h"
#include "OledFont8x16.h"
#include "OledI2C.h"

//-------------------------------------------------------------------------

namespace
{
volatile static std::sig_atomic_t run = 1;
}



static void
signalHandler(
    int signalNumber)
{
    switch (signalNumber)
    {
    case SIGINT:
    case SIGTERM:

        run = 0;
        break;
    };
}

//-------------------------------------------------------------------------

void
helloworld(
    SSD1306::OledI2C& oled)
{
    //---------------------------------------------------------------------

    static constexpr SSD1306::PixelStyle style{SSD1306::PixelStyle::Set};

    //---------------------------------------------------------------------

    char mess[12] = "Hello World";
    int length = 11;
    int offset = (128 - (8 * length)) / 2;

    SSD1306::OledPoint location{offset, 18};

    location = drawString8x16(location, mess, style, oled);

    //---------------------------------------------------------------------


    oled.displayUpdate();
}

//-------------------------------------------------------------------------

int
main()
{
    try
    {
        constexpr std::array<int, 2> signals{SIGINT, SIGTERM};

        for (auto signal : signals)
        {
            if (std::signal(signal, signalHandler) == SIG_ERR)
            {
                std::string what{"installing "};
                what += strsignal(signal);
                what += " signal handler";

                throw std::system_error(errno,
                                        std::system_category(),
                                        what);
            }
        }

        SSD1306::OledI2C oled{"/dev/i2c-0", 0x3C};

        while (run)
        {
            helloworld(oled);


        }

        oled.clear();
        oled.displayUpdate();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << "\n";
    }

    return 0;
}

