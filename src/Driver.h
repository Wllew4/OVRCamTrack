#pragma once

#include <memory>
#include <vector>
#include <chrono>
#include <variant>

#include "Device.h"

namespace OVRct {

    class OVRDriver : protected vr::IServerTrackedDeviceProvider {
        public:
            //Custom
            std::vector<std::shared_ptr<OVRDevice>> GetDevices();
            std::vector<vr::VREvent_t> GetOpenVREvents();
            std::chrono::milliseconds GetLastFrameTime();
            bool AddDevice(std::shared_ptr<OVRDevice> device);
            //Settings Key requires C++17
            vr::IVRDriverInput* GetInput();
            vr::CVRPropertyHelpers* GetProperties();
            vr::IVRServerDriverHost* GetDriverHost();
            void Log(std::string msg);
            virtual inline const char* const* GetInterfaceVersions() override {
                return vr::k_InterfaceVersions;
            }

            //  Inherited from IServerTrackedDeviceProvider
            virtual vr::EVRInitError Init(vr::IVRDriverContext* pDriverContext) override;
            virtual void Cleanup() override;
            virtual void RunFrame() override;
            virtual bool ShouldBlockStandbyMode() override;
            virtual void EnterStandby() override;
            virtual void LeaveStandby() override;


            virtual ~OVRDriver() = default;

        private:
            std::vector<std::shared_ptr<OVRDevice>> devices;
            std::vector<vr::VREvent_t> openvr_events;
            std::chrono::milliseconds frame_timing = std::chrono::milliseconds(16);
            std::chrono::system_clock::time_point last_frame_time = std::chrono::system_clock::now();
            std::string settings_key = "OVRCamTrack";
    };
}