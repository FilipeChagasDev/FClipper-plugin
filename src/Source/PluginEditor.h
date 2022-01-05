/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "KnobManLNF.h"
#include <memory>
#include <functional>

//==============================================================================
/**
*/
class FClipperAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FClipperAudioProcessorEditor (FClipperAudioProcessor&);
    ~FClipperAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    ToggleButton hard_soft_switch;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FClipperAudioProcessor& audioProcessor;

private:
    Slider pre_gain_slider {Slider::SliderStyle::RotaryHorizontalVerticalDrag, Slider::TextEntryBoxPosition::TextBoxBelow};
    Slider post_gain_slider {Slider::SliderStyle::RotaryHorizontalVerticalDrag, Slider::TextEntryBoxPosition::TextBoxBelow};
    Slider offset_slider {Slider::SliderStyle::RotaryHorizontalVerticalDrag, Slider::TextEntryBoxPosition::TextBoxBelow};
    
    Label pre_gain_label {"pre-gain", "INPUT (db)"};
    Label post_gain_label {"post-gain", "OUTPUT (db)"};
    Label offset_label {"offset", "OFFSET"};
    Label hard_label {"hard", "HARD"};
    Label soft_label {"soft", "SOFT"};
    Label title_label {"title", "FClipper by Filipe Chagas"};
    Label version_label {"version", "v1.1.1 (Jan-2022)"};

    AudioProcessorValueTreeState::SliderAttachment pre_gain_attch, post_gain_attch, offset_attch;
    AudioProcessorValueTreeState::ButtonAttachment hard_soft_attch;

    //String knob_gray_path {"./knob_gray.png"};
    //String switch_metal_path {"./switch_metal.png"};
    //String background_path {"./background.png"};

    //KnobManSliderLNF gray_knob_slider_lnf {ImageCache::getFromFile(knob_gray_path), 150, 150};
    //KnobManToggleButtonLNF toggle_button_lnf {ImageCache::getFromFile(switch_metal_path), 64, 64, 64, 64};

    KnobManSliderLNF gray_knob_slider_lnf {ImageCache::getFromMemory(BinaryData::knob_gray_png, BinaryData::knob_gray_pngSize), 150, 150};
    KnobManToggleButtonLNF toggle_button_lnf {ImageCache::getFromMemory(BinaryData::switch_metal_png, BinaryData::switch_metal_pngSize), 64, 64, 64, 64};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FClipperAudioProcessorEditor)
};
