/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AxelDelayPluginAudioProcessor::AxelDelayPluginAudioProcessor() :
    AudioProcessor(
        BusesProperties()
            .withInput("Input", juce::AudioChannelSet::stereo(), true)
            .withOutput("Output", juce::AudioChannelSet::stereo(), true)
    )
{
    auto* param = apvts.getParameter(gainParamID.getParamID());
    gainParam = dynamic_cast<juce::AudioParameterFloat*>(param);
}

AxelDelayPluginAudioProcessor::~AxelDelayPluginAudioProcessor()
{
}

//==============================================================================
// getName
const juce::String AxelDelayPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

// acceptsMidi
bool AxelDelayPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

// producesMidi
bool AxelDelayPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

// isMidiEffect
bool AxelDelayPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

// getTailLengthSeconds
double AxelDelayPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

// getNumPrograms
int AxelDelayPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

// getCurrentProgram
int AxelDelayPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

// setCurrentProgram
void AxelDelayPluginAudioProcessor::setCurrentProgram (int index)
{
}

// getProgramName
const juce::String AxelDelayPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

// changeProgramName
void AxelDelayPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
// prepareToPlay
void AxelDelayPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

// releaseResources
void AxelDelayPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

// isBusesLayoutSupported
#ifndef JucePlugin_PreferredChannelConfigurations
bool AxelDelayPluginAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const {
return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}
#endif

// processBlock
void AxelDelayPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    float gainInDecibels = gainParam->get();

    float gain = juce::Decibels::decibelsToGain(gainInDecibels);
    
    for (int channel = 0; channel < totalNumInputChannels; channel++) {
        auto* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); sample++) {
            channelData[sample] *= gain;
        }
    }

        // ..do something to the data...
}

//==============================================================================

// hasEditor
bool AxelDelayPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

// createEditor
juce::AudioProcessorEditor* AxelDelayPluginAudioProcessor::createEditor()
{
    return new AxelDelayPluginAudioProcessorEditor (*this);
}

//==============================================================================

// getStateInformation
void AxelDelayPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    copyXmlToBinary(*apvts.copyState().createXml(), destData);
}

// setStateInformation
void AxelDelayPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml.get() != nullptr && xml->hasTagName(apvts.state.getType())) {
        apvts.replaceState(juce::ValueTree::fromXml(*xml));
    }
}

//==============================================================================

// createPluginFilter
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AxelDelayPluginAudioProcessor();
}

// Parameter Layout
juce::AudioProcessorValueTreeState::ParameterLayout
AxelDelayPluginAudioProcessor::createParameterLayout() {
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    // Gain Parameter
    layout.add(std::make_unique<juce::AudioParameterFloat>(
        gainParamID,
        "Output Gain",
        juce::NormalisableRange<float> {-12.0f, 12.0f},
        0.0f));

    return layout;
}
