# Analog-DJ-Board
An analog DJ board which has manual equalisation, crossfaders, a mixing pad.

## Hardware Validation

The active two-channel mixer was assembled and validated on a breadboard using TL082 dual JFET-input operational amplifiers.

Each channel uses the following signal path:

`Input → 10 kΩ Volume Control → TL082 Voltage Follower → Variable RC Low-Pass Filter → Active Summing Amplifier`

### Buffer Validation
A TL082 voltage follower was added after each channel volume control to isolate the passive volume stage from the RC filter.

Bench measurements at 1 kHz confirmed:
- approximately unity voltage gain
- no phase inversion
- clean sinusoidal output
- successful stage isolation between the volume control and filter

### Variable Low-Pass Filter
Each channel uses:
- 150 Ω fixed resistor
- 10 kΩ variable resistance
- 0.1 µF capacitor

This provides an approximate cutoff-frequency range of:

- ~10.6 kHz at minimum resistance
- ~157 Hz at maximum resistance

Oscilloscope measurements confirmed that the filter output closely follows the buffered signal at minimum resistance and becomes strongly attenuated at 1 kHz when the resistance is increased.

### Active Summing Amplifier
The two channels are combined using an inverting summing amplifier with:

- 47 kΩ Deck A input resistor
- 47 kΩ Deck B input resistor
- 47 kΩ feedback resistor

For a single active channel, the expected gain is approximately:

`Av = -Rf / Rin = -1`

Bench measurements confirmed approximately unity-magnitude gain with the expected 180° phase inversion at the master output.

### Current Hardware Status
Validated in hardware:
- Deck A voltage follower
- Deck A variable low-pass filter
- Deck B voltage follower
- Deck B variable low-pass filter
- Active two-channel summing amplifier
- Master-output signal integrity and expected phase inversion

The next hardware milestone is integrating and characterizing the crossfader network.


## Hardware Validation and Characterization

The two-channel analog mixer was validated on the breadboard using a function generator, oscilloscope, FFT measurements, and real audio playback through a powered speaker.

The implemented signal chain is:

**Audio Input → Volume Control → TL082 Buffer → Variable RC Low-Pass Filter → Crossfader → Active Summing Amplifier → Master Output**

The active circuitry was powered using ±12 V rails.

---

## Functional Validation

Each block was tested independently before validating the complete system.

| Block | Validation Method | Result |
|---|---|---|
| Deck A Buffer | Compared buffer input and output using a 1 kHz sine wave | Unity gain, clean waveform |
| Deck B Buffer | Compared buffer input and output using a 1 kHz sine wave | Unity gain, clean waveform |
| Deck A LPF | Adjusted variable filter resistance while monitoring output | Expected high-frequency attenuation observed |
| Deck B LPF | Adjusted variable filter resistance while monitoring output | Expected high-frequency attenuation observed |
| Active Summer, Deck A | Applied Deck A only and compared input/output | Equal magnitude with 180° phase inversion |
| Active Summer, Deck B | Applied Deck B only and compared input/output | Equal magnitude with 180° phase inversion |
| Dual-Channel Summing | Applied both channels simultaneously | Channels successfully summed |
| Crossfader | Adjusted channel weights between Deck A and Deck B | Successful channel transition |
| Input Jack | Applied external audio source | Audio successfully entered signal chain |
| Output Jack | Connected MASTER_OUT to powered speaker AUX input | Output successfully transferred |
| Full Mixer | Played real audio through the complete signal chain | Successful end-to-end audio playback |

---

## Frequency Response

Frequency-response measurements were taken from the channel input to `MASTER_OUT` with the variable low-pass filter set to its highest cutoff frequency.

The filter used:

- Minimum series resistance: approximately **150 Ω**
- Variable resistance: **0–10 kΩ**
- Capacitor: **0.1 µF**

The theoretical maximum cutoff frequency is approximately:

\[
f_c = \frac{1}{2\pi RC}
\]

Using \(R = 150\ \Omega\) and \(C = 0.1\ \mu F\):

\[
f_c \approx 10.6\text{ kHz}
\]

### Measured Frequency Response

