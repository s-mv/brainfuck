#include "mem.h"

u16 mem_len = 8;  // length of memory
u8 *memory;       // memory

void InitMem() {
  // at the very beginning, we go with 8 bytes instead of 1 single byte because
  // 7 extra bytes for only 1 used sounds okay; having to expand to 2, then 4,
  // then 8 the very instant you start running the program, not that okay
  memory = (u8 *)malloc(8 * sizeof(u8));
}

// oh no here we are, read end note
void ExpandMem() { ExpandMemTo(mem_len * 2); }

void ExpandMemTo(u16 len) {
  if (mem_len == len) return;
  // note, this will never be true but I'll keep it for safety
  // TODO: reset pointer to old value (though that should never happen)
  if (mem_len >= MEMORY_LIMIT)
    Report("Memory limit reached. Stopping.", NO_CHAR);
  mem_len = len;

  // sizeof(u8) seems redundant but idk I used it
  // does it just shove in the size at compile-time? idk again but likely
  memory = (u8 *)realloc(memory, mem_len * sizeof(u8));

  if (memory == NULL) Report("Error managing memory. Stopping.", NO_CHAR);
}

void DestroyMem() {
  if (memory != NULL) free(memory);
}

u8 Mem(u16 pointer) { return (pointer > mem_len) ? 0 : memory[pointer]; }

void SetMem(u16 pointer, u8 data) {
  // NOTE this condition is always false, I don't know why I've kept it, maybe
  // will remove when I'm done and polishing
  if (pointer > mem_len) ExpandMemTo(pointer * 2);
  memory[pointer] = data;
}

u16 MemLength() { return mem_len; }

// it kills me to write this ExpandMem because of my own slighly insane
// beliefs about optimisation blocking the wonderful sunset of logic from my
// vision, I just dislike thinking of how the compiler at some point will try to
// reallocate 2^10ish bytes of memory but... I took a little break from life and
// gave this some thought: isn't this method worth it? the answer is that it is,
// the overall cost of implementing growing memory is less than having a 30,000
// byte array at the very beginning...