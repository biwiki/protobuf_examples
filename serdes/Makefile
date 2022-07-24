SERDES_OUT=${OUTPUT}/serdes
SERDES_SRC=serdes
SERDES_SRV=${SERDES_SRC}/server
SERDES_CLIENT=${SERDES_SRC}/client
SERDES_PY=${SERDES_SRC}/py_client
SERDES_PY_GEN=${SERDES_PY}/message_pb2.py

serdes: ${SERDES_OUT}/server ${SERDES_OUT}/client ${SERDES_PY_GEN}

${SERDES_OUT}/server: ${SERDES_SRV}/main.cpp ${MSG_OBJ} ${SERDES_SRC}/inc/common.h
	@mkdir -p $(dir $@)
	${CXX} ${CXX_FLAGS} -I${SERDES_SRC} ${INC_DIRS} $< ${MSG_OBJ} -lprotobuf -o $@

${SERDES_OUT}/client: ${SERDES_CLIENT}/main.cpp ${MSG_OBJ} ${SERDES_SRC}/inc/common.h
	@mkdir -p $(dir $@)
	${CXX} ${CXX_FLAGS} -I${SERDES_SRC} ${INC_DIRS} $< ${MSG_OBJ} -lprotobuf -o $@

${SERDES_PY_GEN}: ${MSG_PROTO}
	protoc -I=${PB_DIR} --python_out=${SERDES_PY} $<

serdes_clean:
	rm -f ${SERDES_PY_GEN}

.PHONY: serdes serdes_clean
