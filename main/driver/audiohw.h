/*
 * Klimper: ESP32 I²S Synthesizer Test
 * © 2024 Dennis Schulmeister-Zimolong <dennis@wpvs.de>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 */

#pragma once

#include <freertos/FreeRTOS.h>              // Common FreeRTOS (must come first)
#include <freertos/task.h>                  // TaskHandle_t
#include <stdint.h>                         // int16_t

/**
 * Configuration parameters for audio output.
 */
typedef struct {
    int          sample_rate;               // Sample rate in Hz
    size_t       n_samples;                 // Number of samples per buffer (do determine latency)
    int          i2s_mck_io;                // I²S Master Clock
    int          i2s_bck_io;                // I²S Bit Clock
    int          i2s_lrc_io;                // I²S Left/Right Clock
    int          i2s_dout_io;               // I²S Data Output
    TaskHandle_t dsp_task;                  // DSP Task
} audiohw_config_t;

/**
 * Callback structure passed to the mixing task to inform it about where
 * and how many audio samples to put. A pointer to this structure is passed
 * as "notification value" to the mixing task.
 */
typedef struct {
    size_t   size;                          // Buffer size
    int16_t* data;                          // Transmit buffer
} audiohw_buffer_t;

/**
 * Initialize audio hardware. Initializes the I²S driver and installs an
 * ISR to pull new audio data to be played. The ISR sends a notification
 * to an external DSP task that provides the actual audio data.
 * 
 * @param config Configuration parameters (can be freed afterwards)
 */
void audiohw_init(audiohw_config_t* config);
