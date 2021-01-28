#pragma once

#include <chrono>
#include <cmath>

#include "Device.h"
#include "main.h"

namespace OVRct {
    class Tracker : public OVRDevice {
        public:
            Tracker(std::string serial);
            ~Tracker() = default;

            virtual std::string GetSerial() override;
            virtual void Update() override;
            virtual vr::TrackedDeviceIndex_t GetDeviceIndex() override;

            virtual vr::EVRInitError Activate(uint32_t unObjectId) override;
            virtual void Deactivate() override;
            virtual void EnterStandby() override;
            virtual void* GetComponent(const char* pchComponentNameAndVersion) override;
            virtual void DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) override;
            virtual vr::DriverPose_t GetPose() override;

        private:
            vr::TrackedDeviceIndex_t device_index = vr::k_unTrackedDeviceIndexInvalid;
            std::string serial_;
            vr::DriverPose_t last_pose = OVRDevice::MakeDefaultPose();
            bool did_vibrate = false;
            float vibrate_anim_state = 0.0f;
            vr::VRInputComponentHandle_t haptic_comp = 0;
            vr::VRInputComponentHandle_t system_click_comp = 0;
            vr::VRInputComponentHandle_t system_touch_comp = 0;
    };
}