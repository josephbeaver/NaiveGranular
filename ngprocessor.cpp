//------------------------------------------------------------------------
// Copyright(c) 2022 Castorid.
//------------------------------------------------------------------------

#include "ngprocessor.h"
#include "ngcids.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"

using namespace Steinberg;

namespace castoridaudio {
//------------------------------------------------------------------------
// NaiveGranularProcessor
//------------------------------------------------------------------------
NaiveGranularProcessor::NaiveGranularProcessor ()
{
	//--- set the wanted controller for our processor
	setControllerClass (kNaiveGranularControllerUID);
}

//------------------------------------------------------------------------
NaiveGranularProcessor::~NaiveGranularProcessor ()
{}

//------------------------------------------------------------------------
tresult PLUGIN_API NaiveGranularProcessor::initialize (FUnknown* context)
{
	// Here the Plug-in will be instanciated
	
	//---always initialize the parent-------
	tresult result = AudioEffect::initialize (context);
	// if everything Ok, continue
	if (result != kResultOk)
	{
		return result;
	}

	//--- create Audio IO ------
	addAudioInput (STR16 ("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
	addAudioOutput (STR16 ("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);

	/* If you don't need an event bus, you can remove the next line */
	addEventInput (STR16 ("Event In"), 1);

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API NaiveGranularProcessor::terminate ()
{
	// Here the Plug-in will be de-instanciated, last possibility to remove some memory!
	
	//---do not forget to call parent ------
	return AudioEffect::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API NaiveGranularProcessor::setActive (TBool state)
{
	//--- called when the Plug-in is enable/disable (On/Off) -----
	return AudioEffect::setActive (state);
}

//------------------------------------------------------------------------
tresult PLUGIN_API NaiveGranularProcessor::process (Vst::ProcessData& data)
{
	//--- First : Read inputs parameter changes-----------

    /*if (data.inputParameterChanges)
    {
        int32 numParamsChanged = data.inputParameterChanges->getParameterCount ();
        for (int32 index = 0; index < numParamsChanged; index++)
        {
            if (auto* paramQueue = data.inputParameterChanges->getParameterData (index))
            {
                Vst::ParamValue value;
                int32 sampleOffset;
                int32 numPoints = paramQueue->getPointCount ();
                switch (paramQueue->getParameterId ())
                {
				}
			}
		}
	}*/
	
	int numSamples = data.numSamples;
	Vst::Sample32* outLeft = data.outputs[0].channelBuffers32[0];
	Vst::Sample32* outRight = data.outputs[0].channelBuffers32[1];

	int wavePosition = 0;
	for (int n = 0; n < numSamples; n++)	// ignoring state maintenance between calls of this method
	{
		wavePosition = n % 100;
		if (wavePosition < 50)
		{
			outLeft[n] = -0.25f + 0.01f * wavePosition;	// set rising values
		}
		else
		{
			outLeft[n] = 0.75f - 0.01f * wavePosition;	// set falling values
		}

		outRight[n] = outLeft[n];	// copy value to other channel
		
	}
	
	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API NaiveGranularProcessor::setupProcessing (Vst::ProcessSetup& newSetup)
{
	//--- called before any processing ----
	return AudioEffect::setupProcessing (newSetup);
}

//------------------------------------------------------------------------
tresult PLUGIN_API NaiveGranularProcessor::canProcessSampleSize (int32 symbolicSampleSize)
{
	// by default kSample32 is supported
	if (symbolicSampleSize == Vst::kSample32)
		return kResultTrue;

	// disable the following comment if your processing support kSample64
	/* if (symbolicSampleSize == Vst::kSample64)
		return kResultTrue; */

	return kResultFalse;
}

//------------------------------------------------------------------------
tresult PLUGIN_API NaiveGranularProcessor::setState (IBStream* state)
{
	// called when we load a preset, the model has to be reloaded
	IBStreamer streamer (state, kLittleEndian);
	
	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API NaiveGranularProcessor::getState (IBStream* state)
{
	// here we need to save the model
	IBStreamer streamer (state, kLittleEndian);

	return kResultOk;
}

//------------------------------------------------------------------------
} // namespace castoridaudio
