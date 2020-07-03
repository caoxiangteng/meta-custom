# # This file was derived from the 'Hello World!' example recipe in the
# Yocto Project Development Manual.
#

DESCRIPTION = "gpio ctrl libs"
SECTION = "libs"
PV = "0"
PR = "1"
PN = "gpio_ctrl"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://files"

S = "${WORKDIR}/files"
do_compile () {
	make
}

do_install () {
	install -d ${D}/usr/lib
	cp ${S}/libgpioctrl.so ${S}/libgpioctrl.so.${PR}
    install -m 0755 ${S}/libgpioctrl.so ${D}/usr/lib
    install -m 0755 ${S}/libgpioctrl.so.${PR} ${D}/usr/lib
	cd ${D}/usr/lib/
#	ln -sf libgpioctrl.so.${PR} libgpioctrl.so
	ln -sf libgpioctrl.so libgpioctrl.so.${PR} 
	install -d ${D}/usr/include
	install -m 0644 ${S}/gpio_ctrl.h ${D}/usr/include/
}



FILES_${PN} += "${libdir}/*.so"
FILES_${PN}-dbg += "${libdir}/.debug"
FILES_SOLIBSDEV = ""
INSANE_SKIP_${PN} = "dev-so"
INSANE_SKIP_${PN} = "ldflags"
