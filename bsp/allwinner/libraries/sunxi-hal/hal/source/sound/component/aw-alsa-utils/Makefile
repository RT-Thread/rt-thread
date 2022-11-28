asflags-y += -I$(srctree)/ekernel/drivers/hal/source/sound/component/aw-alsa-utils \
             -DCONFIG_BUILTIN_WAV_FILE

obj-$(CONFIG_COMPONENTS_AW_ALSA_UTILS) += aplay.o
obj-$(CONFIG_COMPONENTS_AW_ALSA_UTILS) += arecord.o
obj-$(CONFIG_COMPONENTS_AW_ALSA_UTILS) += aduplex.o
obj-$(CONFIG_COMPONENTS_AW_ALSA_UTILS) += amixer.o
obj-$(CONFIG_COMPONENTS_AW_ALSA_UTILS) += common.o
obj-$(CONFIG_COMPONENTS_AW_ALSA_UTILS) += wav_parser.o
obj-$(CONFIG_COMPONENTS_AW_ALSA_UTILS) += card.o
obj-$(CONFIG_BUILTIN_WAV_FILE) += audio_wav/audio_wav.o
