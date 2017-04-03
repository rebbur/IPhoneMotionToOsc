#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MotionMonitor
{
public:
    MotionMonitor(float rate);
    ~MotionMonitor();

    struct GyroData
    {
        Vector3D<double> rotationRate;
    };
    
    struct MotionData
    {
        Vector3D<double> acceleration;
        Vector3D<double> gravity;
        Vector3D<double> rotation;
        Vector3D<double> attitude;
        double angle;
    };
    
    struct LockedGyroData : public CriticalSection
    {
        GyroData gyroData;
        bool updated = false;
    };
    
    struct LockedMotionData : public CriticalSection
    {
        MotionData motionData;
        bool updated = false;
    };
    
    
    void updateMotion(MotionData motionData);
    void updateGyro(GyroData gyroData);
    
    bool getMotionData(MotionData& motionData);
    bool getGyroData(GyroData& gyroData);
    
private:
    class Pimpl;
    
    ScopedPointer<Pimpl> pimpl;

    LockedGyroData lockedGyroData;
    LockedMotionData lockedMotionData;
};
