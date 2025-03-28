/*
  ==============================================================================

    RotaryKnob.cpp
    Created: 27 Mar 2025 9:25:48pm
    Author:  axels

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RotaryKnob.h"

//==============================================================================
RotaryKnob::RotaryKnob(const juce::String& text,
    juce::AudioProcessorValueTreeState& aptvs,
    const juce::ParameterID& parameterID)
    : attachment(aptvs, parameterID.getParamID(), slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 16);
    slider.setBounds(0, 0, 70, 86);
    addAndMakeVisible(slider);

    label.setText(text, juce::NotificationType::dontSendNotification);
    label.setJustificationType(juce::Justification::horizontallyCentred);
    label.setBorderSize(juce::BorderSize<int>{0, 0, 2, 0});
    label.attachToComponent(&slider, false);
    addAndMakeVisible(label);

    setSize(70, 110);
}

RotaryKnob::~RotaryKnob()
{
}

void RotaryKnob::resized(){
    slider.setTopLeftPosition(0, 24);
}