| Frequency | Deck A Vin (Vpp) | Deck A Vout (Vpp) | Deck A Gain (dB) | Deck B Vin (Vpp) | Deck B Vout (Vpp) | Deck B Gain (dB) |
|---:|---:|---:|---:|---:|---:|---:|
| 20 Hz | 0.140 | 0.140 | 0.00 | 0.140 | 0.140 | 0.00 |
| 50 Hz | 0.330 | 0.330 | 0.00 | 0.330 | 0.320 | -0.27 |
| 100 Hz | 0.600 | 0.600 | 0.00 | 0.600 | 0.600 | 0.00 |
| 200 Hz | 0.970 | 0.970 | 0.00 | 0.970 | 0.960 | -0.09 |
| 500 Hz | 1.020 | 1.010 | -0.09 | 1.020 | 1.010 | -0.09 |
| 1 kHz | 1.020 | 1.010 | -0.09 | 1.020 | 1.010 | -0.09 |
| 2 kHz | 1.020 | 1.000 | -0.17 | 1.020 | 1.000 | -0.17 |
| 5 kHz | 1.020 | 0.930 | -0.80 | 1.020 | 0.930 | -0.80 |
| 10 kHz | 1.020 | 0.790 | -2.22 | 1.020 | 0.780 | -2.33 |
| 15 kHz | 1.020 | 0.640 | -4.05 | 1.020 | 0.640 | -4.05 |
| 20 kHz | 1.020 | 0.530 | -5.69 | 1.020 | 0.530 | -5.69 |

The two channels showed closely matched frequency responses.

The measured attenuation also followed the expected behavior of a first-order low-pass filter, with increasing attenuation above approximately 10 kHz.

During the sweep, the measured function-generator amplitude varied at the lower test frequencies even though the generator setting was intended to remain constant. Gain was therefore calculated using the measured input voltage at every frequency:

\[
A_v = 20\log_{10}\left(\frac{V_{out}}{V_{in}}\right)
\]

This preserves the usefulness of the measured transfer-function data while accounting for the observed instrumentation variation.

---

## Total Harmonic Distortion

THD was estimated using the oscilloscope FFT at a 1 kHz input frequency.

FFT settings included approximately:

- Fundamental frequency: **1 kHz**
- FFT span: **0–10 kHz**
- Frequency resolution: approximately **9.54 Hz/bin**
- Harmonics measured: **2nd through 5th**

THD was calculated using:

\[
THD =
\frac{
\sqrt{V_2^2 + V_3^2 + V_4^2 + V_5^2}
}{
V_1
}
\]

where \(V_1\) is the fundamental and \(V_2\) through \(V_5\) are the measured harmonic amplitudes.

### Deck A FFT

| Component | Frequency | FFT Amplitude |
|---|---:|---:|
| Fundamental | 1 kHz | -9.375 dBV |
| 2nd Harmonic | 2 kHz | -75.625 dBV |
| 3rd Harmonic | 3 kHz | -76.250 dBV |
| 4th Harmonic | 4 kHz | -76.875 dBV |
| 5th Harmonic | 5 kHz | -71.250 dBV |

**Estimated Deck A THD: approximately 0.11%**

### Deck B FFT

| Component | Frequency | FFT Amplitude |
|---|---:|---:|
| Fundamental | 1 kHz | -9.375 dBV |
| 2nd Harmonic | 2 kHz | -76.250 dBV |
| 3rd Harmonic | 3 kHz | -71.250 dBV |
| 4th Harmonic | 4 kHz | -76.250 dBV |
| 5th Harmonic | 5 kHz | -69.375 dBV |

**Estimated Deck B THD: approximately 0.14%**

### THD Summary

| Channel | Estimated THD | Design Target |
|---|---:|---:|
| Deck A | ~0.11% | <1% |
| Deck B | ~0.14% | <1% |

Both channels met the project target of less than 1% THD.

These values should be interpreted as oscilloscope-based FFT estimates rather than precision audio-analyzer measurements because the smaller harmonics were close to the FFT noise floor and showed some variation.

---

## Crossfader Validation

The initial crossfader implementation placed the 10 kΩ potentiometers in series with the 47 kΩ summing-amplifier input resistors.

This configuration could not fully attenuate either channel because the maximum attenuation was approximately:

\[
\frac{47k}{47k + 10k} \approx 0.825
\]

The crossfader was redesigned so each potentiometer operated as a voltage divider:

- One outer terminal connected to the channel filter output
- Opposite outer terminal connected to ground
- Wiper connected to the 47 kΩ summing-amplifier input resistor

This allowed each channel contribution to vary from approximately zero to full scale.

For constant-power behavior, the ideal channel gains are:

\[
g_A = \cos\left(\frac{\pi x}{2}\right)
\]

\[
g_B = \sin\left(\frac{\pi x}{2}\right)
\]

At the midpoint:

