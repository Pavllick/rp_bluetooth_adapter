FILESEXTRAPATHS_append := "${THISDIR}/${PN}:"
SRC_URI += "\
    file://main.conf \
		file://bluetooth.service"


do_install_append() {
    install -d ${D}${sysconfdir}/bluetooth
    install -m 0644 ${WORKDIR}/main.conf ${D}${sysconfdir}/bluetooth/

    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/bluetooth.service ${D}/${systemd_unitdir}/system/
}