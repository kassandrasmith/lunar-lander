include Makedefs

# ----------------------------------------------------------------------------------------------------
# Filepaths
# ----------------------------------------------------------------------------------------------------
DRIVOBJROOT = ${TWROOT}/driverlib/gcc
UTILSROOT = ${TWROOT}/utils


# ----------------------------------------------------------------------------------------------------
# Project properties
# ----------------------------------------------------------------------------------------------------
FILENAME = lunar-lander
STARTUP_FILE = startup_gcc
LINKER_FILE = ${FILENAME}.ld
EXTERN_FILES = ${UTILSROOT}/uartstdio.c


# ----------------------------------------------------------------------------------------------------
# Definitions
# ----------------------------------------------------------------------------------------------------

# Compiler prefix
ifndef PREFIX
PREFIX = arm-none-eabi
endif

ifndef OUTDIR
OUTDIR = out
endif

# Compiler, linker, etc.
CC = ${PREFIX}-gcc
LD = ${PREFIX}-ld
OBJCOPY = ${PREFIX}-objcopy
OBJDUMP = ${PREFIX}-objdump

# Compiler CPU/FPU options
CPU = -mcpu=cortex-m4
FPU = -mfpu=fpv4-sp-d16 -mfloat-abi=softfp
PART = TM4C123GH6PM

# Compiler flags
CFLAGS=-g                  \
       -c                  \
       -mthumb             \
       ${CPU}              \
       ${FPU}              \
       -ffunction-sections \
       -fdata-sections     \
       -MD                 \
       -std=c99            \
       -Wall               \
       -pedantic           \
       -DPART_${PART}      \
       -Os                 \
       -I${TWROOT}           \
       -DTARGET_IS_BLIZZARD_RB1 \

SILENTCFLAGS=-g                  \
       -c                  \
       -mthumb             \
       ${CPU}              \
       ${FPU}              \
       -ffunction-sections \
       -fdata-sections     \
       -MD                 \
       -std=c99            \
       -DPART_${PART}      \
       -Os                 \
       -I${TWROOT}           \
       -DTARGET_IS_BLIZZARD_RB1 \

# Linker flags
LDFLAGS=--entry ResetISR   \
	--gc-sections      \

# Objectcopy flags
CPFLAGS = -O binary

# Objectdump flags
ODFLAGS = -S

# Lm4flash flags
UPFLAGS = -v

# Libgcc, libc, and libm paths
LIB_GCC_PATH=${shell ${CC} ${CFLAGS} -print-libgcc-file-name}
LIBC_PATH=${shell ${CC} ${CFLAGS} -print-file-name=libc.a}
LIBM_PATH=${shell ${CC} ${CFLAGS} -print-file-name=libm.a}

# Files
SRC = ${wildcard src/*.c} ${EXTERN_FILES}
OBJS = ${SRC:.c=.o}
OBJS_NAMES = $(notdir ${OBJS})


# ----------------------------------------------------------------------------------------------------
# Rules
# ----------------------------------------------------------------------------------------------------
all: ${OBJS} ${FILENAME}.axf ${FILENAME}

silent: CFLAGS=${SILENTCFLAGS}

silent: ${OBJS} ${FILENAME}.axf ${FILENAME}

%.o: %.c ${EXTERN_FILES}
	@echo Compiling ${<}...
	@${CC} ${CFLAGS} ${<} -o ${OUTDIR}/$(notdir ${@})

${FILENAME}.axf: ${OBJS}
	@echo Linking...
	@echo
	@${LD} -T ${LINKER_FILE} ${LDFLAGS} -o ${OUTDIR}/${FILENAME}.axf $(addprefix ${OUTDIR}/, ${OBJS_NAMES}) ${DRIVOBJROOT}/libdriver.a ${LIBM_PATH} ${LIBC_PATH} ${LIB_GCC_PATH}

${FILENAME}: ${FILENAME}.axf
	@echo Copying...
	@${OBJCOPY} ${CPFLAGS} ${OUTDIR}/${FILENAME}.axf ${OUTDIR}/${FILENAME}.bin
	@echo Dumping...
	@${OBJDUMP} ${ODFLAGS} ${OUTDIR}/${FILENAME}.axf > ${OUTDIR}/${FILENAME}.lst

upload: ${FILENAME}
	lm4flash ${UPFLAGS} ${OUTDIR}/${FILENAME}.bin

clean:
	rm -rfv ${OUTDIR}/*.o ${OUTDIR}/*.d ${OUTDIR}/*.axf ${OUTDIR}/*.bin ${OUTDIR}/*.lst