\[
g_A = g_B \approx 0.707
\]

Each hardware crossfader potentiometer was manually calibrated so the midpoint channel amplitude was approximately 70.7% of the full-scale value.

Representative midpoint measurements included:

- Single-channel level: approximately **1.03–1.05 Vpp**
- Target midpoint level: approximately **0.73 Vpp**
- Initial measured midpoint: approximately **0.70 Vpp**
- Two coherent 1 kHz signals at midpoint: approximately **1.42 Vpp MASTER_OUT**

For identical coherent tones, the theoretical midpoint output is:

\[
0.707 + 0.707 = 1.414
\]

The measured combined output was close to this expected value.

The current breadboard therefore approximates constant-power midpoint behavior using independently adjusted linear potentiometers. A future revision can replace this with a single dual-gang control or active sine/cosine shaping network for continuous one-knob constant-power operation.

---

## Active Summing Amplifier

The two channels are combined using an inverting summing amplifier.

Each channel enters the summing node through a **47 kΩ input resistor**, with a **47 kΩ feedback resistor**.

The output is:

\[
V_{out}
=
-R_f
\left(
\frac{V_A}{R_A}
+
\frac{V_B}{R_B}
\right)
\]

With:

\[
R_f = R_A = R_B = 47k\Omega
\]

the output becomes:

\[
V_{out}=-(V_A+V_B)
\]

The 180° phase inversion measured at the output is therefore expected.

Using an active summer prevents the two source channels from directly loading each other and provides a predictable low-impedance master output.

---

## Buffer Stage

Each channel uses a TL082 voltage follower between the volume control and the variable RC filter.

The original passive design showed significant filter-cutoff variation because the volume potentiometer introduced a nonzero Thevenin resistance.

For a 10 kΩ volume potentiometer at its midpoint:

\[
R_{TH}
=
5k\Omega \parallel 5k\Omega
=
2.5k\Omega
\]

This resistance interacted with the RC filter and shifted its cutoff frequency.

Adding the voltage follower provided:

- High input impedance
- Low output impedance
- Isolation between the volume control and filter
- More predictable cutoff frequency
- Reduced stage-to-stage loading

This was one of the major design changes discovered during SPICE and hardware validation.

---

## Debugging and Bring-Up

Several hardware issues were identified and resolved during bring-up.

### Power-Rail Verification

Before reinstalling fresh TL082 devices, the breadboard power rails were checked with the supply physically disconnected.

Results:

| Measurement | Result |
|---|---|
| +12 V to GND | Open |
| -12 V to GND | Open |
| +12 V to -12 V | Open |

After reconnecting power:

| TL082 Pin | Measured Voltage |
|---|---:|
| Pin 8, VCC+ | +12 V |
| Pin 4, VCC- | -12 V |
| Pin 1, output | ~0 V at idle |
| Pin 7, output | ~0 V at idle |

An earlier wiring mistake involving the TL082 supply pins likely contributed to damaged devices.

The correct TL082 power connections are:

- **Pin 8 = +12 V**
- **Pin 4 = -12 V**

### Faulty BNC Connection

During testing, the function-generator signal unexpectedly disappeared.

The generator was connected directly to the oscilloscope, which revealed a faulty BNC connection.

Replacing/reseating the cable restored the 1 kHz sine wave.

### Accidental Signal Grounding

Later during characterization, both oscilloscope channels suddenly displayed only noise.

The function generator was verified independently and was operating correctly.

The problem was traced to the signal node accidentally being connected to ground.

Removing the unintended ground connection immediately restored normal operation.

These debugging events reinforced a structured troubleshooting procedure:

1. Verify power rails.
2. Verify the signal source independently.
3. Probe the circuit stage-by-stage.
4. Confirm grounding.
5. Reintroduce circuit blocks individually.
6. Validate the complete signal path only after each stage is known to work.

---

## End-to-End Audio Validation

After individual block validation, an external audio source was connected to the mixer.

The complete signal path was verified node-by-node:

**Audio Source → Input Jack → Volume Control → Buffer → LPF → Crossfader → Active Summer → MASTER_OUT → Output Jack → Powered Speaker AUX IN**

The waveform was successfully observed at each stage.

The powered speaker reproduced the processed audio correctly, confirming successful end-to-end operation of the breadboard prototype.

---

## Current Hardware Results

The breadboard prototype currently demonstrates:

