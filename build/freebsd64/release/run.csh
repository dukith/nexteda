#!/bin/csh -f

setenv CURR_DIR ${PWD}
cd ../../../

if (! $?LD_LIBRARY_PATH) then
	setenv LD_LIBRARY_PATH ""
endif

setenv NXE_LIB_PATH ${CURR_DIR}/../../../
setenv LD_LIBRARY_PATH ${NXE_LIB_PATH}/lib/freebsd64/:${LD_LIBRARY_PATH}

${CURR_DIR}/sample.exe ${CURR_DIR}/../../../testdata/nxe/nxe.ini
