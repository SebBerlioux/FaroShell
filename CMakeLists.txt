cmake_minimum_required(VERSION 3.9)
project(FaroShell)

set(CMAKE_CXX_STANDARD 11)

add_executable(FaroShell
        src/cmd/cat/cat.c
        src/cmd/cat/cat.h
        src/cmd/cd/cd.c
        src/cmd/cd/cd.h
        src/cmd/chgrp/chgrp.c
        src/cmd/chgrp/chgrp.h
        src/cmd/chmod/chmod.c
        src/cmd/chmod/chmod.h
        src/cmd/cp/cp.c
        src/cmd/cp/cp.h
        src/cmd/du/du.c
        src/cmd/du/du.h
        src/cmd/echo/echo.c
        src/cmd/echo/echo.h
        src/cmd/ls/ls.c
        src/cmd/ls/ls.h
        src/cmd/mkdir/mkdir.c
        src/cmd/mkdir/mkdir.h
        src/cmd/mv/mv.c
        src/cmd/mv/mv.h
        src/cmd/pwd/pwd.c
        src/cmd/rm/rm.c
        src/cmd/rm/rm.h
        src/cmd/su/su.c
        src/cmd/su/su.h
        src/interpreter/lecture.c
        src/interpreter/lecture.h
        src/interpreter/main.c
        src/interpreter/parse.c
        src/interpreter/parse.h
        src/libs/liste.c
        src/libs/liste.h
        .gitignore
        Makefile
        README.md)
