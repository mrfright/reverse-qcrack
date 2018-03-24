#original functions by Ruben Molina
#put together as this script by Eric Faehnrich

import struct
import subprocess
import re
import binascii
from shutil import copyfile

#or any executable you want to dump memory from
ORIG_EXE = "QCRACK.EXE"
TARGET_EXE = "QCRACK01.EXE"

#let's just be safe here since this modifies the executable file
copyfile(ORIG_EXE, TARGET_EXE)

def get_24_bytes(addr, game, challenge, breakpoint):
    with open(TARGET_EXE, "r+b") as f:
        addr = struct.pack("L", addr)
        f.seek(breakpoint - 0x800)
        f.write("\x68" + addr)   # PUSH ADDR
        f.write("\x5F")          # POP EDI
        f.write("\x8B\x07")      # MOV EAX,DWORD PTR DS:[EDI]
        f.write("\x8B\x5F\x04")  # MOV EBX,DWORD PTR DS:[EDI+0x04]
        f.write("\x8B\x4F\x08")  # MOV ECX,DWORD PTR DS:[EDI+0x08]
        f.write("\x8B\x57\x0C")  # MOV EDX,DWORD PTR DS:[EDI+0x0C]
        f.write("\x8B\x77\x10")  # MOV ESI,DWORD PTR DS:[EDI+0x10]
        f.write("\x8B\x7F\x14")  # MOV EDI,DWORD PTR DS:[EDI+0x14]
        f.write("\xCC")          # INT3
    p = subprocess.Popen([TARGET_EXE, "-g", game, challenge],
                         stdout=subprocess.PIPE,
                         stderr=subprocess.PIPE)
    output, errors = p.communicate()
    pattern = "eax=(.*) ebx=(.*) ecx=(.*) edx=(.*) esi=(.*) edi=(.*)\r"
    match = re.findall(pattern, errors).pop()
    result = [struct.pack("L", int(reg, 16)) for reg in match]
    return binascii.hexlify("".join(result))

def get_many_bytes(addr, count, codename, challenge, breakpoint):
    ptr, data = 0, ""
    while ptr < count:
        data += get_24_bytes(addr + ptr, codename, challenge, breakpoint)
        ptr += 24
    return data[:count*2]


def pmem(game, chall, breakpoint, addr, size):
    dump = get_many_bytes(addr, size, game, chall, breakpoint)
    print("[%s] mem points to bytes:\n%s" % (game, dump))
    return dump

#an example to get the doc mem
##bpointused = 0x2c50
##addr = 0x56000
##length = 0x200
##data = pdoc("doom2", "Q58880852966", bpointused, addr, length)

#an example to get the dst mem
##bpointused = 0x2c50
##addr = 0x5b400
##length = 0x200
##data = pdoc("doom2", "Q58880852966", bpointused, addr, length)

#the address I just happen to use to get the final memory block
bpointused = 0x2c61
addr = 0xc49c
length = 508
data = pmem("doom2", "Q58880852966", bpointused, addr, length)
