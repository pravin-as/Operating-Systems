#!/usr/bin/python

import sys
import os
import binascii
import struct


def read_entry(path, offset, size=8):
  with open(path, 'rb') as f:
    f.seek(offset, 0)
    return struct.unpack('Q', f.read(size))[0]

# Read /proc/$PID/pagemap
def get_pagemap_entry(pid, addr):
  global offset
  maps_path = "/proc/{0}/pagemap".format(pid)
  if not os.path.isfile(maps_path):
    print ("Process {0} doesn't exist.".format(pid))
    return

  page_size = os.sysconf("SC_PAGE_SIZE")
  pagemap_entry_size = 8
  offset  = int(addr / page_size) * pagemap_entry_size

  return read_entry(maps_path, offset)

def get_pfn(entry):
  return entry & 0x7FFFFFFFFFFFFF
  
def is_present(entry):
  return ((entry & (1 << 63)) != 0)
  
def is_file_page(entry):
  return ((entry & (1 << 61)) != 0) 
  
def swap_offset_(entry): 
  return ((entry & 0x7FFFFFFFFFFFF0)>>4) 
  
def swap_type_(entry): 
   return entry & 0XF

def is_exclusive_map(entry): 
    return (True if (entry & 0x80000000000000) else False)
       
def ZERO_(entry): 
   return ((entry & 0xF00000000000000) >> 56)
  
def is_page_swapped(entry):
  return ((entry & (1 << 62 )) != 0)
  
def Page_is_dirty(entry): 
   return ((entry & (1 << 55 )) != 0)  


# Read /proc/kpagecount
def get_pagecount(pfn):
  return read_entry("/proc/kpagecount", pfn * 8)


# Read /proc/kpageflags
def get_page_flags(pfn):
  return read_entry("/proc/kpageflags", pfn * 8)


if __name__ == "__main__":

  pid  = input("Give PID : ")
  addr  = input("Give Virtual Adress : ")
  
  if  addr.startswith("0x"): 
      addr = int( addr , base=16)
  else :
      addr = int("0x"+addr , base=16)
      
  entry = get_pagemap_entry(pid, addr)
  pfn = get_pfn(entry)
  
  if(not is_page_swapped(entry)): 
   	print( "Physical address : "  , str(hex(pfn))+str(hex(offset)).strip('0x'))
  
  
  print( "PFN: {}".format(hex(pfn)))
  print("Offset swap : " , swap_offset_(entry))
  print ("Zero : " , ZERO_(entry))  
  print("swap type : " , swap_type_(entry))
  print("Page is Dirty? : " , Page_is_dirty(entry))
  print ("Exclusivel mapped page :" ,is_exclusive_map(entry))
  print("Swapped? :{}".format(is_page_swapped(entry))) 
  print( "Is Present? : {}".format(is_present(entry)))
  print( "Is file-page: {}".format(is_file_page(entry)))
  print( "Page count: {}".format(get_pagecount(pfn)))
  print( "Page flags: {}".format(hex(get_page_flags(pfn))))
