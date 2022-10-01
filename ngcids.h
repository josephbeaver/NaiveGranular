//------------------------------------------------------------------------
// Copyright(c) 2022 Castorid.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace castoridaudio {
//------------------------------------------------------------------------
static const Steinberg::FUID kNaiveGranularProcessorUID (0x6F0DEC61, 0xB0ED5430, 0xBEFA10FF, 0xD78A7686);
static const Steinberg::FUID kNaiveGranularControllerUID (0x187B4E98, 0xA56B53E5, 0x8246EBC9, 0x3DCC7AA8);

#define NaiveGranularVST3Category "Instrument"

//------------------------------------------------------------------------
} // namespace castoridaudio
