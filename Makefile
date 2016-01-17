LIB=	z80e-core
PREFIX?=/usr/local
LIBDIR?=${PREFIX}/lib
SRCS=	cpu.c \
	registers.c
INCS=	z80e/cpu.h \
	z80e/registers.h
INCSDIR?=${PREFIX}/include/z80e
SHLIB_MAJOR=1
# Start configurables
WITH_THREADS?=YES
# End configurables
.if ${WITH_THREADS} == "YES"
CFLAGS+= -DWITH_THREADS
.endif

beforeinstall :
	${INSTALL} -d -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} ${INCSDIR}

.include <bsd.lib.mk>

