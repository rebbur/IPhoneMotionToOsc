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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MotionViewComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]


//[NamespaceStart]
//[/NamespaceStart]

//==============================================================================
MotionViewComponent::MotionViewComponent (MotionMonitor& motionMonitor_)
    : Thread("Motion Thread"),
      motionMonitor( motionMonitor_)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (accelerationLabel = new Label ("accelerationLabel",
                                                      TRANS("Acceleration:")));
    accelerationLabel->setFont (Font (15.00f, Font::plain));
    accelerationLabel->setJustificationType (Justification::centredRight);
    accelerationLabel->setEditable (false, false, false);
    accelerationLabel->setColour (TextEditor::textColourId, Colours::black);
    accelerationLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (gravityLabel = new Label ("gravityLabel",
                                                 TRANS("Gravity:")));
    gravityLabel->setFont (Font (15.00f, Font::plain));
    gravityLabel->setJustificationType (Justification::centredRight);
    gravityLabel->setEditable (false, false, false);
    gravityLabel->setColour (TextEditor::textColourId, Colours::black);
    gravityLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (rotationLabel = new Label ("rotationLabel",
                                                  TRANS("Rotation:")));
    rotationLabel->setFont (Font (15.00f, Font::plain));
    rotationLabel->setJustificationType (Justification::centredRight);
    rotationLabel->setEditable (false, false, false);
    rotationLabel->setColour (TextEditor::textColourId, Colours::black);
    rotationLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (attitudeLabel = new Label ("attitudeLabel",
                                                  TRANS("Attitude:")));
    attitudeLabel->setFont (Font (15.00f, Font::plain));
    attitudeLabel->setJustificationType (Justification::centredRight);
    attitudeLabel->setEditable (false, false, false);
    attitudeLabel->setColour (TextEditor::textColourId, Colours::black);
    attitudeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (accelerationValueLabel = new Label ("accelerationValueLabel",
                                                           TRANS("x: y: z:")));
    accelerationValueLabel->setFont (Font (15.00f, Font::plain));
    accelerationValueLabel->setJustificationType (Justification::centredLeft);
    accelerationValueLabel->setEditable (false, false, false);
    accelerationValueLabel->setColour (TextEditor::textColourId, Colours::black);
    accelerationValueLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (gravityValueLabel = new Label ("gravityValueLabel",
                                                      TRANS("x: y: z:")));
    gravityValueLabel->setFont (Font (15.00f, Font::plain));
    gravityValueLabel->setJustificationType (Justification::centredLeft);
    gravityValueLabel->setEditable (false, false, false);
    gravityValueLabel->setColour (TextEditor::textColourId, Colours::black);
    gravityValueLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (rotationValueLabel = new Label ("rotationValueLabel",
                                                       TRANS("x: y: z:")));
    rotationValueLabel->setFont (Font (15.00f, Font::plain));
    rotationValueLabel->setJustificationType (Justification::centredLeft);
    rotationValueLabel->setEditable (false, false, false);
    rotationValueLabel->setColour (TextEditor::textColourId, Colours::black);
    rotationValueLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (attitudeValueLabel = new Label ("attitudeValueLabel",
                                                       TRANS("pitch: roll: yaw:")));
    attitudeValueLabel->setFont (Font (15.00f, Font::plain));
    attitudeValueLabel->setJustificationType (Justification::centredLeft);
    attitudeValueLabel->setEditable (false, false, false);
    attitudeValueLabel->setColour (TextEditor::textColourId, Colours::black);
    attitudeValueLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (angleLabel = new Label ("angleLabel",
                                               TRANS("Angle:")));
    angleLabel->setFont (Font (15.00f, Font::plain));
    angleLabel->setJustificationType (Justification::centredRight);
    angleLabel->setEditable (false, false, false);
    angleLabel->setColour (TextEditor::textColourId, Colours::black);
    angleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (angleValueLabel = new Label ("angleValueLabel",
                                                    String()));
    angleValueLabel->setFont (Font (15.00f, Font::plain));
    angleValueLabel->setJustificationType (Justification::centredLeft);
    angleValueLabel->setEditable (false, false, false);
    angleValueLabel->setColour (TextEditor::textColourId, Colours::black);
    angleValueLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    ipAddress = "10.0.1.7";
    port = 7000;

    oscSender.connect("10.0.1.7", 7000);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    startThread(7);
    //[/Constructor]
}

