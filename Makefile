PB_DIR=pb
BASIC=basic
OUTPUT=out

MSG_PROTO=${PB_DIR}/message.proto
MSG_CC=$(MSG_PROTO:.proto=.pb.cc)
MSG_OBJ=$(MSG_PROTO:.proto=.ph.o)

INC_DIRS=-I${PB_DIR} 
CXX_FLAGS=-g -std=c++17

all: ${OUTPUT}/basic serdes

include serdes/Makefile

${MSG_CC}: ${PB_DIR}/message.proto
	protoc -I=${PB_DIR} --cpp_out=${PB_DIR} $<

${MSG_OBJ}: ${MSG_CC}
	${CXX} ${CXX_FLAGS} -c ${INC_DIRS} $< -o $@

${OUTPUT}/basic: ${BASIC}/main.cpp ${MSG_OBJ}
	@mkdir -p $(dir $@)
	${CXX} ${CXX_FLAGS} ${INC_DIRS} $^ -lprotobuf -o $@

clean:
	rm -rf ${OUTPUT}
	rm -f ${MSG_CC} ${MSG_CC:.cc=.h} ${MSG_OBJ}

.PHONY: all message_pb clean
