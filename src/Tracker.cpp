#include "Tracker.h"
#include "main.h"
#include "ExternalDevice.h"

OVRct::Tracker::Tracker(std::string serial): serial_(serial){}

std::string OVRct::Tracker::GetSerial(){ return this->serial_; }


vr::TrackedDevicePose_t poses[3] = {};
OVRct::ExternalDevice HMD (0, "HMD");
OVRct::ExternalDevice HandL(1, "HandL");
OVRct::ExternalDevice HandR(2, "HandR");

void OVRct::Tracker::Update(){
    if(this->device_index == vr::k_unTrackedDeviceIndexInvalid) return;

    OVRct::GetDriver()->GetDriverHost()->GetRawTrackedDevicePoses(0, poses, 3);
    HMD.UpdatePos(poses);
    HandL.UpdatePos(poses);
    HandR.UpdatePos(poses);


    auto events = GetDriver()->GetOpenVREvents();
    for(auto event : events){
        if(event.eventType == vr::EVREventType::VREvent_Input_HapticVibration){
            if(event.data.hapticVibration.componentHandle == this->haptic_comp){
                this->did_vibrate = true;
            }
        }
    }

    if(this->did_vibrate){
        this->vibrate_anim_state += (GetDriver()->GetLastFrameTime().count()/1000.0f);
        if(this->vibrate_anim_state > 1.0f){
            this->did_vibrate = false;
            this->vibrate_anim_state = 0.0f;
        }
    }

    auto pose = OVRDevice::MakeDefaultPose();
    pose.vecPosition[0] = HandL.GetPos()[0];
    pose.vecPosition[1] = HandL.GetPos()[1];
    pose.vecPosition[2] = HandL.GetPos()[2];

    GetDriver()->GetDriverHost()->TrackedDevicePoseUpdated(this->device_index, pose, sizeof(vr::DriverPose_t));
    this->last_pose = pose;
}

vr::TrackedDeviceIndex_t OVRct::Tracker::GetDeviceIndex(){ return this->device_index; }

vr::EVRInitError OVRct::Tracker::Activate(uint32_t unObjectId){
    this->device_index = unObjectId;

    GetDriver()->Log("Activating tracker hello " + this->serial_);

    auto props = GetDriver()->GetProperties()->TrackedDeviceToPropertyContainer(this->device_index);

    GetDriver()->GetInput()->CreateHapticComponent(props, "/output/haptic", &this->haptic_comp);

    GetDriver()->GetInput()->CreateBooleanComponent(props, "/input/system/click", &this->system_click_comp);
    GetDriver()->GetInput()->CreateBooleanComponent(props, "/input/system/touch", &this->system_touch_comp);

    // Set some universe ID (Must be 2 or higher)
    GetDriver()->GetProperties()->SetUint64Property(props, vr::Prop_CurrentUniverseId_Uint64, 2);
    
    // Set up a model "number" (not needed but good to have)
    GetDriver()->GetProperties()->SetStringProperty(props, vr::Prop_ModelNumber_String, "example_tracker");

    // Opt out of hand selection
    GetDriver()->GetProperties()->SetInt32Property(props, vr::Prop_ControllerRoleHint_Int32, vr::ETrackedControllerRole::TrackedControllerRole_OptOut);

    // Set up a render model path
    GetDriver()->GetProperties()->SetStringProperty(props, vr::Prop_RenderModelName_String, "vr_controller_05_wireless_b");

    // Set controller profile
    GetDriver()->GetProperties()->SetStringProperty(props, vr::Prop_InputProfilePath_String, "{OVRCamTrack}/input/example_tracker_bindings.json");

    // Set the icon
    GetDriver()->GetProperties()->SetStringProperty(props, vr::Prop_NamedIconPathDeviceReady_String, "{OVRCamTrack}/icons/tracker_ready.png");

    GetDriver()->GetProperties()->SetStringProperty(props, vr::Prop_NamedIconPathDeviceOff_String, "{OVRCamTrack}/icons/tracker_not_ready.png");
    GetDriver()->GetProperties()->SetStringProperty(props, vr::Prop_NamedIconPathDeviceSearching_String, "{OVRCamTrack}/icons/tracker_not_ready.png");
    GetDriver()->GetProperties()->SetStringProperty(props, vr::Prop_NamedIconPathDeviceSearchingAlert_String, "{OVRCamTrack}/icons/tracker_not_ready.png");
    GetDriver()->GetProperties()->SetStringProperty(props, vr::Prop_NamedIconPathDeviceReadyAlert_String, "{OVRCamTrack}/icons/tracker_not_ready.png");
    GetDriver()->GetProperties()->SetStringProperty(props, vr::Prop_NamedIconPathDeviceNotReady_String, "{OVRCamTrack}/icons/tracker_not_ready.png");
    GetDriver()->GetProperties()->SetStringProperty(props, vr::Prop_NamedIconPathDeviceStandby_String, "{OVRCamTrack}/icons/tracker_not_ready.png");
    GetDriver()->GetProperties()->SetStringProperty(props, vr::Prop_NamedIconPathDeviceAlertLow_String, "{OVRCamTrack}/icons/tracker_not_ready.png");

    return vr::EVRInitError::VRInitError_None;
}

void OVRct::Tracker::Deactivate(){ this->device_index = vr::k_unTrackedDeviceIndexInvalid; }

void OVRct::Tracker::EnterStandby(){}

void* OVRct::Tracker::GetComponent(const char* pchComponentNameAndVersion){ return nullptr; }

void OVRct::Tracker::DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize){
    if(unResponseBufferSize >= 1) pchResponseBuffer[0] = 0;
}

vr::DriverPose_t OVRct::Tracker::GetPose(){ return last_pose; }