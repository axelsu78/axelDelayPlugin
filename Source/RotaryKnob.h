/*
  ==============================================================================

    RotaryKnob.h
    Created: 27 Mar 2025 9:25:48pm
    Author:  axels

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class RotaryKnob  : public juce::Component
{
public:
    RotaryKnob(const juce::String& text,
        juce::AudioProcessorValueTreeState& aptvs,
        const juce::ParameterID& parameterID,
        bool drawFromMiddle = false);

    ~RotaryKnob() override;

    void resized() override;

    juce::Slider slider;
    juce::Label label;

	juce::AudioProcessorValueTreeState::SliderAttachment attachment;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RotaryKnob)
};
