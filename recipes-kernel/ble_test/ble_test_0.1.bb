# # This file was derived from the 'Hello World!' example recipe in the
# Yocto Project Development Manual.
#
DESCRIPTION = "ble test"
SECTION = "ble demo test"
PV = "0"
PR = "1"
PN = "ble_test"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = " file://files/"
S = "${WORKDIR}/files/"

do_compile () {
    cmake .
	make
}

do_install () {
	install -d ${D}${bindir}
	install -m 0755 ble_test ${D}${bindir}
}



FILES_${PN} += "${bindir}"
FILES_${PN}-dbg += "${bindir}/.debug"
