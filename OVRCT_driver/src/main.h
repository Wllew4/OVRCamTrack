#pragma once

#include <cstdlib>
#include <memory>
#include <openvr_driver.h>
#include "Driver.h"

extern "C" __declspec(dllexport) void* HmdDriverFactory(const char* interface_name, int* return_code);

namespace OVRct {
    std::shared_ptr<OVRct::OVRDriver> GetDriver();
}