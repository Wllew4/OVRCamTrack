#pragma once
#include <openvr_driver.h>
#include <string>

namespace OVRct {
	class ExternalDevice
	{
	private:
		int m_index;
		std::string m_name;
		float* m_Pos = new float[3];
	public:
		ExternalDevice(int index, std::string name);
		void LogPos();
		float* GetPos();
		void UpdatePos(vr::TrackedDevicePose_t poses[3]);
	};
}