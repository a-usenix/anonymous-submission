# name of your application
APPLICATION = aha-compress

# If no BOARD is found in the environment, use this default:
BOARD ?= nucleo-l552ze-q

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../..

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 0

TOOLCHAIN = llvm
WERROR = 0 

USEMODULE += log log_color xtimer mpu_prog
CFLAGS += -O2 -DLOG_LEVEL=LOG_ALL

# Add the `--wrap` option for malloc, calloc, realloc, and free
# LDFLAGS += -Wl,--wrap=_malloc_r \
           -Wl,--wrap=_calloc_r \
           -Wl,--wrap=_realloc_r \
           -Wl,--wrap=_free_r

include $(RIOTBASE)/Makefile.include
