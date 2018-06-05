#---------------------------------------------------------
#Copyright 2015- Beijing ChagLiaoTianXia Technology Co.Ltd
# static library make
# make file
# created by luojie
#---------------------------------------------------------
#编译版本debug,release,release_log

#工程名
PROJECT     = libthrift_cli

#版本号，以后发布时候修改
include     ./version.h
VERSION     = $(DEFVERSION)

TOP_DIR     = ../../../../..


#release
CXXFLAG     =  -w -O3 -shared -fvisibility=hidden -DTRACE_LOG -D_GLIBCXX_DEPRECATED
OUTNAME     = $(PROJECT).l
LIBS        = 
SOLIB       =

#---------------------------------------------------------
ARCH        = linux
SrcSuf      = c
SrcSuf2     = cpp
ObjSuf      = o
LibSuf      = a
#---------------------------------------------------------
ifeq ($(ARCH),linux)

CXX         = g++
CXXFLAGS    = -w -g -fPIC  -fshort-wchar -D__cplusplus $(CXXFLAG)
LIBPATH     =

#include path
INCLUDEPATH += -I../Src
INCLUDEPATH += -I../../include
INCLUDEPATH += -I/usr/local/include/thrift
INCLUDEPATH += -I$(TOP_DIR)/include
INCLUDEPATH += -I$(TOP_DIR)/include/common
INCLUDEPATH += -I$(TOP_DIR)/include/rpc


LD          = ar
LDFLAGS     = rcs
endif

#---------------------------------------------------------
OBJFILES    = ../Src/client.$(ObjSuf)\
            ../Src/rpc/ProtoRpcService.$(ObjSuf)\
            ../Src/rpc/ProtoService_constants.$(ObjSuf)\
            ../Src/rpc/ProtoService_types.$(ObjSuf)\

#---------------------------------------------------------
.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(LibSuf) .$(SrcSuf2)

all:  $(PROJECT) install

$(PROJECT):   $(OBJFILES)
	@echo "Linking $(OUTNAME).$(LibSuf) start..."
	$(LD) $(LDFLAGS) $(OUTNAME).$(LibSuf) $(OBJFILES)
	@echo "Linking $(OUTNAME.$(LibSuf)) end"

install:
    ifeq ($(COMP_VER),debug)
		@echo "copying $(OUTNAME).$(LibSuf) to  ../../lib/"
		@cp $(OUTNAME).$(LibSuf) ../../lib/
		@echo "all process completed."
    endif

    ifeq ($(COMP_VER),release)
		@echo "copying $(OUTNAME).$(LibSuf) to  ../../lib/"
		@cp $(OUTNAME).$(LibSuf) ../../lib/
		@echo "all process completed."
    endif

    ifeq ($(COMP_VER),release_log)
		@echo "copying $(OUTNAME).$(LibSuf) to ../../lib/"
		@cp $(OUTNAME).$(LibSuf) ../../lib/
		@echo "all process completed."
    endif

clean:
	@echo "Cleaning $(PROJECT) project files"
	@rm -f $(OBJFILES) core
	@rm -f ./*.a

#---------------------------------------------------------
.$(SrcSuf).$(ObjSuf):
	@echo "Compiling $(PROJECT) $<"
	$(CXX) -c $(CXXFLAGS) $(INCLUDEPATH) $(LIBPATH) $< -o $@

#---------------------------------------------------------
.$(SrcSuf2).$(ObjSuf):
	@echo "Compiling $(PROJECT) $<"
	$(CXX) -c $(CXXFLAGS) $(INCLUDEPATH) $(LIBPATH) $< -o $@

