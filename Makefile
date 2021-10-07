
#== Project config ==
#Build mode: debug or release
BUILDTARGET	:= release

BUILDDIR	:= build
OBJDIR		:= obj
INCDIR		:= include
SRCDIR		:= src
OUTPRG		:= $(BUILDDIR)/hello.prg
LIBS		:= cx16.lib

#== Target system config ==
TARGET		:= cx16
CFGFILE		:= cx16.cfg

#== Emulator config ==
X16EMU		:= x16emu
EFLAGS		= -run

#== Compiler config ==
#CC65 binary path (with trailing /). Leave blank to find in system path
CCPATH		:= 

#Compiler Binaries
CC			:= $(CCPATH)cl65
AS			:= $(CCPATH)ca65
LD			:= $(CCPATH)ld65

#Compiler flags
FLAGS		= -t $(TARGET) -I $(INCDIR) -I $(SRCDIR) --create-dep $(OBJDIR)/$*.d
CFLAGS		= $(FLAGS) -c -l $@.lst -O
AFLAGS		= $(FLAGS)
LFLAGS		= -C $(CFGFILE) -m $(BUILDDIR)/memory.map

#== Build targets ==
#List of all source files to be compiled/assembled
M_SRC		= $(wildcard $(SRCDIR)/*.c)
M_ASM		= $(wildcard $(SRCDIR)/*.asm)

#List of all object files that will be created
#C source files are compiled + assembled with a _c suffix to allow .asm & .c files to share same names
OBJ_SRC		= $(addprefix $(OBJDIR)/,$(patsubst %.c,%_c.o,$(notdir $(M_SRC))))
OBJ_ASM		= $(addprefix $(OBJDIR)/,$(patsubst %.asm,%.o,$(notdir $(M_ASM))))

#Final list of objects to link
OBJS		= $(OBJ_ASM) $(OBJ_SRC)

#Dependency files created by the compiler
DEPS		= $(OBJS:%.o=%.d)

#== Build goals ==
all: $(BUILDTARGET)

debug: FLAGS += -d
debug: $(OUTPRG)

release: $(OUTPRG)

#Link final PRG file
$(OUTPRG): $(OBJS) | resources $(BUILDDIR)
	$(LD) $(LFLAGS) -o $@ $^ $(LIBS)

#Assemble .asm source files to object code
$(OBJDIR)/%.o: $(SRCDIR)/%.asm | $(OBJDIR)
	$(AS) $(AFLAGS) -o $@ $<

#Compile .c source files to object code
$(OBJDIR)/%_c.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ $<

#Generate binary/object files for assets/resources
resources:

#Load dependency files, if they exist
-include $(DEPS)

#Launch emulator and load the PRG rom. If it doesn't exist, it will be built
run: $(OUTPRG)
	$(X16EMU) $(EFLAGS) -prg $<

#Create directories for output files, if they don't exist
$(BUILDDIR) $(OBJDIR):
	mkdir $@