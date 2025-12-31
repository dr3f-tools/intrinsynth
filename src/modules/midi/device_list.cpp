#include "logger/logger.h"
#include "midi/device_list.h"

midi::device_list::device_list()
: observer{libremidi::observer_configuration{
      .on_error =
          [](const std::string_view& err, const std::source_location& loc) {
              logger::log("[ERROR]: {}" /*, loc*/, err);
          },
      .on_warning =
          [](const std::string_view& warn, const std::source_location& loc) {
              logger::log("[WARN]: {}" /*, loc*/, warn);
          },
      .input_added =
          [this](const libremidi::input_port& port) {
              std::unique_lock lock(mutex);
              if (std::find(input_ports.begin(), input_ports.end(), port) == input_ports.end()) {
                  input_ports.push_back(port);
                  logger::log("Input port added: {}", port.port_name);
              }
          },
      .input_removed =
          [this](const libremidi::input_port& port) {
              std::unique_lock lock(mutex);
              if (std::find(input_ports.begin(), input_ports.end(), port) != input_ports.end()) {
                  input_ports.remove(port);
                  logger::log("Input port removed: {}", port.port_name);
              }
          },
      .output_added =
          [this](const libremidi::output_port& port) {
              std::unique_lock lock(mutex);
              if (std::find(output_ports.begin(), output_ports.end(), port) == output_ports.end()) {
                  output_ports.push_back(port);
                  logger::log("Input port added: {}", port.port_name);
              }
          },
      .output_removed =
          [this](const libremidi::output_port& port) {
              std::unique_lock lock(mutex);
              if (std::find(output_ports.begin(), output_ports.end(), port) != output_ports.end()) {
                  output_ports.remove(port);
                  logger::log("Input port removed: {}", port.port_name);
              }
          },
      .track_hardware = true,
      .track_virtual = true,
      .track_any = false,
      .notify_in_constructor = false
  }} {}