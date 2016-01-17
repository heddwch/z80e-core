#ifndef CPU_H
#define CPU_H

#include <stdbool.h>
#include <stdint.h>
#ifdef WITH_THREADS
#include <pthread.h>
#endif

#include "registers.h"

typedef struct z80cpu z80cpu_t;
typedef struct z80iodevice z80iodevice_t;

struct z80iodevice {
  void *device;
  uint8_t (*read_in)(void *);
  void (*write_out)(void *, uint8_t);
};

struct z80cpu {
  z80iodevice_t devices[0x100];
  z80registers_t registers;
  bool IFF1;
  bool IFF2;
  uint8_t int_mode;
  bool IFF_wait;
  bool halted;
  uint16_t prefix;
  void *memory;
  uint8_t (*read_byte)(void *, uint16_t);
  void (*write_byte)(void *, uint16_t, uint8_t);
#ifdef WITH_THREADS
  pthread_mutex_t bus_lock;
#endif
  bool interrupt;
  uint8_t bus;
};


uint8_t cpu_read_register_byte(z80cpu_t *, registers);
uint16_t cpu_read_register_word(z80cpu_t *, registers);

uint8_t cpu_write_register_byte(z80cpu_t *, registers, uint8_t);
uint16_t cpu_write_register_word(z80cpu_t *, registers, uint16_t);

z80cpu_t* cpu_init();
void cpu_free(z80cpu_t *cpu);
uint8_t cpu_read_byte(z80cpu_t *cpu, uint16_t address);
void cpu_write_byte(z80cpu_t *cpu, uint16_t address, uint8_t value);
uint16_t cpu_read_word(z80cpu_t *cpu, uint16_t address);
void cpu_write_word(z80cpu_t *cpu, uint16_t address, uint16_t value);
int cpu_interrupt(z80cpu_t *cpu, uint8_t bus);
#ifdef WITH_THREADS
int cpu_try_interrupt(z80cpu_t *cpu, uint8_t bus);
#endif
int cpu_execute(z80cpu_t *cpu, int cycles);

#endif
