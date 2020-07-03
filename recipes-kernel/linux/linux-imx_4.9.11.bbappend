FILESEXTRAPATHS_prepend := "${THISDIR}/features:"
SRC_URI_append = " \ 
file://0001-cxt-add-for-kernel.patch \
file://0001-cxt-add-for-fix-ble-can-t-open-and-wifi-open-failed.patch \
file://custom_defconfig \
"
do_copy_defconfig_append () {
	cp ${WORKDIR}/custom_defconfig ${WORKDIR}/defconfig          
    cp ${WORKDIR}/custom_defconfig ${WORKDIR}/build/.config
}
PATCHTOOL = "git"
