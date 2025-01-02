/*
  ==============================================================================

    Parameters.cpp
    Created: 1 Jan 2025 3:53:39pm
    Author:  axels

  ==============================================================================
*/

#include "Parameters.h"

Parameters::Parameters(juce::AudioProcessorValueTreeState& apvts)
{
    auto* param = apvts.getParameter(gainParamID.getParamID());
    gainParam = dynamic_cast<juce::AudioParameterFloat*>(param);
}

// Parameter Layout
juce::AudioProcessorValueTreeState::ParameterLayout 
    Parameters::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    // Gain Parameter
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        gainParamID,
        "Output Gain",
        juce::NormalisableRange<float> {-12.0f, 12.0f},
        0.0f));

    return layout;
}