- Two functional audio channels
- Independent volume controls
- Buffered signal paths
- Variable first-order low-pass filtering
- Crossfader control
- Active channel summing
- Successful real-audio playback
- Closely matched channel frequency responses
- Approximately **0.11% estimated THD on Deck A**
- Approximately **0.14% estimated THD on Deck B**
- Successful constant-power midpoint approximation
- Stable operation using TL082 op-amps on ±12 V rails

---

## Remaining Characterization

Additional measurements planned for the prototype include:

- Output noise floor
- Channel-to-channel crosstalk
- Maximum unclipped output amplitude
- Input/output headroom
- Comparison of measured frequency response against LTspice simulation
- Python-based processing and visualization of measured data
- PCB revision based on validated breadboard architecture

---

## Key Engineering Iterations

The project evolved through several hardware and simulation iterations:

1. Initial passive two-channel mixer architecture
2. Passive volume and RC low-pass filtering
3. Discovery of filter loading caused by the volume potentiometer
4. Addition of TL082 voltage-follower buffers
5. Addition of separate buffered channels
6. Active inverting summing amplifier
7. Initial series-resistor crossfader implementation
8. Discovery that the series configuration could not fully mute a channel
9. Crossfader redesign using voltage-divider potentiometers
10. Manual constant-power midpoint calibration
11. Breadboard frequency-response characterization
12. FFT-based THD characterization
13. Full real-audio end-to-end validation

The final breadboard architecture prioritizes modularity, predictable stage interaction, simple analog implementation, and ease of measurement and debugging.


### Output Noise

With both Deck A and Deck B inputs grounded, the mixer output noise was measured at `MASTER_OUT`.

- Output noise: ~20 mVpp
- AC RMS noise: ~2.1 mVrms
- FFT span: 0–10 kHz
- FFT bin size: 95.4 Hz
- Observed spectral floor: approximately -95 to -105 dBV across much of the measured band

The FFT measurement is treated as a bench-level noise characterization rather than a precision audio-noise measurement.

## Final Bench Characterization

### Output Noise

Both channel inputs were grounded at the volume-stage inputs while the mixer remained powered normally.

Measured at `MASTER_OUT`:

- Peak-to-peak output noise: approximately **20 mVpp**
- AC RMS output noise: approximately **2.16 mVrms**
- FFT span: **0–10 kHz**
- FFT bin size: approximately **95.4 Hz/bin**
- Observed spectral floor: approximately **-95 to -105 dBV** across much of the measured band

The FFT result is treated as a bench-level noise estimate rather than a precision audio-analyzer measurement.

### Crosstalk / Channel Isolation

Crosstalk was measured by driving one deck with a 1 kHz sine wave while grounding the opposite deck input and selecting the grounded deck using the crossfader.

The driven signal was measured immediately before the crossfader, while residual leakage was measured at `MASTER_OUT`.

| Direction | Driven Signal | Residual at MASTER_OUT | Measured Isolation |
|---|---:|---:|---:|
| Deck A → Deck B | 1.02 Vpp | 20 mVpp | approximately -34.2 dB |
| Deck B → Deck A | 1.02 Vpp | 20 mVpp | approximately -34.2 dB |

Isolation was calculated using:

`Isolation = 20 log10(Vleak / Vsignal)`

Because the measured residual was approximately equal to the previously measured 20 mVpp output-noise level, the actual channel isolation may be better than -34 dB and was limited by the measurement floor of the bench setup.

### Headroom / Clipping Test

Headroom was evaluated using a 1 kHz sine wave while selecting one deck at a time.

For both Deck A and Deck B:

- Clean generator output: **0.80 Vpp**
- Clean `MASTER_OUT`: approximately **0.80 Vpp**
- No visible mixer clipping was observed at this level
- At approximately **0.90 Vpp generator setting**, the waveform was already visibly clipped at the function-generator output itself

Because the source waveform distorted before a mixer-specific clipping limit could be observed, the mixer headroom exceeded the available clean test-source range.

The correct conclusion from this test is:

**No mixer clipping was observed up to 0.80 Vpp input/output at 1 kHz. Further headroom characterization was limited by the available clean function-generator output.**

### Final Audio Playback Validation

After completing bench characterization, the mixer was reconnected to a real audio source and powered speaker.

The complete signal path was verified:

**Audio Source → Volume → TL082 Buffer → Variable LPF → Crossfader → Active Summer → MASTER_OUT → Powered Speaker AUX IN**

Both channels, volume controls, filters, crossfader, summing stage, and final audio output operated correctly.

Successful end-to-end audio playback was confirmed after completion of all bench measurements.
