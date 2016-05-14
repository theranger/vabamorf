#!/usr/bin/env bash

DIR=$(cd "$(dirname ${0})" && echo ${PWD})
BIN_DIR="${DIR}/../bin"
MRF_DIR="${DIR}/mrf"
YHH_DIR="${DIR}/yhh"
TMP_DIR="${DIR}/tmp"

if [ ! -d ${BIN_DIR} ]; then
	echo "Executables directory $BIN_DIR does not exist"
	exit
fi

if [ ! -d ${MRF_DIR} ]; then
	echo "Morph sources directory $MRF_DIR does not exist"
	exit
fi

if [ ! -d ${YHH_DIR} ]; then
	echo "Disambiguator sources directory $YHH_DIR does not exist"
	exit
fi


if [ -d ${TMP_DIR} ]; then
	rm -rf ${TMP_DIR}
fi

mkdir ${TMP_DIR}
if [ ! -d ${TMP_DIR} ]; then
	echo "Temporary directory $TMP_DIR does not exist"
	exit
fi

source ${DIR}/generate_ok.sh
source ${DIR}/generate_morph.sh
source ${DIR}/generate_disamb.sh

pushd ${TMP_DIR}
generate_ok
generate_morph
generate_disamb

if [ -d ${TMP_DIR} ]; then
	rm -rf ${TMP_DIR}
fi
