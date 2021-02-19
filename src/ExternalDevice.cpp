#include "ExternalDevice.h"
#include "main.h"

OVRct::ExternalDevice::ExternalDevice(int index, std::string name) : m_index(index), m_name(name){}

void OVRct::ExternalDevice::LogPos()
{
    OVRct::GetDriver()->Log(m_name + ": ");
    OVRct::GetDriver()->Log("X: " + std::to_string(m_Pos[0]));
    OVRct::GetDriver()->Log("Y: " + std::to_string(m_Pos[1]));
    OVRct::GetDriver()->Log("Z: " + std::to_string(m_Pos[2]));
}

float* OVRct::ExternalDevice::GetPos()
{
	return m_Pos;
}

void OVRct::ExternalDevice::UpdatePos(vr::TrackedDevicePose_t poses[3])
{
    vr::HmdMatrix34_t mat;
    mat = poses[m_index].mDeviceToAbsoluteTracking;
    m_Pos[0] = mat.m[0][3];
    m_Pos[1] = mat.m[1][3];
    m_Pos[2] = mat.m[2][3];
}