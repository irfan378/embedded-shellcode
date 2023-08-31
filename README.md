# embedded-shellcode
Examples of embedded shellcode in .data,.text and .rsrc section
### To run embedded-text and embedded-data simply compile the c++ files.  
### To run embedded-rsrc run 
```
rsrc rsrc.rc
cvtres MACHINE:x64 /OUT:rsrc.o rsrc.res
cl /nologo /0x /w0 /GS~ /DNDEBUG /Tcembed-rsrc.cpp /LINK /OUT:embed-rsrc.exe /SUBSYSTEM:CONSOLE /MACHINE:x64 rsrc.o
```
