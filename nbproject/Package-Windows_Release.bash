#!/bin/bash -x

#
# Generated - do not edit!
#

# Macros
TOP=`pwd`
PLATFORM=
TMPDIR=build/Windows_Release/${PLATFORM}/tmp-packaging
TMPDIRNAME=tmp-packaging
OUTPUT_PATH=dist/Windows_Release/${PLATFORM}/xsoko
OUTPUT_BASENAME=xsoko
PACKAGE_TOP_DIR=xsoko/

# Functions
function checkReturnCode
{
    rc=$?
    if [ $rc != 0 ]
    then
        exit $rc
    fi
}
function makeDirectory
# $1 directory path
# $2 permission (optional)
{
    mkdir -p "$1"
    checkReturnCode
    if [ "$2" != "" ]
    then
      chmod $2 "$1"
      checkReturnCode
    fi
}
function copyFileToTmpDir
# $1 from-file path
# $2 to-file path
# $3 permission
{
    cp "$1" "$2"
    checkReturnCode
    if [ "$3" != "" ]
    then
        chmod $3 "$2"
        checkReturnCode
    fi
}

# Setup
cd "${TOP}"
mkdir -p dist/Windows_Release/${PLATFORM}/package
rm -rf ${TMPDIR}
mkdir -p ${TMPDIR}

# Copy files and create directories and links
cd "${TOP}"
makeDirectory ${TMPDIR}/xsoko/bin
copyFileToTmpDir "${OUTPUT_PATH}" "${TMPDIR}/${PACKAGE_TOP_DIR}bin/${OUTPUT_BASENAME}" 0755


# Generate tar file
cd "${TOP}"
rm -f dist/Windows_Release/${PLATFORM}/package/xsoko.tar
cd ${TMPDIR}
tar -vcf ../../../../dist/Windows_Release/${PLATFORM}/package/xsoko.tar *
checkReturnCode

# Cleanup
cd "${TOP}"
rm -rf ${TMPDIR}
