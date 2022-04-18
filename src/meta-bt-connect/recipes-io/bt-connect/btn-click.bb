DESCRIPTION = "Bluetooth reset connection on button click"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "\
    file://btn_click.sh \
		file://bt-connect.service"

FILES_${PN} += "${systemd_unitdir}/*"

inherit systemd

SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE_${PN} = "bt-connect.service"

do_install() {
    install -d ${D}${bindir}
    install -m 0775 ${WORKDIR}/btn_click.sh ${D}${bindir}/

    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/bt-connect.service ${D}/${systemd_unitdir}/system/
}