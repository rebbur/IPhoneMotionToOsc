/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent(MotionMonitor& motionMonitor) :
    motionViewComponent(motionMonitor)
{
    addAndMakeVisible(motionViewComponent);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xff001F36));
}

void MainContentComponent::resized()
{
    motionViewComponent.setBounds(0, 0, getWidth(), getHeight());
}
