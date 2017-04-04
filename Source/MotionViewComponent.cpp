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
#include "network/NetworkUtils.h"
#include "settings/UserDefaults.h"
//[/Headers]

#include "MotionViewComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]


//[NamespaceStart]
String MotionViewComponent::defaultIpAddress = "10.0.1.7";
int MotionViewComponent::defaultPort = 7000;

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

    addAndMakeVisible (labelIpAddressValue = new Label ("labelIpAddressValue",
                                                        TRANS("10.0.1.7")));
    labelIpAddressValue->setFont (Font (17.20f, Font::plain));
    labelIpAddressValue->setJustificationType (Justification::centredLeft);
    labelIpAddressValue->setEditable (true, true, false);
    labelIpAddressValue->setColour (Label::outlineColourId, Colours::black);
    labelIpAddressValue->setColour (TextEditor::textColourId, Colours::black);
    labelIpAddressValue->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    labelIpAddressValue->addListener (this);

    addAndMakeVisible (labelIpAddress = new Label ("labelIpAddress",
                                                   TRANS("IP Address:")));
    labelIpAddress->setFont (Font (15.00f, Font::plain));
    labelIpAddress->setJustificationType (Justification::centredRight);
    labelIpAddress->setEditable (false, false, false);
    labelIpAddress->setColour (TextEditor::textColourId, Colours::black);
    labelIpAddress->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelPortValue = new Label ("labelPortValue",
                                                   TRANS("7000")));
    labelPortValue->setFont (Font (17.20f, Font::plain));
    labelPortValue->setJustificationType (Justification::centredLeft);
    labelPortValue->setEditable (true, true, false);
    labelPortValue->setColour (Label::outlineColourId, Colours::black);
    labelPortValue->setColour (TextEditor::textColourId, Colours::black);
    labelPortValue->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    labelPortValue->addListener (this);

    addAndMakeVisible (labelPort = new Label ("labelPort",
                                              TRANS("Port:")));
    labelPort->setFont (Font (15.00f, Font::plain));
    labelPort->setJustificationType (Justification::centredRight);
    labelPort->setEditable (false, false, false);
    labelPort->setColour (TextEditor::textColourId, Colours::black);
    labelPort->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //default settings
    ipAddress = MotionViewComponent::defaultIpAddress;
    port = MotionViewComponent::defaultPort;
    
    //load settings if present
    UserDefaults::loadString("IpAddress", ipAddress);
    long port_ = 0;
    UserDefaults::loadLong("Port", port_);
    if (port_ != 0)
        port = static_cast<int>(port_);


    labelIpAddressValue->setText(ipAddress, dontSendNotification);
    labelPortValue->setText(String(port), dontSendNotification);

    //connect
    
    oscSender.connect(ipAddress, port);
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
    labelIpAddressValue = nullptr;
    labelIpAddress = nullptr;
    labelPortValue = nullptr;
    labelPort = nullptr;


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
    labelIpAddressValue->setBounds (103, 204, 200, 24);
    labelIpAddress->setBounds (8, 204, 88, 24);
    labelPortValue->setBounds (103, 232, 200, 24);
    labelPort->setBounds (8, 232, 88, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MotionViewComponent::labelTextChanged (Label* labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    oscSender.disconnect();
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == labelIpAddressValue)
    {
        //[UserLabelCode_labelIpAddressValue] -- add your label text handling code here..
        try
        {
            String address = labelIpAddressValue->getText();
            ipAddress = address;
        }
        catch (...)
        {
            ipAddress = MotionViewComponent::defaultIpAddress;
        }

        if (ipAddress.trim().isEmpty())
            ipAddress = MotionViewComponent::defaultIpAddress;

        labelIpAddressValue->setText(ipAddress, dontSendNotification);
        
        //store ipaddress setting
        UserDefaults::storeString("IpAddress", ipAddress);
        //[/UserLabelCode_labelIpAddressValue]
    }
    else if (labelThatHasChanged == labelPortValue)
    {
        //[UserLabelCode_labelPortValue] -- add your label text handling code here..
        try
        {
            int p = labelPortValue->getText().getIntValue();
            port = p;
        }
        catch (...)
        {
            port = MotionViewComponent::defaultPort;

        }
        if (port == 0)
            port = MotionViewComponent::defaultPort;

        labelPortValue->setText(String(port), dontSendNotification);
        
        //store port setting
        UserDefaults::storeLong("Port", port);
        //[/UserLabelCode_labelPortValue]
    }

    //[UserlabelTextChanged_Post]
    oscSender.connect(ipAddress, port);
    //[/UserlabelTextChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MotionViewComponent::editorShown (Label* label, TextEditor& editor)
{
    if (labelIpAddressValue == label)
    {
        editor.setInputFilter(new TextEditor::LengthAndCharacterRestriction(15, ".012345678"), true);
    }
    else if (label == labelPortValue)
    {
        editor.setInputFilter(new TextEditor::LengthAndCharacterRestriction(6, "012345678"), true);
    }
}

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
                    OSCMessage msg_Acceleration("/iphone/motion/acceleration",
                                                (float)motionData.acceleration.x,
                                                (float)motionData.acceleration.y,
                                                (float)motionData.acceleration.z);
                    bundle.addElement(msg_Acceleration);

                    OSCMessage msg_Gravity("/iphone/motion/gravity",
                                           (float)motionData.gravity.x,
                                           (float)motionData.gravity.y,
                                           (float)motionData.gravity.z);
                    bundle.addElement(msg_Gravity);

                    OSCMessage msg_Rotation("/iphone/motion/rotation",
                                            (float)motionData.rotation.x,
                                            (float)motionData.rotation.y,
                                            (float)motionData.rotation.z);
                    bundle.addElement(msg_Rotation);

                    OSCMessage msg_Attitude("/iphone/motion/attitude",
                                            (float)motionData.attitude.x,
                                            (float)motionData.attitude.y,
                                            (float)motionData.attitude.z);
                    bundle.addElement(msg_Attitude);

                    const double angle = radiansToDegrees(motionData.angle);
                    OSCMessage msg_Angle("/iphone/motion/angle", (float)angle);
                    bundle.addElement(msg_Angle);

#ifdef JUCE_DEBUG
                    //send resolume specific message so we can
                    OSCMessage msg_res_Angle("/composition/layers/2/video/effects/transform/rotationz", String("a"), (float)angle);
                    bundle.addElement(msg_res_Angle);
#endif

                    oscSender.send(bundle);

                    const ScopedLock sl(lockedMotionData);
                    lockedMotionData.motionData = motionData;

                    newData = true;
                }

                /*
                MotionMonitor::GyroData gyroData;
                if (motionMonitor.getGyroData(gyroData))
                {

                    OSCBundle bundle;
                    OSCMessage msg_RotationRate("/iphone/gyro/rotationrate",
                                                (float)gyroData.rotationRate.x,
                                                (float)gyroData.rotationRate.y,
                                                (float)gyroData.rotationRate.z);
                    bundle.addElement(msg_RotationRate);
                    oscSender.send(bundle);

                    const ScopedLock sl(lockedGyroData);
                    lockedGyroData.gyroData = gyroData;

                    newData = true;
                }
                */
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
  <LABEL name="labelIpAddressValue" id="d23543b4d8ec0fe5" memberName="labelIpAddressValue"
         virtualName="" explicitFocusOrder="0" pos="103 204 200 24" outlineCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="10.0.1.7" editableSingleClick="1"
         editableDoubleClick="1" focusDiscardsChanges="0" fontname="Default font"
         fontsize="17.199999999999999289" bold="0" italic="0" justification="33"/>
  <LABEL name="labelIpAddress" id="6c78f2b1e2929b86" memberName="labelIpAddress"
         virtualName="" explicitFocusOrder="0" pos="8 204 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="IP Address:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="labelPortValue" id="ac1b29696eb5ad3a" memberName="labelPortValue"
         virtualName="" explicitFocusOrder="0" pos="103 232 200 24" outlineCol="ff000000"
         edTextCol="ff000000" edBkgCol="0" labelText="7000" editableSingleClick="1"
         editableDoubleClick="1" focusDiscardsChanges="0" fontname="Default font"
         fontsize="17.199999999999999289" bold="0" italic="0" justification="33"/>
  <LABEL name="labelPort" id="f99c3be829e2c092" memberName="labelPort"
         virtualName="" explicitFocusOrder="0" pos="8 232 88 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Port:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="34"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif



//[NamespaceEnd]
//[/NamespaceEnd]
//[EndFile] You can add extra defines here...
//[/EndFile]
