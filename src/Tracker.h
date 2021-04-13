#pragma once

#include <chrono>
#include <cmath>

#include <openvr_driver.h>

namespace OVRct {
    class Tracker : public vr::ITrackedDeviceServerDriver {
        public:
            Tracker(std::string serial);
            ~Tracker() = default;

            void SetPos(float pos[3]);

            std::string GetSerial();
            void Update();
            vr::TrackedDeviceIndex_t GetDeviceIndex();

            virtual vr::EVRInitError Activate(uint32_t unObjectId) override;
            virtual void Deactivate() override;
            virtual void EnterStandby() override;
            virtual void* GetComponent(const char* pchComponentNameAndVersion) override;
            virtual void DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) override;
            virtual vr::DriverPose_t GetPose() override;
            static inline vr::DriverPose_t MakeDefaultPose(bool connected = true, bool tracking = true) {
                vr::DriverPose_t out_pose = { 0 };

                out_pose.deviceIsConnected = connected;
                out_pose.poseIsValid = tracking;
                out_pose.result = tracking ? vr::ETrackingResult::TrackingResult_Running_OK : vr::ETrackingResult::TrackingResult_Running_OutOfRange;
                out_pose.willDriftInYaw = false;
                out_pose.shouldApplyHeadModel = false;
                out_pose.qDriverFromHeadRotation.w = out_pose.qWorldFromDriverRotation.w = out_pose.qRotation.w = 1.0;

                return out_pose;
            }

        private:
            float m_Pos[3] = {0,0,0};
            vr::TrackedDeviceIndex_t device_index = vr::k_unTrackedDeviceIndexInvalid;
            std::string serial_;
            vr::DriverPose_t last_pose = MakeDefaultPose();
            bool did_vibrate = false;
            float vibrate_anim_state = 0.0f;
            vr::VRInputComponentHandle_t haptic_comp = 0;
            vr::VRInputComponentHandle_t system_click_comp = 0;
            vr::VRInputComponentHandle_t system_touch_comp = 0;
    };
}