/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.3.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_7C8A323F905C5140__
#define __JUCE_HEADER_7C8A323F905C5140__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "MotionMonitor.h"

//[/Headers]



//[NamespaceStart]
//[/NamespaceStart]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MotionViewComponent  : public Component,
                             public Thread,
                             public AsyncUpdater,
                             public LabelListener
{
public:
    //==============================================================================
    MotionViewComponent (MotionMonitor& motionMonitor_);
    ~MotionViewComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void editorShown (Label* label, TextEditor& editor) override;
        void handleAsyncUpdate() override;
    void run() override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void labelTextChanged (Label* labelThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    MotionMonitor& motionMonitor;
    MotionMonitor::LockedMotionData lockedMotionData;
    MotionMonitor::LockedGyroData lockedGyroData;

    OSCSender oscSender;
    static String defaultIpAddress;
    static int defaultPort;

    String ipAddress;
    int port;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> accelerationLabel;
    ScopedPointer<Label> gravityLabel;
    ScopedPointer<Label> rotationLabel;
    ScopedPointer<Label> attitudeLabel;
    ScopedPointer<Label> accelerationValueLabel;
    ScopedPointer<Label> gravityValueLabel;
    ScopedPointer<Label> rotationValueLabel;
    ScopedPointer<Label> attitudeValueLabel;
    ScopedPointer<Label> angleLabel;
    ScopedPointer<Label> angleValueLabel;
    ScopedPointer<Label> labelIpAddressValue;
    ScopedPointer<Label> labelIpAddress;
    ScopedPointer<Label> labelPortValue;
    ScopedPointer<Label> labelPort;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MotionViewComponent)
};


//[NamespaceEnd]
//[/NamespaceEnd]
//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_7C8A323F905C5140__
