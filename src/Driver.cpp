#include "Driver.h"
#include "Tracker.h"

vr::EVRInitError OVRct::OVRDriver::Init(vr::IVRDriverContext* pDriverContext){
    //initialize
    vr::EVRInitError init_error = vr::InitServerDriverContext(pDriverContext);
    if (init_error != vr::EVRInitError::VRInitError_None) {
        return init_error;
    }

    Log("Initializing Driver");

    //add devices
    this->AddDevice(std::make_shared<Tracker>("Tracker1"));

    Log("Driver Loaded Suceessfully");

    return vr::VRInitError_None;
}

void OVRct::OVRDriver::Cleanup(){}

void OVRct::OVRDriver::RunFrame(){
    vr::VREvent_t event;
    std::vector<vr::VREvent_t> events;
    while (vr::VRServerDriverHost()->PollNextEvent(&event, sizeof(event))){
        events.push_back(event);
    }
    this->openvr_events = events;

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    this->frame_timing = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->last_frame_time);
    this->last_frame_time = now;

    for(auto &device : this->devices){
        device->Update();
    }
}

bool OVRct::OVRDriver::ShouldBlockStandbyMode(){
    return false;
}

void OVRct::OVRDriver::EnterStandby(){}

void OVRct::OVRDriver::LeaveStandby(){}

std::vector<std::shared_ptr<OVRct::OVRDevice>> OVRct::OVRDriver::GetDevices(){
    return this->devices;
}

std::vector<vr::VREvent_t> OVRct::OVRDriver::GetOpenVREvents(){
    return this->openvr_events;
}

std::chrono::milliseconds OVRct::OVRDriver::GetLastFrameTime(){
    return this->frame_timing;
}


//  Incomplete
bool OVRct::OVRDriver::AddDevice(std::shared_ptr<OVRDevice> device){
    
    bool result = vr::VRServerDriverHost()->TrackedDeviceAdded(
        device->GetSerial().c_str(),
        vr::ETrackedDeviceClass::TrackedDeviceClass_GenericTracker,
        device.get()
    );
    if(result) this->devices.push_back(device);

    return result;
}

void OVRct::OVRDriver::Log(std::string message){
    std::string message_endl = message + "\n";
    vr::VRDriverLog()->Log(message_endl.c_str());
}

vr::IVRDriverInput* OVRct::OVRDriver::GetInput(){
    return vr::VRDriverInput();
}

vr::CVRPropertyHelpers* OVRct::OVRDriver::GetProperties(){
    return vr::VRProperties();
}

vr::IVRServerDriverHost* OVRct::OVRDriver::GetDriverHost(){
    return vr::VRServerDriverHost();
}