#pragma once

#include "Module.h"

#include <stdint.h>
#include <atomic>
#include <string>

namespace mbed {
    class InterruptIn;
}

class Pin;
class StreamOutput;

class FilamentDetector: public Module
{
public:
    FilamentDetector();
    ~FilamentDetector();
    void on_module_loaded();
    void on_main_loop(void* argument);
    void on_second_tick(void* argument);
    void on_console_line_received( void *argument );

private:
    void on_pin_rise();
    void check_encoder();
    void send_command(std::string msg, StreamOutput *stream);

    mbed::InterruptIn *encoder_pin{0};
    Pin *bulge_pin{0};
    float e_last_moved{0};
    std::atomic_uint pulses{0};
    float pulses_per_mm{0};
    uint8_t seconds_per_check{1};
    uint8_t seconds_passed{0};

    struct {
        bool filament_out_alarm:1;
        bool suspended:1;
    };
};
