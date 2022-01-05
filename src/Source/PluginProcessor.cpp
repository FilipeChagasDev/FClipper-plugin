/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <cmath>

//==============================================================================
FClipperAudioProcessor::FClipperAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{

}

FClipperAudioProcessor::~FClipperAudioProcessor()
{
}

//==============================================================================
const juce::String FClipperAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FClipperAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FClipperAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FClipperAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FClipperAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FClipperAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FClipperAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FClipperAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FClipperAudioProcessor::getProgramName (int index)
{
    return {};
}

void FClipperAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FClipperAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void FClipperAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FClipperAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

float db_to_factor(double db_gain)
{
    return pow(10, db_gain / 20);
}

double hard_clipping_function(double x)
{
    double peak = 0.1;
    double y = x > peak ? peak : x;
    y = y < -peak ? -peak : y;
    return y;
}

double soft_clipping_function(double x)
{
    return tanh(10*x)/10;
}

void FClipperAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
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

    double peak = 0.1;
    double pre_gain = db_to_factor(states.getRawParameterValue("pre-gain")->load());
    double post_gain = db_to_factor(states.getRawParameterValue("post-gain")->load());
    double offset = states.getRawParameterValue("offset")->load();
    bool soft_clipping = states.getRawParameterValue("hard_soft")->load();

    buffer.applyGain(pre_gain);

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            auto s = channelData[i];
            s += offset;
            channelData[i] = soft_clipping ? soft_clipping_function(s) : hard_clipping_function(s);
        }
    }

    buffer.applyGain(post_gain);
}

//==============================================================================
bool FClipperAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FClipperAudioProcessor::createEditor()
{
    return new FClipperAudioProcessorEditor (*this);
    //return new GenericAudioProcessorEditor(*this);
}

//==============================================================================
void FClipperAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    MemoryOutputStream my_stream(destData, true);
    this->states.state.writeToStream(my_stream);
}

void FClipperAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    ValueTree tree = ValueTree::readFromData(data, sizeInBytes);
    
    if(tree.isValid())
    {
        states.replaceState(tree);
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FClipperAudioProcessor();
}

AudioProcessorValueTreeState::ParameterLayout FClipperAudioProcessor::createParameterLayout()
{
    AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add(std::make_unique<AudioParameterFloat>("pre-gain", "pre-gain", -20, 20, 0));
    layout.add(std::make_unique<AudioParameterFloat>("post-gain", "post-gain", -20, 20, 0));
    layout.add(std::make_unique<AudioParameterFloat>("offset", "offset", -0.1, 0.1, 0));
    layout.add(std::make_unique<AudioParameterBool>("hard_soft", "hard_soft", false));
    return layout;
}