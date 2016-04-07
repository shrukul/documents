DST_DIR = Release

SRC_DIR	= src

INC_DIR = include

ifeq (,$(filter $(DST_DIR),$(notdir $(CURDIR))))

MAKETARGET = $(MAKE) --no-print-directory -C $@ -f $(CURDIR)/Makefile \
		SRCDIR=$(CURDIR)/$(SRC_DIR) INCDIR=$(CURDIR)/$(INC_DIR) \
		$(MAKECMDGOALS)

.PHONY: $(DST_DIR)
$(DST_DIR):
	+@[ -d $@ ] || mkdir -p $@
	+@$(MAKETARGET)

.PHONY: clean
clean:
	rm -rf $(DST_DIR)
else

CC	= g++

DEBUG	= -ggdb

CCFLAGS	= -MD $(INCLUDE) -O -m32

INCLUDE	= -I$(INCDIR)

LIBS	= -lc -lm

VPATH	= $(SRCDIR):$(INCDIR)

TARGET	= aip2p

SRCS	= $(shell find $(SRCDIR) -name *.cpp -printf "%f\n")

OBJS	= $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

%.o : %.cpp
	$(CC) -c $(CCFLAGS) $< -o $@
	cp $*.d $*.dep; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.dep; \
	rm -f $*.d

-include $(OBJS:.o=.dep)

endif
