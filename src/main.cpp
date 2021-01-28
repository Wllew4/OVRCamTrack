#include "main.h"
#include <thread>
#include "Driver.h"
#include <Windows.h>
#include <sstream>
#include <cstring>

static std::shared_ptr<OVRct::OVRDriver> driver;

void* HmdDriverFactory(const char* interface_name, int* return_code){
    if(std::strcmp(interface_name, vr::IServerTrackedDeviceProvider_Version) == 0){
        if(!driver){
            driver = std::make_shared<OVRct::OVRDriver>();
        }
        return driver.get();
    }

    if(return_code){
        *return_code = vr::VRInitError_Init_InterfaceNotFound;
    }
    return nullptr;
}

std::shared_ptr<OVRct::OVRDriver> OVRct::GetDriver(){
    return driver;
}