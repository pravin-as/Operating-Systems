#!/usr/bin/python

import sys
import os
import binascii
import struct
 

def read_entry(path, offset, size=8):
#Only updated r to rb to read the file as binary.
  with open(path, 'rb') as f:
    f.seek(offset, 0)
    if(f.read(size) == b''): 
         return "NULL"
    return struct.unpack('Q', f.read(size))[0]

# Read /proc/$PID/pagemap
def get_pagemap_entry(pid, addr):
  maps_path = "/proc/{0}/pagemap".format(pid)
  if not os.path.isfile(maps_path):
    print ("Process {0} doesn't exist.".format(pid))
    return

  page_size = os.sysconf("SC_PAGE_SIZE")
  pagemap_entry_size = 8
  offset  = int((addr / page_size)) * pagemap_entry_size

  return read_entry(maps_path, offset)
  
def get_pfn(entry):
  return entry & 0x7FFFFFFFFFFFFF
  
#Main function
def Virtual_Adress(pid):
  path = "/proc/"+pid+"/maps" 
  with open(path, 'r') as tm:
       for mark in tm: 
          Trie  = mark.split(" ")
          temp = get_pagemap_entry(pid,  int("0x"+ Trie[0].split('-')[0] , base=16)) 
          if temp != "NULL":
              print("Process Virtual Adress: " ,hex(int("0x"+ Trie[0].split('-')[0] , base=16)))
              print("PFN: " , hex(get_pfn(temp)))
          
       
pid =   (input("Enter PID of a Process: "))    
Virtual_Adress(pid)
 