MotionViewComponent::~MotionViewComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    stopThread(4000);
    //[/Destructor_pre]

    accelerationLabel = nullptr;
    gravityLabel = nullptr;
    rotationLabel = nullptr;
    attitudeLabel = nullptr;
    accelerationValueLabel = nullptr;
    gravityValueLabel = nullptr;
    rotationValueLabel = nullptr;
    attitudeValueLabel = nullptr;
    angleLabel = nullptr;
    angleValueLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MotionViewComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MotionViewComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    accelerationLabel->setBounds (8, 8, 88, 24);
    gravityLabel->setBounds (8, 36, 88, 24);
    rotationLabel->setBounds (8, 64, 88, 24);
    attitudeLabel->setBounds (8, 92, 88, 24);
    accelerationValueLabel->setBounds (103, 8, getWidth() - 112, 24);
    gravityValueLabel->setBounds (103, 36, getWidth() - 112, 24);
    rotationValueLabel->setBounds (103, 64, getWidth() - 112, 24);
    attitudeValueLabel->setBounds (103, 92, getWidth() - 112, 24);
    angleLabel->setBounds (8, 120, 88, 24);
    angleValueLabel->setBounds (103, 120, getWidth() - 112, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
String constructXYZString(const Vector3D<double>& vector)
{
    return "x: " + String(vector.x, 2) + " y: " + String(vector.y, 2) + " z: " + String(vector.z, 2);
}

String constructPitchRollYawString(const Vector3D<double>& vector)
{
    return "Pitch: " + String(vector.x, 2) + " Roll: " + String(vector.y, 2) + " Yaw: " + String(vector.z, 2);
}

void MotionViewComponent::handleAsyncUpdate()
{
    MotionMonitor::MotionData motionData;
    {
        const ScopedLock sl(lockedMotionData);
        motionData = lockedMotionData.motionData;
    }

    accelerationValueLabel->setText(constructXYZString(motionData.acceleration), dontSendNotification);
    gravityValueLabel->setText(constructXYZString(motionData.gravity), dontSendNotification);
    rotationValueLabel->setText(constructXYZString(motionData.rotation), dontSendNotification);
    attitudeValueLabel->setText(constructPitchRollYawString(motionData.attitude), dontSendNotification);
    angleValueLabel->setText(String(radiansToDegrees(motionData.angle), 2), dontSendNotification);
}

void MotionViewComponent::run()
{

    while (!threadShouldExit())
    {
        {
            {
                bool newData = false;
                MotionMonitor::MotionData motionData;
                if (motionMonitor.getMotionData(motionData))
                {


                    OSCBundle bundle;
                    /*
                    OSCMessage msg_Acceleration("/motion/acceleration",
                                                (float)motion_Acceleration.x,
                                                (float)motion_Acceleration.y,
                                                (float)motion_Acceleration.z);
                    bundle.addElement(msg_Acceleration);

                    OSCMessage msg_Gravity("/motion/gravity",
                                           (float)motion_Gravity.x,
                                           (float)motion_Gravity.y,
                                           (float)motion_Gravity.z);
                    bundle.addElement(msg_Gravity);

                    OSCMessage msg_Rotation("/motion/rotation",
                                            (float)motion_Rotation.x,
                                            (float)motion_Rotation.y,
                                            (float)motion_Rotation.z);
                    bundle.addElement(msg_Rotation);

                    OSCMessage msg_Attitude("/motion/attitude",
                                            (float)motion_Attitude.x,
                                            (float)motion_Attitude.y,
                                            (float)motion_Attitude.z);
                    bundle.addElement(msg_Attitude);
                    */


                    double angle = radiansToDegrees(motionData.angle);

                    //double resangle = -180.0 + angle;





                    OSCMessage msg_Angle("/composition/layers/2/video/effects/transform/rotationz", String("a"), (float)angle);

                    //bundle.addElement(msg_Angle);
                    oscSender.sendToIPAddress("10.0.1.7", 7000, msg_Angle);
                    //(msg_Angle);

                    const ScopedLock sl(lockedMotionData);
                    lockedMotionData.motionData = motionData;


                    newData = true;


                }

                MotionMonitor::GyroData gyroData;
                if (motionMonitor.getGyroData(gyroData))
                {
                    /*
                     OSCBundle bundle;
                     OSCMessage msg_RotationRate("/gyro/rotationrate",
                     (float)gyro_RotationRate.x,
                     (float)gyro_RotationRate.y,
                     (float)gyro_RotationRate.z);
                     bundle.addElement(msg_RotationRate);

                     sender.sendToIPAddress (ipAddress, port, bundle);
                     */
                    const ScopedLock sl(lockedGyroData);
                    lockedGyroData.gyroData = gyroData;

                    newData = true;
                }

                if (newData)
                    triggerAsyncUpdate();


            }

        }

        Thread::wait(10);
    }

}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MotionViewComponent" componentName=""
                 parentClasses="public Component, public Thread, public AsyncUpdater"
                 constructorParams="MotionMonitor&amp; motionMonitor_" variableInitialisers="Thread(&quot;Motion Thread&quot;),&#10;motionMonitor( motionMonitor_)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="accelerationLabel" id="5887b2f6fe7dddb9" memberName="accelerationLabel"
         virtualName="" explicitFocusOrder="0" pos="8 8 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Acceleration:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="gravityLabel" id="a3059c2151e1577a" memberName="gravityLabel"
         virtualName="" explicitFocusOrder="0" pos="8 36 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Gravity:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <LABEL name="rotationLabel" id="cd33930a1fedf14a" memberName="rotationLabel"
         virtualName="" explicitFocusOrder="0" pos="8 64 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Rotation:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <LABEL name="attitudeLabel" id="49b3704305a023c" memberName="attitudeLabel"
         virtualName="" explicitFocusOrder="0" pos="8 92 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Attitude:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <LABEL name="accelerationValueLabel" id="ef9c9cbeae0ef36d" memberName="accelerationValueLabel"
         virtualName="" explicitFocusOrder="0" pos="103 8 112M 24" edTextCol="ff000000"
         edBkgCol="0" labelText="x: y: z:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="gravityValueLabel" id="a27c9bc7e2a88ba8" memberName="gravityValueLabel"
         virtualName="" explicitFocusOrder="0" pos="103 36 112M 24" edTextCol="ff000000"
         edBkgCol="0" labelText="x: y: z:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="rotationValueLabel" id="89b3f56b4fe7437f" memberName="rotationValueLabel"
         virtualName="" explicitFocusOrder="0" pos="103 64 112M 24" edTextCol="ff000000"
         edBkgCol="0" labelText="x: y: z:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="attitudeValueLabel" id="861d6f3b9bb125df" memberName="attitudeValueLabel"
         virtualName="" explicitFocusOrder="0" pos="103 92 112M 24" edTextCol="ff000000"
         edBkgCol="0" labelText="pitch: roll: yaw:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="angleLabel" id="df8b35ef9c855dd0" memberName="angleLabel"
         virtualName="" explicitFocusOrder="0" pos="8 120 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Angle:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
  <LABEL name="angleValueLabel" id="c73ccc1bc4eb9562" memberName="angleValueLabel"
         virtualName="" explicitFocusOrder="0" pos="103 120 112M 24" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif



//[NamespaceEnd]
//[/NamespaceEnd]
//[EndFile] You can add extra defines here...
//[/EndFile]
