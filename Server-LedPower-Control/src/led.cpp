#include <iostream>
#include <gpiod.hpp>
#include <thread>

#define ledLine 19
const char* chipname = "gpiochip0";

int main(int argc, const char** argv) {

    // line configuration
    gpiod::line_request lreq;
    lreq.request_type = lreq.DIRECTION_OUTPUT;
    lreq.flags = lreq.FLAG_OPEN_SOURCE;
    
    try {
        gpiod::chip gpioChip1(chipname, gpiod::chip::OPEN_LOOKUP);

        gpiod::line line = gpioChip1.get_line(ledLine);

        // Check if the line is requested
        if (!line.is_requested()) {
            // If not requested, request it
            line.request(lreq);
        }
        
        // set line value
        line.set_value(static_cast<int>(*argv[1]-'0'));
    
    } catch (const std::system_error& e) {
        std::cerr << "Error: " << e.what() << " (code " << e.code() << ")" << std::endl;
        return 1;
    }

    return 0;
}


