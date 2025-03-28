/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Parameters.h"

//==============================================================================
/**
*/
class AxelDelayPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    AxelDelayPluginAudioProcessorEditor (AxelDelayPluginAudioProcessor&);
    ~AxelDelayPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    AxelDelayPluginAudioProcessor& audioProcessor;

    juce::Slider slider;

    juce::Label label;
    
    juce::AudioProcessorValueTreeState::SliderAttachment attachment{
        audioProcessor.apvts, gainParamID.getParamID(), slider
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AxelDelayPluginAudioProcessorEditor)
};
