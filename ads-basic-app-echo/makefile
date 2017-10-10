################################################################################
#                   Shenzhen Xinguodu Technology Co., LTD.
#                        http://www.xinguodu.com
#
# -----------------Author      :  wushilin   
# -----------------Date        :  2014-06-19 
# -----------------Version     :  1.07
# -----------------Description :  makefine for compiling application project.
################################################################################

# add static libraries here
# eg. : if the library file is "libappdbg.a" of $(LIB_DIR),then -> MYLIBS += $(LIB_DIR)/libappdbg.a
	MYLIBS += 
	
# add dynamic libraries here 
# eg. : if the library file is "libsdk8583.so",then -> MYDLLS += -lsdk8583
	MYDLLS += -L$(LIB_DIR)
	MYDLLS += -L./lib -lsqlite3 -ldatabase

#----------!!!! DO NOT MODIFY ANY OF THE FOLLOWING CONTENTS !!!-------------
TARGET = ./$(trg_name)".so.unsign"							# default is xxx.so.unsign
ifeq ($(trg_format),lib)
	TARGET = ./$(trg_name)".a"								# static is xxx.a
else
	ifeq ($(env_cpl),arm-linux-gcc)
#		ifeq ($(auto_sign),true)
			TARGET = ./$(trg_name)".so.unsign"						# K-PLATFORM
#		endif
	endif
endif

# source files
SRC = $(wildcard ./src/*/*/*.c)
SRC += $(wildcard ./src/*/*.c)
SRC += $(wildcard ./src/*.c)

# OBJS
OBJS = $(patsubst %.c, %.o, $(SRC))

# include the application head files
CFLAGS += -I$(POSDIR)/$(app_dir)/inc
CFLAGS += -I$(POSDIR)/$(app_dir)/inc/private_sdk_inc	#wm20160917

# include the sdk library head files
CFLAGS += -I$(LIB_INC)

# static library
LDFLAGS_STATIC = -Wl,-elf2flt
ifeq ($(is_cpp),true)
	MYLIBS += /usr/local/arm-elf/lib/libstdc++.a
endif

# for app running in debug mode
ifeq ($(trg_mode),debug)
	MYLIBS += $(LIB_DIR)/libappdbg.a
endif


ifeq ($(trg_format),exe)
	MYDLLS += -L$(LIB_DIR) -lsdkload -lsdkextload -lsdk8583
	ifeq ($(env_cpl),arm-buildroot-linux-gnueabi)
		MYDLLS += -L$(LIB_DIR) -lsdktouch -lts -lz
	else
		MYDLLS += -L$(LIB_DIR) -lsdktouch -lts -lHANDWRITE -lz -ldev
	endif
endif

#ifeq ($(trg_format),dll)
#	MYDLLS += -L$(LIB_DIR)
#	MYDLLS += 
#endif

# for C++
ifeq ($(is_cpp),true)
	CFLAGS += -x c++
	MYDLLS += -L $(CROSS_DIR)/lib/ -lstdc++	
endif

# ALL
all: $(TARGET) 
	#for i in  $(dir_y) ;do make -C $$i || exit$? ;done  

$(TARGET) : $(OBJS)
	if [ $(trg_format) == lib ]; then \
		$(AR) -ruv $(TARGET) $(OBJS) ; \
	else \
		$(CC) -s -fPIC -lpthread -Wl,-rpath,/mtd0/dll $(LINTFLAG) -o $@ $(OBJS) -ldl -lm $(MYLIBS) $(MYDLLS) ; \
	fi
		
%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(SRC:.c=.o):    $(POSDIR)/$(app_dir)/inc/*.h

# make clean
clean:
	-rm -f $(TARGET) ./*.unsign ./*.a ./*.so ./*.sign *.elf *.gdb *.o */*.o */*/*.o */*/*/*.o

