DESCRIPTION = "Bluetooth reset connection on button click"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "\
  file://CMakeLists.txt \
  file://bt-connect.cpp \
  file://fileutil.h \
  file://fileutil.cpp \
  file://gpio.h \
  file://gpio.cpp"

inherit cmake

S = "${WORKDIR}"