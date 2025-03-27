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
    ),
    params(apvts)
{
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
	params.prepareToPlay(sampleRate);
    params.reset();

    juce::dsp::ProcessSpec spec;
	spec.sampleRate = sampleRate;
    spec.maximumBlockSize = juce::uint32(samplesPerBlock);
    spec.numChannels = 2;
    
    delayLine.prepare(spec);

    double numSamples = Parameters::maxDelayTime / 1000.0 * sampleRate;
    int maxDelayInSamples = int(std::ceil(numSamples));
    delayLine.setMaximumDelayInSamples(maxDelayInSamples);
    delayLine.reset();

    DBG(maxDelayInSamples);
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

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    params.update();

    float sampleRate = float(getSampleRate());
    float delayInSamples = params.delayTime / 1000.0f * sampleRate;
    delayLine.setDelay(delayInSamples);
    
	float* channelDataL = buffer.getWritePointer(0);
	float* channelDataR = buffer.getWritePointer(1);

    for (int sample = 0; sample < buffer.getNumSamples(); sample++) {
        params.smoothen();

        float dryL = channelDataL[sample];
        float dryR = channelDataR[sample];

        delayLine.pushSample(0, dryL);
		delayLine.pushSample(1, dryR);

		float wetL = delayLine.popSample(0);
		float wetR = delayLine.popSample(1);

        channelDataL[sample] = (dryL + wetL) * params.gain;
		channelDataR[sample] = (dryR +wetR) * params.gain;
    }     
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


