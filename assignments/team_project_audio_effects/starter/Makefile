# Team Project：音樂音響效果器
#   make          編譯 fx
#   make test     編譯並執行自動測試
#   make clean    刪除編譯產物
# Windows（MSYS2）上指令是 mingw32-make。

CC     = gcc
CFLAGS = -Wall -Wextra -std=gnu99 -O2 -Iinclude
LDLIBS = -lm

ifeq ($(OS),Windows_NT)
    EXE = .exe
else
    EXE =
endif

# mingw32-make 找不到 sh 時（PowerShell／cmd）SHELL 會是 sh.exe，指令交給 cmd 執行：
# 沒有 rm，執行目前資料夾的程式也不加 ./
ifeq ($(SHELL),sh.exe)
    RM  = del /Q
    RUN =
else
    RM  = rm -f
    RUN = ./
endif

SRC     = $(wildcard src/*.c)
LIB_SRC = $(filter-out src/main.c,$(SRC))
HDR     = $(wildcard include/*.h)

all: fx$(EXE)

# 新增 src/*.c 會自動被編進來，不需要改這裡
fx$(EXE): $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) -o $@ $(LDLIBS)

test_fx$(EXE): tests/test_fx.c $(LIB_SRC) $(HDR)
	$(CC) $(CFLAGS) tests/test_fx.c $(LIB_SRC) -o $@ $(LDLIBS)

test: fx$(EXE) test_fx$(EXE)
	$(RUN)test_fx$(EXE)

clean:
	-$(RM) fx$(EXE) test_fx$(EXE)

.PHONY: all test clean
