# # This file was derived from the 'Hello World!' example recipe in the
# Yocto Project Development Manual.
#

SUMMARY = "Simple brcm43456 firmware application"
SECTION = "brcm"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://files "

#INHIBIT_PACKAGE_STRIP = "1"
S = "${WORKDIR}/files"
RDEPENDS_${PN} += "gpio_ctrl"
do_compile() {
#	    ${CC} brcm_patchram_plus.c -o brcm_patchram_plus
		make
}


do_install() {
	    install -d ${D}${base_libdir}/firmware/bcm/APM_BCM43456
    	cp -rfv fw_bcm43456c5_ag_apsta.bin ${D}${base_libdir}/firmware/bcm/APM_BCM43456
        cp -rfv fw_bcm43456c5_ag.bin ${D}${base_libdir}/firmware/bcm/APM_BCM43456
    	cp -rfv bcmdhd.hcd ${D}${base_libdir}/firmware/bcm/APM_BCM43456
    	cp -rfv nvram.txt ${D}${base_libdir}/firmware/bcm/APM_BCM43456

	    install -d ${D}${bindir}
	    install -m 0755 brcm_patchram_plus ${D}${bindir}
	    install -m 0755 gpio_ctrl_test ${D}${bindir}

		install -d ${D}${sysconfdir}/init.d/
		install -m 0755 ble_setup.sh ${D}${sysconfdir}/init.d/ble_setup.sh
		install -m 0755 wifi_setup.sh ${D}${sysconfdir}/init.d/wifi_setup.sh
#		update-rc.d -r ${D} bt-wifi-setup.sh start 99 2 3 5 .
}

FILES_${PN} += "${base_libdir}/firmware/bcm/*"
INSANE_SKIP_${PN} = "ldflags"

