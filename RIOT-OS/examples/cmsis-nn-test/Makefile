APPLICATION = cmsis-nn-test

BOARD ?= nucleo-l552ze-q

RIOTBASE ?= $(CURDIR)/../..

DEVELHELP ?= 1

QUIET ?= 1

TOOLCHAIN = llvm
WERROR = 0

USEMODULE += log log_color xtimer
CFLAGS += -v -O2 -DLOG_LEVEL=LOG_ALL

# TODO: Get rid of this flag
CFLAGS += -Wno-cast-align

USEPKG += cmsis-nn

BLOBS += input

include $(RIOTBASE)/Makefile.include
