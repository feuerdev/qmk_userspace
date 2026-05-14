.SILENT:

MAKEFLAGS += --no-print-directory

QMK_USERSPACE := $(patsubst %/,%,$(dir $(shell realpath "$(lastword $(MAKEFILE_LIST))")))
ifeq ($(QMK_USERSPACE),)
    QMK_USERSPACE := $(shell pwd)
endif

HOMEBREW_PREFIX := $(shell brew --prefix 2>/dev/null)
ifneq ($(HOMEBREW_PREFIX),)
    export PATH := $(HOMEBREW_PREFIX)/opt/arm-none-eabi-binutils/bin:$(HOMEBREW_PREFIX)/opt/arm-none-eabi-gcc@8/bin:$(HOMEBREW_PREFIX)/opt/avr-binutils/bin:$(HOMEBREW_PREFIX)/opt/avr-gcc@8/bin:$(PATH)
endif

QMK_FIRMWARE_ROOT = $(shell qmk config -ro user.qmk_home | cut -d= -f2 | sed -e 's@^None$$@@g')
ifeq ($(QMK_FIRMWARE_ROOT),)
    $(error Cannot determine qmk_firmware location. `qmk config -ro user.qmk_home` is not set)
endif

%:
	+$(MAKE) -C $(QMK_FIRMWARE_ROOT) $(MAKECMDGOALS) QMK_USERSPACE=$(QMK_USERSPACE)
