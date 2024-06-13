/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USB_MIDI_H
#define USB_MIDI_H

/* bDescriptorSubType */
#define MIDI_VC_HEADER_DESCRIPTOR_SUBTYPE     0x01U
#define MIDI_MS_HEADER_DESCRIPTOR_SUBTYPE     0x01U
#define MIDI_MS_GENERAL_DESCRIPTOR_SUBTYPE    0x01U
#define MIDI_MIDI_IN_JACK_DESCRIPTOR_SUBTYPE  0x02U
#define MIDI_MIDI_OUT_JACK_DESCRIPTOR_SUBTYPE 0x03U

/* bJackType */
#define MIDI_JACK_TYPE_EMBEDDED 0x01
#define MIDI_JACK_TYPE_EXTERNAL 0x02

#define MIDI_CHANNEL_OMNI 0
#define MIDI_CHANNEL_OFF  17

#define MIDI_PITCHBEND_MIN -8192
#define MIDI_PITCHBEND_MAX 8191

/*! Enumeration of MIDI code index number */
enum MidiCodeIndexNumber {
    MIDI_CIN_MISC              = 0,
    MIDI_CIN_CABLE_EVENT       = 1,
    MIDI_CIN_SYSCOM_2BYTE      = 2, ///< 2 byte system common message e.g MTC, SongSelect
    MIDI_CIN_SYSCOM_3BYTE      = 3, ///< 3 byte system common message e.g SPP
    MIDI_CIN_SYSEX_START       = 4, ///< SysEx starts or continue
    MIDI_CIN_SYSEX_END_1BYTE   = 5, ///< SysEx ends with 1 data, or 1 byte system common message
    MIDI_CIN_SYSEX_END_2BYTE   = 6, ///< SysEx ends with 2 data
    MIDI_CIN_SYSEX_END_3BYTE   = 7, ///< SysEx ends with 3 data
    MIDI_CIN_NOTE_OFF          = 8,
    MIDI_CIN_NOTE_ON           = 9,
    MIDI_CIN_POLY_KEYPRESS     = 10,
    MIDI_CIN_CONTROL_CHANGE    = 11,
    MIDI_CIN_PROGRAM_CHANGE    = 12,
    MIDI_CIN_CHANNEL_PRESSURE  = 13,
    MIDI_CIN_PITCH_BEND_CHANGE = 14,
    MIDI_CIN_1BYTE_DATA        = 15
};

/*! Enumeration of MIDI types */
enum MidiType {
    InvalidType = 0x00,          ///< For notifying errors
    NoteOff = 0x80,              ///< Note Off
    NoteOn = 0x90,               ///< Note On
    AfterTouchPoly = 0xA0,       ///< Polyphonic AfterTouch
    ControlChange = 0xB0,        ///< Control Change / Channel Mode
    ProgramChange = 0xC0,        ///< Program Change
    AfterTouchChannel = 0xD0,    ///< Channel (monophonic) AfterTouch
    PitchBend = 0xE0,            ///< Pitch Bend
    SystemExclusive = 0xF0,      ///< System Exclusive
    TimeCodeQuarterFrame = 0xF1, ///< System Common - MIDI Time Code Quarter Frame
    SongPosition = 0xF2,         ///< System Common - Song Position Pointer
    SongSelect = 0xF3,           ///< System Common - Song Select
    TuneRequest = 0xF6,          ///< System Common - Tune Request
    Clock = 0xF8,                ///< System Real Time - Timing Clock
    Start = 0xFA,                ///< System Real Time - Start
    Continue = 0xFB,             ///< System Real Time - Continue
    Stop = 0xFC,                 ///< System Real Time - Stop
    ActiveSensing = 0xFE,        ///< System Real Time - Active Sensing
    SystemReset = 0xFF,          ///< System Real Time - System Reset
};

/*! Enumeration of Thru filter modes */
enum MidiFilterMode {
    Off = 0,              ///< Thru disabled (nothing passes through).
    Full = 1,             ///< Fully enabled Thru (every incoming message is sent back).
    SameChannel = 2,      ///< Only the messages on the Input Channel will be sent back.
    DifferentChannel = 3, ///< All the messages but the ones on the Input Channel will be sent back.
};

/*! \brief Enumeration of Control Change command numbers.
 See the detailed controllers numbers & description here:
 http://www.somascape.org/midi/tech/spec.html#ctrlnums
 */
enum MidiControlChangeNumber {
    // High resolution Continuous Controllers MSB (+32 for LSB) ----------------
    BankSelect = 0,
    ModulationWheel = 1,
    BreathController = 2,
    // CC3 undefined
    FootController = 4,
    PortamentoTime = 5,
    DataEntry = 6,
    ChannelVolume = 7,
    Balance = 8,
    // CC9 undefined
    Pan = 10,
    ExpressionController = 11,
    EffectControl1 = 12,
    EffectControl2 = 13,
    // CC14 undefined
    // CC15 undefined
    GeneralPurposeController1 = 16,
    GeneralPurposeController2 = 17,
    GeneralPurposeController3 = 18,
    GeneralPurposeController4 = 19,

    // Switches ----------------------------------------------------------------
    Sustain = 64,
    Portamento = 65,
    Sostenuto = 66,
    SoftPedal = 67,
    Legato = 68,
    Hold = 69,

