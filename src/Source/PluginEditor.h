/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <memory>

struct MyLookAndFeel : LookAndFeel_V4
{
public:
    MyLookAndFeel()
    {
        setColour(Slider::thumbColourId, Colours::red);
    }
};

//==============================================================================
/**
*/
class NewProjectAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewProjectAudioProcessor& audioProcessor;
    
    Slider pre_gain_slider {Slider::SliderStyle::RotaryHorizontalVerticalDrag, Slider::TextEntryBoxPosition::TextBoxBelow};
    Slider post_gain_slider {Slider::SliderStyle::RotaryHorizontalVerticalDrag, Slider::TextEntryBoxPosition::TextBoxBelow};
    Label pre_gain_label {"pre-gain", "input (db)"};
    Label post_gain_label {"post-gain", "output (db)"};
    Label title_label {"title", "FClipper by Filipe Chagas"};

    AudioProcessorValueTreeState::SliderAttachment pre_gain_attch, post_gain_attch;
    
    MyLookAndFeel my_look_and_feel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
};
