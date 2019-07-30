@ECHO OFF
C:\MinGW\bin\mingw32-gcc.exe -Wall -Wextra -Werror -g -IC:\MinGW\include -Iincludes -c D:\Work\wolf3d\srcs\main.c -o obj\Debug\srcs\main.o
IF NOT ERRORLEVEL 1 C:\MinGW\bin\mingw32-gcc.exe -Wall -Wextra -Werror -g -IC:\MinGW\include -Iincludes -c D:\Work\wolf3d\srcs\checks.c -o obj\Debug\srcs\checks.o
IF NOT ERRORLEVEL 1 C:\MinGW\bin\mingw32-gcc.exe -Wall -Wextra -Werror -g -IC:\MinGW\include -Iincludes -c D:\Work\wolf3d\srcs\keycode.c -o obj\Debug\srcs\keycode.o
IF NOT ERRORLEVEL 1 C:\MinGW\bin\mingw32-gcc.exe -Wall -Wextra -Werror -g -IC:\MinGW\include -Iincludes -c D:\Work\wolf3d\srcs\math.c -o obj\Debug\srcs\math.o
IF NOT ERRORLEVEL 1 C:\MinGW\bin\mingw32-gcc.exe -Wall -Wextra -Werror -g -IC:\MinGW\include -Iincludes -c D:\Work\wolf3d\srcs\parsing.c -o obj\Debug\srcs\parsing.o
IF NOT ERRORLEVEL 1 C:\MinGW\bin\mingw32-gcc.exe -Wall -Wextra -Werror -g -IC:\MinGW\include -Iincludes -c D:\Work\wolf3d\srcs\raycaster.c -o obj\Debug\srcs\raycaster.o

IF NOT ERRORLEVEL 1 C:\MinGW\bin\mingw32-g++.exe -LC:\MinGW\lib -o bin\Debug\Wolf3d.exe -L obj\Debug\libft obj\Debug\srcs\checks.o obj\Debug\srcs\keycode.o obj\Debug\srcs\main.o obj\Debug\srcs\math.o obj\Debug\srcs\parsing.o obj\Debug\srcs\raycaster.o   -lmingw32 -lSDL2main -lSDL2.dll -luser32 -lgdi32 -lwinmm -ldxguid -lft

IF NOT ERRORLEVEL 1 D:\Work\wolf3d\bin\Debug\Wolf3d.exe D:\Work\wolf3d\test.map
