#pragma once

#include <memory>

namespace libremidi
{
struct input_port;
}

namespace midi
{
class InputDevice
{
public:
    InputDevice() = default;
    virtual ~InputDevice() = default;

private:
    std::unique_ptr<libremidi::input_port> port;
};
}