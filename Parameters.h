/*
  ==============================================================================

    Parameters.h
    Created: 1 Jan 2025 3:53:39pm
    Author:  axels

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

const juce::ParameterID gainParamID{ "gain", 1 };

class Parameters
{
public:

    Parameters(juce::AudioProcessorValueTreeState& apvts);

    static
        juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    juce::AudioParameterFloat* gainParam;
};
