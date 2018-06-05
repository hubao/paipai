#---------------------------------------------------------
#编译版本debug,release,release_log
COMP_VER	= release_log

PROJECT	    = audition_svr

#版本号，以后发布时候修改
include     ./versionno.h
VERSION     = $(DEFVERSION)
LIBEXPORT   = -fvisibility=hidden
LIBFLAG     =

#顶级目录
TOP_DIR     = ../../../..

#release
ifeq ($(COMP_VER),release_log)
CXXFLAG     = -w -O2
.DEFINES    = -DTRACE_LOG -D__DEBUG__ -D__TEST__
OUTNAME		= $(PROJECT).l

#LIBS        += $(TOP_DIR)/import/lib/libthrift_cli.l.a
LIBS        += $(TOP_DIR)/import/lib/libthrift_svr.l.a
#LIBS        += /usr/local/lib/libthrift.a
#LIBS        += $(TOP_DIR)/import/lib/libthrift_rpc.l.a

SOLIB       +=  -levent -lthrift -lthriftnb
endif

#---------------------------------------------------------
ARCH       	= linux
SrcSuf      = c
SrcSuf2		= cpp
ObjSuf      = o
LibSuf      = so
#---------------------------------------------------------

CXX         = g++
CXXFLAGS    = -w -D__cplusplus -pthread -fshort-wchar -fPIC -rdynamic $(CXXFLAG) $(LIBFLAG) $(LIBEXPORT) $(.DEFINES)
LIBPATH		= -L$(TOP_DIR)/import/lib -L/usr/local/lib

#include path
INCLUDEPATH	+= -I$(TOP_DIR)/import/include
INCLUDEPATH	+= -I$(TOP_DIR)/import/include/common
INCLUDEPATH	+= -I$(TOP_DIR)/import/include/rpc
INCLUDEPATH	+= -I$(TOP_DIR)/import/include/export/thrift
INCLUDEPATH	+= -I$(TOP_DIR)/import/include/export/thrift/include
INCLUDEPATH += -I/usr/local/include/thrift/
INCLUDEPATH	+= -I../Src

LD          = g++
LDFLAGS     = -lpthread $(LIBPATH)  $(SOLIB)

#---------------------------------------------------------
OBJFILES	= ../Src/BusinessHandler.$(ObjSuf)\
		../Src/BusinessMain.$(ObjSuf)\

#---------------------------------------------------------
.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(LibSuf) .$(SrcSuf2)

all:  $(PROJECT)

$(PROJECT):   $(OBJFILES)
	@echo "Linking $(OUTNAME) start..."
	$(LD) $(CXXFLAGS) $(OBJFILES) -o $(OUTNAME) $(LIBS) $(LDFLAGS) -ldl
	@mv $(OUTNAME) /data/server/$(PROJECT)
	@echo "Linking $(OUTNAME) end"

clean:
	@echo "Cleaning $(PROJECT) project files"
	@rm -f $(OBJFILES) core
#---------------------------------------------------------
.$(SrcSuf).$(ObjSuf):
	@echo "Compiling $(PROJECT) $<"
	$(CXX) -c $(CXXFLAGS) $(INCLUDEPATH) $(LIBPATH) $< -o $@

#---------------------------------------------------------
.$(SrcSuf2).$(ObjSuf):
	@echo "Compiling $(PROJECT) $<"
	$(CXX) -c $(CXXFLAGS) $(INCLUDEPATH) $(LIBPATH) $< -o $@
