# マ ク ロ 定 義
CC = cl
CFLAGS = /Tc
OBJS = gcmsub1.obj gcmmain1.obj

# 暗 黙 の ル ー ル
.c.obj:
	$(CC) /c$(CFLAGS)$<

# 依 存 関 係 の 指 定
gcmsub1.obj  gcmmain1.obj : gcm.h

# 明 示 的 ル ー ル
gcm1.exe:$(OBJS)
	$(CC) /Fe$@ $(OBJS)

# 擬 似 タ ー ゲ ッ ト
clear:
	del *.obj
	del *.exe

# EOF


# EOF

# $?, $%, $@, $*, $+, $<, $^
# $? 
# $%
# $@
# $*
# $+
# $<
# $^
