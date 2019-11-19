#
# This file was derived from the 'Hello World!' example recipe in the
# Yocto Project Development Manual.
#

SUMMARY = "Simple helloworld application"
SECTION = "examples"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://brcm_patchram_plus.c \
	  file://fw_bcm43456c5_ag_apsta.bin \
	  file://fw_bcm43456c5_ag.bin \
	  file://nvram.txt \
	  file://bcmdhd.hcd \
	  file://gatttool \
	  file://btmgmt \
"

S = "${WORKDIR}"

do_compile() {
	     ${CC} brcm_patchram_plus.c -o brcm_patchram_plus
}

do_install() {

	     install -d ${D}${base_libdir}/firmware/bcm/APM_BCM43456
    	     cp -rfv fw_bcm43456c5_ag_apsta.bin ${D}${base_libdir}/firmware/bcm/APM_BCM43456
             cp -rfv fw_bcm43456c5_ag.bin ${D}${base_libdir}/firmware/bcm/APM_BCM43456
    	     cp -rfv bcmdhd.hcd ${D}${base_libdir}/firmware/bcm/APM_BCM43456
    	     cp -rfv nvram.txt ${D}${base_libdir}/firmware/bcm/APM_BCM43456

	     install -d ${D}${bindir}
	     install -m 0755 brcm_patchram_plus ${D}${bindir}
	     install -m 0755 gatttool ${D}${bindir}
	     install -m 0755 btmgmt ${D}${bindir}
}

FILES_${PN} += "${base_libdir}/firmware/bcm/*"
