#pragma once

#include <openvr_driver.h>

namespace OVRct {
    class OVRDevice : public vr::ITrackedDeviceServerDriver {
        public:
            virtual std::string GetSerial() = 0;
            virtual void Update() = 0;
            virtual vr::TrackedDeviceIndex_t GetDeviceIndex() = 0;
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

            virtual vr::EVRInitError Activate(uint32_t unObjectId) = 0;
            virtual void Deactivate() = 0;
            virtual void EnterStandby() = 0;
            virtual void* GetComponent(const char* pchComponentNameAndVersion) = 0;
            virtual void DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) = 0;
            virtual vr::DriverPose_t GetPose() = 0;

            ~OVRDevice() = default;
    };
}