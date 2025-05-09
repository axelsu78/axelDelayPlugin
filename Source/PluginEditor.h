/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Parameters.h"
#include "RotaryKnob.h"
#include "LookAndFeel.h"

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

    // Knobs:
    RotaryKnob gainKnob { "Gain", audioProcessor.apvts, gainParamID, true };
    RotaryKnob mixKnob{ "Mix", audioProcessor.apvts, mixParamID };
	RotaryKnob delayTimeKnob{ "Delay Time", audioProcessor.apvts, delayTimeParamID };

    juce::GroupComponent delayGroup, feedbackGroup, outputGroup;

    MainLookAndFeel mainLF;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AxelDelayPluginAudioProcessorEditor)
};
