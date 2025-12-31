#pragma once

#include <libremidi/libremidi.hpp>

#include <list>
#include <memory>
#include <mutex>

// namespace libremidi
// {
// class observer;
// }

namespace midi
{
class device_list
{
public:
    device_list();
    virtual ~device_list() = default;

private:
    libremidi::observer observer;
    std::list<libremidi::input_port> input_ports;
    std::list<libremidi::output_port> output_ports;

    std::mutex mutex;
};
}