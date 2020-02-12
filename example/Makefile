ARCH := $(shell $(CXX) -dumpmachine)

IPC_INC?=../include
ifeq ($(IPC_LIB),)
ifeq ($(DEBUG),y)
IPC_LIB=../$(ARCH)-debug/
else
IPC_LIB=../$(ARCH)-release/
endif
endif

LIBS = -lipc -pthread -ljson-c
LIB_PATHS = -L$(IPC_LIB)

LDFLAGS = $(LIB_PATHS) $(LIBS)
INC = -I$(IPC_INC)

CXXFLAGS += $(SYSROOT_FLAG) $(INC) -fpic -fno-omit-frame-pointer -Wall -Wextra -std=c++14

ifeq ($(DEBUG),y)
DEST = $(ARCH)-debug/
CXXFLAGS += -g -O0
else
CXXFLAGS += -O2
DEST = $(ARCH)-release/
endif

APP_DEST = $(DEST)
OBJ_DEST = $(DEST)/obj/

CPPSRCS += \
	server.cpp \
	client.cpp \

OBJS = $(CPPSRCS:%.cpp=$(OBJ_DEST)%.o)

# all cpp files are a final program target
all: $(CPPSRCS:%.cpp=$(APP_DEST)%)

# magic rule for all .cpp files to be its own program
$(APP_DEST)%: $(OBJ_DEST)%.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# stop it deleting the .o files!
.PRECIOUS: %.cpp %.o

clean:
	rm -rf $(DEST)

-include $(OBJS:.o=.d)

$(OBJ_DEST)%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) -MMD -MP -c $(CXXFLAGS) $< -o $@