    // Low resolution continuous controllers -----------------------------------
    SoundController1 = 70,  ///< Synth: Sound Variation   FX: Exciter On/Off
    SoundController2 = 71,  ///< Synth: Harmonic Content  FX: Compressor On/Off
    SoundController3 = 72,  ///< Synth: Release Time      FX: Distortion On/Off
    SoundController4 = 73,  ///< Synth: Attack Time       FX: EQ On/Off
    SoundController5 = 74,  ///< Synth: Brightness        FX: Expander On/Off
    SoundController6 = 75,  ///< Synth: Decay Time        FX: Reverb On/Off
    SoundController7 = 76,  ///< Synth: Vibrato Rate      FX: Delay On/Off
    SoundController8 = 77,  ///< Synth: Vibrato Depth     FX: Pitch Transpose On/Off
    SoundController9 = 78,  ///< Synth: Vibrato Delay     FX: Flange/Chorus On/Off
    SoundController10 = 79, ///< Synth: Undefined         FX: Special Effects On/Off
    GeneralPurposeController5 = 80,
    GeneralPurposeController6 = 81,
    GeneralPurposeController7 = 82,
    GeneralPurposeController8 = 83,
    PortamentoControl = 84,
    // CC85 to CC90 undefined
    Effects1 = 91, ///< Reverb send level
    Effects2 = 92, ///< Tremolo depth
    Effects3 = 93, ///< Chorus send level
    Effects4 = 94, ///< Celeste depth
    Effects5 = 95, ///< Phaser depth

    // Channel Mode messages ---------------------------------------------------
    AllSoundOff = 120,
    ResetAllControllers = 121,
    LocalControl = 122,
    AllNotesOff = 123,
    OmniModeOff = 124,
    OmniModeOn = 125,
    MonoModeOn = 126,
    PolyModeOn = 127
};

struct midi_cs_if_ac_header_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubType;
    uint16_t bcdADC;
    uint16_t wTotalLength;
    uint8_t bInCollection;
    uint8_t baInterfaceNr[];
} __PACKED;

#define MIDI_SIZEOF_AC_HEADER_DESC(n) (8 + n)

struct midi_cs_if_ms_header_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubType;
    uint16_t bcdMSC;
    uint16_t wTotalLength;
} __PACKED;

#define MIDI_SIZEOF_MS_HEADER_DESC (7)

struct midi_cs_if_in_jack_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubType;
    uint8_t bJackType;
    uint8_t bJackId;
    uint8_t iJack;
} __PACKED;

#define MIDI_SIZEOF_IN_JACK_DESC (6)

struct midi_cs_if_out_jack_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubType;
    uint8_t bJackType;
    uint8_t bJackId;
    uint8_t bNrInputPins;
    uint8_t baSourceId;
    uint8_t baSourcePin;
    uint8_t iJack;
} __PACKED;

#define MIDI_SIZEOF_OUT_JACK_DESC (9)

struct midi_cs_ep_ms_general_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubType;
    uint8_t bNumEmbMIDIJack;
    uint8_t baAssocJackID[];
} __PACKED;

#define MIDI_SIZEOF_MS_GENERAL_DESC(n) (4 + n)

// clang-format off
#define MIDI_CS_HEADER_DESCRIPTOR_INIT(wTotalLength)                                              \
    0x07,                                             /* bLength */                               \
    USB_CS_DESCRIPTOR_TYPE_INTERFACE,                 /* bDescriptorType */                       \
    MIDI_MS_HEADER_DESCRIPTOR_SUBTYPE,                /* bDescriptorSubtype */                    \
    WBVAL(0x0100),                                    /* bcdMSC */                                \
    WBVAL(wTotalLength)                               /* wTotalLength */

#define MIDI_IN_JACK_DESCRIPTOR_INIT(bJackType, bJackID) \
    0x06,                                                \
    0x24,                                                \
    MIDI_MIDI_IN_JACK_DESCRIPTOR_SUBTYPE,                \
    bJackType,                                           \
    bJackID,                                             \
    0x00

#define MIDI_OUT_JACK_DESCRIPTOR_INIT(bJackType, bJackID, baSourceID) \
    0x09,                                                             \
    0x24,                                                             \
    MIDI_MIDI_OUT_JACK_DESCRIPTOR_SUBTYPE,                            \
    bJackType,                                                        \
    bJackID,                                                          \
    0x01,                                                             \
    baSourceID,                                                       \
    0x01,                                                             \
    0x00

#define MIDI_JACK_DESCRIPTOR_INIT(bJackFirstID)                                                     \
    MIDI_IN_JACK_DESCRIPTOR_INIT(MIDI_JACK_TYPE_EMBEDDED, bJackFirstID),                            \
    MIDI_IN_JACK_DESCRIPTOR_INIT(MIDI_JACK_TYPE_EXTERNAL, (bJackFirstID + 1)),                      \
    MIDI_OUT_JACK_DESCRIPTOR_INIT(MIDI_JACK_TYPE_EMBEDDED, (bJackFirstID + 2), (bJackFirstID + 1)), \
    MIDI_OUT_JACK_DESCRIPTOR_INIT(MIDI_JACK_TYPE_EXTERNAL, (bJackFirstID + 3), (bJackFirstID))

#define MIDI_SIZEOF_JACK_DESC (6 + 6 + 9 + 9)

// clang-format on

#endif /* USB_MIDI_H */
