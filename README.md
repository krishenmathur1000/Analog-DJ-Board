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
