FILESEXTRAPATHS_append := "${THISDIR}/network:"
SRC_URI += "file://10-usb0.network"

FILES_${PN} += "{sysconfdir}/systemd/network/*"

do_install_append() {
  install -d ${D}${sysconfdir}/systemd/network/
  install -m 0644 ${WORKDIR}/*.network ${D}${sysconfdir}/systemd/network/
}
