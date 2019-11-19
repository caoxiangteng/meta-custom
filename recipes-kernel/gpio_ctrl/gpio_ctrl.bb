DESCRIPTION = "gpio ctrl libs"
SECTION = "libs"
PV = "3"
PR = "r0"
PN = "gpio_ctrl"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = " \
          file://gpio_ctrl.c \
          file://gpio_ctrl.h \
          file://makefile \
          "

S = "${WORKDIR}"
do_compile () {
    make
}

do_install () {
	install -d ${D}/usr/lib
	cp ${WORKDIR}/libgpioctrl.so ${WORKDIR}/libgpioctrl.so.${PR}
    install -m 0755 ${WORKDIR}/libgpioctrl.so ${D}/usr/lib
    install -m 0755 ${WORKDIR}/libgpioctrl.so.${PR} ${D}/usr/lib
	cd ${D}/usr/lib/
#	ln -sf libgpioctrl.so.${PR} libgpioctrl.so
	ln -sf libgpioctrl.so libgpioctrl.so.${PR} 
	install -d ${D}/usr/include
	install -m 0644 ${WORKDIR}/gpio_ctrl.h ${D}/usr/include/
}



FILES_${PN} += "${libdir}/*.so"
FILES_${PN}-dbg += "${libdir}/.debug"
FILES_SOLIBSDEV = ""
INSANE_SKIP_${PN} = "dev-so"
