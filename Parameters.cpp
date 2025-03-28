/*
  ==============================================================================

    Parameters.cpp
    Created: 1 Jan 2025 3:53:39pm
    Author:  axels

  ==============================================================================
*/

#include "Parameters.h"

template<typename T>
static void castParameter(juce::AudioProcessorValueTreeState& apvts, const juce::ParameterID& id, T& destination) {
    destination = dynamic_cast<T>(apvts.getParameter(id.getParamID()));
    jassert(destination);
}

// Constructor
Parameters::Parameters(juce::AudioProcessorValueTreeState& apvts)
{
    castParameter(apvts, gainParamID, gainParam);
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

void Parameters::update() noexcept {
    gain = juce::Decibels::decibelsToGain(gainParam->get());
}
