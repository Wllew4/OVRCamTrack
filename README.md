# OVRCamTrack
NOT COMPLETE/RELEASED YET

OVRCamTrack is a combination of recent machine-learning-based 3D pose estimation software with OpenVR, intended to provide users with full-body tracking in Virtual Reality from only one camera input.

The program consists of two components which communicate over named pipes: a pose-estimation app and an OpenVR driver.

Pose Estimation is based on ["ThreeDPoseUnityBarracuda"](https://github.com/digital-standard/ThreeDPoseUnityBarracuda) by Digital-Standard Co., Ltd.
This absolutely would not have been possible without an efficient pose estimation program.

Driver is based on ["Simple-OpenVR-Driver-Tutorial"](https://github.com/terminal29/Simple-OpenVR-Driver-Tutorial) by terminal29.
Valve's OpenVR documentation is not the most thorough, and this project helped tremendously in learning how to interact with the OpenVR API.