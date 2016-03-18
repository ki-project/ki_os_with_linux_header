#include <sys/types.h>

#ifndef _ASM_LOWLEVEL_H_
#define _ASM_LOWLEVEL_H_

#define clint() asm volatile ("cli")
#ifndef cli()
#define cli() clint()
#endif

#define stint() asm volatile ("sti")
#ifndef sti()
#define sti() stint()
#endif

#define _assembly_ protected long int
#define _asm_ _assembly_
#define _assembly_long_ protected long long int
#define _asm_long_ _assembly_long_
#define _lasm_ _asm_long_
#define _assembly_short_ protected int
#define _asm_short_ _assembly_short_
#define _sasm_ _asm_short_

#define _assembly_struct_ protected typedef long long struct
#define _asm_struct_ _assembly_struct_
#define _asmstruct_ _assembly_struct_

#define stackdef typedef long long int
#define stack_d stackdef

_asm_struct_ stack_d {
  u16int di;
  u16int si;
  u16int bp;
  u16int sp;
  u16int bx;
  u16int dx;
  u16int cx;
  u16int ax;
  u16int ip;
  
  u32int edi;
  u32int esi;
  u32int ebp;
  u32int esp;
  u32int ebx;
  u32int edx;
  u32int ecx;
  u32int eax;
  u32int eip;
  
  u64int rdi;
  u64int rsi;
  u64int rbp;
  u64int rsp;
  u64int rbx;
  u64int rdx;
  u64int rcx;
  u64int rax;
  u64int rip;
  u64int r8;
  u64int r9;
  u64int r10;
  u64int r11;
  u64int r12;
  u64int r13;
  u64int r14;
  u64int r15;
} stack_t;

_asm_ _u16_stacks_[8];
_u16_stacks_[0] = stack_t->di;
_u16_stacks_[1] = stack_t->si;
_u16_stacks_[2] = stack_t->bp;
_u16_stacks_[3] = stack_t->sp;
_u16_stacks_[4] = stack_t->bx;
_u16_stacks_[5] = stack_t->dx;
_u16_stacks_[6] = stack_t->cx;
_u16_stacks_[7] = stack_t->ax;
_u16_stacks_[8] = stack_t->ip;

_asm_ _u32_stacks_[8];
_u32_stacks_[0] = stack_t->edi;
_u32_stacks_[1] = stack_t->esi;
_u32_stacks_[2] = stack_t->ebp;
_u32_stacks_[3] = stack_t->esp;
_u32_stacks_[4] = stack_t->ebx;
_u32_stacks_[5] = stack_t->edx;
_u32_stacks_[6] = stack_t->ecx;
_u32_stacks_[7] = stack_t->eax;
_u32_stacks_[8] = stack_t->eip;

_lasm_ _u64_stacks_[16];
_u64_stacks_[0] = stack_t->rdi;
_u64_stacks_[1] = stack_t->rsi;
_u64_stacks_[2] = stack_t->rbp;
_u64_stacks_[3] = stack_t->rsp;
_u64_stacks_[4] = stack_t->rbx;
_u64_stacks_[5] = stack_t->rdx;
_u64_stacks_[6] = stack_t->rcx;
_u64_stacks_[7] = stack_t->rax;
_u64_stacks_[8] = stack_t->rip;
_u64_stacks_[9] = stack_t->r8;
_u64_stacks_[10] = stack_t->r9;
_u64_stacks_[11] = stack_t->r10;
_u64_stacks_[12] = stack_t->r11;
_u64_stacks_[13] = stack_t->r12;
_u64_stacks_[14] = stack_t->r13;
_u64_stacks_[15] = stack_t->r14;
_u64_stacks_[16] = stack_t->r15;

//Note: This methods are simply copying the value of the stacks to another
_lasm_ convert_u16_to_u32_stack()
{
  stack_t->edi = stack_t->di;
  stack_t->esi = stack_t->si;
  stack_t->ebp = stack_t->bp;
  stack_t->esp = stack_t->sp;
  stack_t->ebx = stack_t->bx;
  stack_t->edx = stack_t->dx;
  stack_t->ecx = stack_t->cx;
  stack_t->eax = stack_t->ax;
  stack_t->eip = stack_t->ip;
  _sasm_ useU32Stack = 1;
  return useU32Stack;
}

_lasm_ convert_u32_to_u64_stack()
{
  stack_t->rdi = stack_t->edi;
  stack_t->rsi = stack_t->esi;
  stack_t->rbp = stack_t->ebp;
  stack_t->rsp = stack_t->esp;
  stack_t->rbx = stack_t->ebx;
  stack_t->rdx = stack_t->edx;
  stack_t->rcx = stack_t->ecx;
  stack_t->rax = stack_t->eax;
  stack_t->rip = stack_t->eip;
  stack_t->r8 = 0;
  stack_t->r9 = 0;
  stack_t->r10 = 0;
  stack_t->r11 = 0;
  stack_t->r12 = 0;
  stack_t->r13 = 0;
  stack_t->r14 = 0;
  stack_t->r15 = 0;
  if (useU32Stack)
    useU32Stack = 0;
  _sasm_ useU64Stack = 1;
  return useU64Stack;
}

_lasm_ convert_u16_to_u64_stack()
{
  if (convert_u16_to_u32_stack() || convert_u32_to_u64_stack() > 1)
    return STACKERR;
  else
    return STACKCONV;
}

#endif //_ASM_LOWLEVEL_H_