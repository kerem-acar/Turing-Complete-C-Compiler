clang test1_result.s -o a.exe
a.exe
echo %errorlevel%

clang test2_result.s -o b.exe
b.exe
echo %errorlevel%

clang test3_result.s -o c.exe
c.exe
echo %errorlevel%