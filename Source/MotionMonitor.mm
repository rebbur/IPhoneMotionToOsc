
#include "MotionMonitor.h"

#import <CoreMotion/CoreMotion.h>

@interface CoreMotionMonitor : NSObject
{
    CMMotionManager* motionManager;
    MotionMonitor* motionMonitor;
}

- (id) initWithMotionMonitorAndRate:(MotionMonitor*) motionMonitor_ rate:(float) rate;
@end


@implementation CoreMotionMonitor

- (id) initWithMotionMonitorAndRate:(MotionMonitor*) motionMonitor_ rate:(float) rate
{
    if (self = [super init])
    {
        motionManager = [[CMMotionManager alloc] init];
        motionMonitor = motionMonitor_;
        
        //CMDevice​Motion
        if([motionManager isDeviceMotionAvailable])
        {
            if([motionManager isDeviceMotionActive] == NO)
            {
                /* Update us 2 times a second */
                [motionManager setDeviceMotionUpdateInterval:1.0 / rate];
                
                [motionManager startDeviceMotionUpdatesToQueue:[NSOperationQueue mainQueue]
                                                   withHandler:^(CMDeviceMotion* motion, NSError* error)
                {
                    CMAcceleration acceleration = motion.userAcceleration;
                    CMAcceleration gravity = motion.gravity;
                    CMRotationRate rotation = motion.rotationRate;
                    CMAttitude* attitude = motion.attitude;
                    
                    MotionMonitor::MotionData motionData;
                    motionData.acceleration = juce::Vector3D<double>(acceleration.x, acceleration.y, acceleration.z);
                    motionData.gravity = juce::Vector3D<double>(gravity.x, gravity.y, gravity.z);
                    motionData.rotation = juce::Vector3D<double>(rotation.x, rotation.y, rotation.z);
                    motionData.attitude = juce::Vector3D<double>(attitude.pitch, attitude.roll, attitude.yaw);
                    motionData.angle = atan2(gravity.x, gravity.y) - M_PI;
                    motionMonitor->updateMotion(motionData);
                    
                }];
            }
        }
        else
        {
            NSLog(@"DeviceMotion not Available!");
        }
        
        /*
        if([motionManager isGyroAvailable])
        {
            // Start the gyroscope if it is not active already
            if([motionManager isGyroActive] == NO)
            {
                [motionManager setGyroUpdateInterval:1.0f / rate];
                
                // Add on a handler block object
                
                // Receive the gyroscope data on this block
                [motionManager startGyroUpdatesToQueue:[NSOperationQueue mainQueue]
                                                withHandler:^(CMGyroData *gyroData, NSError *error)
                 {                     
                     MotionMonitor::GyroData motionGyroData;
                     motionGyroData.rotationRate = juce::Vector3D<double>(gyroData.rotationRate.x,
                                                                          gyroData.rotationRate.y,
                                                                          gyroData.rotationRate.z);
                     motionMonitor->updateGyro(motionGyroData);
                 }];
            }
        }
        else
        {
            NSLog(@"Gyroscope not Available!");
        }
        */
        
    }
    return self;
}


@end

class MotionMonitor::Pimpl
{
public:
    
    Pimpl(MotionMonitor* motionMonitor, float rate)
    {
        coreMotionMonitor = [[CoreMotionMonitor alloc] initWithMotionMonitorAndRate:motionMonitor rate:rate];
    }
    
    ~Pimpl()
    {
        [coreMotionMonitor dealloc];
    }
    
    
private:
    CoreMotionMonitor* coreMotionMonitor;
};


MotionMonitor::MotionMonitor(float rate)
{
    pimpl = new Pimpl(this, rate);
    
}

MotionMonitor::~MotionMonitor()
{
    
}

void MotionMonitor::updateMotion(MotionData motionData)
{
    const ScopedLock sl(lockedMotionData);
    lockedMotionData.motionData = motionData;
    lockedMotionData.updated = true;
}

void MotionMonitor::updateGyro(GyroData gyroData)
{
    const ScopedLock sl(lockedGyroData);
    lockedGyroData.gyroData = gyroData;
    lockedGyroData.updated = true;
}

bool MotionMonitor::getMotionData(MotionData& motionData)
{
    const ScopedLock sl(lockedMotionData);
    if (!lockedMotionData.updated)
        return false;
    motionData = lockedMotionData.motionData;
    lockedMotionData.updated = false;
    return true;
}

bool MotionMonitor::getGyroData(GyroData& gyroData)
{
    const ScopedLock sl(lockedGyroData);
    if (!lockedGyroData.updated)
        return false;
    gyroData = lockedGyroData.gyroData;
    lockedGyroData.updated = false;
    return true;
}

