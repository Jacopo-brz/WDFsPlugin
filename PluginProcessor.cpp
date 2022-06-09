/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WDFsPluginAudioProcessor::WDFsPluginAudioProcessor()
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

WDFsPluginAudioProcessor::~WDFsPluginAudioProcessor()
{
}

//==============================================================================
const juce::String WDFsPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WDFsPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WDFsPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WDFsPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WDFsPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WDFsPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WDFsPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WDFsPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String WDFsPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void WDFsPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void WDFsPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{    

    juce::ignoreUnused (sampleRate, samplesPerBlock);
    //formatManager.registerBasicFormats();
    //testing if juce correctly read and write a .wav file
//-- 1 read from file - juce method
    //juce::File ExpSweepFile("/home/jacopo/Scaricati/ExpSweep.wav");
    //if (! ExpSweepFile.existsAsFile())
    //{
    //    DBG ("File doesn't exist ...");
    //}
    //exp_sweep_buffer = GetAudioBufferFromFile(ExpSweepFile); //juce native method

/*-- 2 salvare il risultato della computazione in un file wav
    AudioFile<double> audioFileOutput;
    audioFileOutput.setSampleRate(sample_rate);
    audioFileOutput.setBitDepth(16);
    audioFileOutput.setAudioBufferSize(1, numSamples);

    for (int i = 0; i < numSamples ; i++)
    {
        //float sample = expPointer[i];
        float sample = read_exp_buffer[i];
        audioFileOutput.samples[0][i] = sample;
    }

    const std::string projectBuildDirectory = "/home/jacopo/Documenti/Università/ProjectCourse/Matlab_Gain/";
    audioFileOutput.save(projectBuildDirectory + "expSweep_pluginX.wav", AudioFileFormat::Wave);
    bool loadedOK = audioFileOutput.load(projectBuildDirectory + "expSweep_pluginX.wav");
    std::cout << "expSweep_pluginX.wav correctly loaded: " << loadedOK << std::endl;
*/
    //Compute S for each stage
    S_in = PrepareInputStage(sample_rate);
    S_g = PrepareGainStage(sample_rate);
    S_ss = PrepareSummingStage(sample_rate);
    S_tc = PrepareToneCTLStage(sample_rate);

}

//juce native - based method found online
juce::AudioBuffer<float> WDFsPluginAudioProcessor::GetAudioBufferFromFile(juce::File file)
{
    auto* reader = formatManager.createReaderFor(file);
    juce::AudioBuffer<float> audioBuffer;
    audioBuffer.setSize(reader->numChannels, reader->lengthInSamples);
    reader->read(&audioBuffer, 0, reader->lengthInSamples, 0, true, true);
    delete reader;
    return audioBuffer;
}

void WDFsPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WDFsPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void WDFsPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    //FORCED MONO INPUT (Guitar pedal :D)
    juce::ignoreUnused(midiMessages);
    //juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = 1; //getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

     int channel = 0;
     auto* channelData = buffer.getWritePointer (channel);
     auto* channelData1 = buffer.getWritePointer (channel+1);

     //const float* read_exp_buffer = exp_sweep_buffer.getReadPointer(0);
     //int numSamples = exp_sweep_buffer.getNumSamples();
     //std::cout << "num samples: " << numSamples << std::endl;

     //vst_output_buffer.setSize(1,numSamples);
     //float* write_on_output = vst_output_buffer.getWritePointer(0);

     //const float* read_vst_out = vst_output_buffer.getReadPointer(0);
 //la funzione vera e propria, che leggerà i samples in input dal buffer exp_sweep
 //e scriverà i samples di output nel buffer vst_output
 //  GainStage(read_exp_buffer, write_on_gain, numSamples, S_g, G_mats);
        //GainStage(buffer.getReadPointer(0), channelData, buffer.getNumSamples(), S_g, G_mats);

     float input_out = 0;
     float gain_out = 0;
     float sum_out = 0;
     float tone_out = 0;

     /*for(int sample = 0; sample<exp_sweep_buffer.getNumSamples(); ++sample)
     {
         const float input_sample = read_exp_buffer[sample];
         input_out = InputStageSample(input_sample, S_in, I_data);
         gain_out = GainStageSample(input_out, S_g, G_data);
         sum_out = SummingStageSample(gain_out, S_ss, S_data);
         tone_out = ToneCTLStageSample(sum_out, S_tc, TC_data);
         write_on_output[sample] = OutputStageSample(tone_out, O_data);

     }*/


       //VST version:
       auto inputBuffer = buffer.getReadPointer(channel);//MONO input
       for(int sample = 0; sample<buffer.getNumSamples(); ++sample)
       {
           const float input_sample = inputBuffer[sample];
           input_out = InputStageSample(input_sample, S_in, I_data);
           gain_out = GainStageSample(input_out, S_g, G_data);
           sum_out = SummingStageSample(gain_out, S_ss, S_data);
           tone_out = ToneCTLStageSample(sum_out, S_tc, TC_data);
           channelData[sample] = OutputStageSample(tone_out, O_data);
           channelData1[sample] = channelData[sample];
       }
    /*
 // salvare il risultato della computazione in un file wav
       AudioFile<double> vstOutFile;
       vstOutFile.setSampleRate(sample_rate);
       vstOutFile.setBitDepth(16);
       vstOutFile.setAudioBufferSize(1, numSamples);

       for (int i = 0; i < numSamples ; i++)
       {
           float sample = read_vst_out[i];
           vstOutFile.samples[0][i] = sample;
       }

       const std::string projectBuildDirectory = "/home/jacopo/Documenti/Università/ProjectCourse/MATLAB GENERALE/INPUTeGAINeSUMMINGeTONE_CONTROLeOUTPUT/";
       vstOutFile.save(projectBuildDirectory + "VSTOutput_pluginProcessor_SxS2.wav", AudioFileFormat::Wave);
       bool isloaded = vstOutFile.load(projectBuildDirectory + "VSTOutput_pluginProcessor_SxS2.wav");
       std::cout << "VSTOutput_pluginProcessor_SxS2.wav correctly loaded: " << isloaded << std::endl;
    */
}

//==============================================================================
bool WDFsPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* WDFsPluginAudioProcessor::createEditor()
{
    return new WDFsPluginAudioProcessorEditor (*this);
}

//==============================================================================
void WDFsPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void WDFsPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WDFsPluginAudioProcessor();
}
