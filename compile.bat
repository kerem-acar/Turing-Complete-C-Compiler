clang codegen/compile.c -o a.exe && a.exe 
clang codegen/result.s -o bin/exec.exe -Wl,-subsystem:console,-entry:main1