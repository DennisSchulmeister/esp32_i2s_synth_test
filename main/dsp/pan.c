/*
 * ESP32 I²S Synthesizer Test / µDSP Library
 * © 2024 Dennis Schulmeister-Zimolong <dennis@wpvs.de>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 */

#include "pan.h"

bool             dsp_pan_initialized = false;
float            dsp_pan_const       = 0.0;
dsp_wavetable_t* dsp_pan_wt_cos      = NULL;
dsp_wavetable_t* dsp_pan_wt_sin      = NULL;

/**
 * Static initialization of the wave tables and calculated constants.
 */
void dsp_pan_init() {
    if (dsp_pan_initialized) return;
    dsp_pan_initialized = true;

    dsp_pan_const = sqrt(2) * 0.5;

    dsp_pan_wt_cos = dsp_wavetable_new(DSP_WAVETABLE_DEFAULT_LENGTH, 1, &dsp_wavetable_cos);
    dsp_pan_wt_sin = dsp_wavetable_new(DSP_WAVETABLE_DEFAULT_LENGTH, 1, &dsp_wavetable_sin);
}