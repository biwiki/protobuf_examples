SERDES_OUT=${OUTPUT}/serdes
SERDES_SRC=serdes
SERDES_SRV=${SERDES_SRC}/server
SERDES_CLIENT=${SERDES_SRC}/client

serdes: ${SERDES_OUT}/server ${SERDES_OUT}/client

${SERDES_OUT}/server: ${SERDES_SRV}/main.cpp ${MSG_OBJ} ${SERDES_SRC}/inc/common.h
	@mkdir -p $(dir $@)
	${CXX} ${CXX_FLAGS} -I${SERDES_SRC} ${INC_DIRS} $< ${MSG_OBJ} -lprotobuf -o $@

${SERDES_OUT}/client: ${SERDES_CLIENT}/main.cpp ${MSG_OBJ} ${SERDES_SRC}/inc/common.h
	@mkdir -p $(dir $@)
	${CXX} ${CXX_FLAGS} -I${SERDES_SRC} ${INC_DIRS} $< ${MSG_OBJ} -lprotobuf -o $@

.PHONY: serdes
