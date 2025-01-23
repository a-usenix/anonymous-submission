APPLICATION = double-free

BOARD ?= nucleo-l552ze-q

RIOTBASE ?= $(CURDIR)/../../..

DEVELHELP ?= 1

QUIET ?= 1

TOOLCHAIN = llvm
WERROR = 0

USEMODULE += log log_color xtimer mpu_prog
CFLAGS += -v -O0 -DLOG_LEVEL=LOG_ALL
CFLAGS += -DELK_SECURITY
#CFLAGS += -Xanalyzer -analyzer-disable-checker
#CFLAGS += -mllvm -disable-dce

include $(RIOTBASE)/Makefile.include
