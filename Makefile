# makefile の変数とか
# http://quruli.ivory.ne.jp/document/make_3.79.1/make-jp_9.html#index-_0024_0025

TARGET = a.out

DIST ?= ./bin
ODIR ?= ./obj
SDIR ?= ./src

SRCS := $(shell find $(SDIR) -name *.cpp -or -name *.c)
OBJS := $(SRCS:$(SDIR)/%.cpp=$(ODIR)/%.o)

# file.cpp           C++ ソースファイル
# file.hpp           C++ ヘッダ (プリプロセッサ) ファイル
# file.i             プリプロセス済みの ソースファイル
# file.s             アセンブリ言語ファイル
# file.o             オブジェクトファイル
# a.out              リンクエディット済みの出力

INCLUDE = $(addprefix -I,$(shell find $(SDIR) -type d)) -I/Library/Developer/CommandLineTools/usr/include/c++/v1/ -I/Library/Developer/CommandLineTools/usr/lib/clang/7.0.2/include/
# find /usr/include -name iostream とか
# find /Library -name stdarg.h とかで探す
# -Idir
#  ディレクトリ dir を、インクルードファイルの検索するディレクトリのリスト中に追加します。
# -llibrary
#  名前が library であるライブラリをリンク時に使用します。
#  リンカは、標準のライブラリ用ディレクトリのリスト中から、 実際のファイル名が `liblibrary.a' であるファイルを検索します。リンカはこのファイルを、ファイル 名で直接指定した場合と同様に使用します。
#  検索するディレクトリには、いくつかの標準システムディレクトリと、`-L' によって指定したディレクトリが含まれます。
# -Ldir
#  ディレクトリdir を `-l' による検索が行なわれるディレクトリのリストに加えます。

LD := g++
LDFLAGS ?=
AS ?= as
ASFLAGS ?=
CXX = g++
CXXFLAGS = -std=c++1z -O1 -Wall
# -v
#  コンパイルの各ステージで実行されるコマンドを表示
# -H
#  通常の動作に加えて、使用されたヘッダファイルの名前を表示します。


all : $(DIST)/$(TARGET)

$(DIST)/libsaori.so: $(OBJS)
	if [ ! -d $(DIST) ]; then mkdir $(DIST); fi
	$(CXX)  $(CXXFLAGS) -shared lib/libsaori.cpp -o $@


# linker: object[] -> exe
$(DIST)/$(TARGET): $(OBJS)
	if [ ! -d $(DIST) ]; then mkdir $(DIST); fi
	$(LD) $(LDFLAGS) $(LDLIBS) $^ -o $@
	#em++ -O1        $(^:%.o=%.bc) -o $@.js
	#tree .

# assembler: source -> (object, LLVM BC)
$(ODIR)/%.o: $(SDIR)/%.cpp
	if [ ! -d $(ODIR) ]; then mkdir $(ODIR); fi
	if [ ! -d $(ADIR) ]; then mkdir $(ADIR); fi
	$(CXX)  $(CXXFLAGS) -MMD -MP      $(INCLUDE) -c $< -o $@
	#$(CXX)  $(CXXFLAGS) -S            $(INCLUDE) -c $< -o $@.s
	#em++    $(CXXFLAGS) -MMD -MP      $(INCLUDE) -c $< -o $(@:%.o=%.bc)
	#llvm-dis $(@:%.o=%.bc) -o $(@:%.o=%.bc).ll
	#tree .
# -S で アセンブリ出力
# em++ で bc へコンパイルしないと target が emscripten にならず em++ リンカが落ちる
# clang++ -S -emit-llvm で LLVM IR 出力 してその IR を em++ に食わせてもダメという話

.PHONY: clean
clean:
	$(RM) -rf $(ADIR) $(ODIR) $(DIST)

-include $(DEPS)

# $@ ターゲットファイル
# $< 依存ファイルの先頭
