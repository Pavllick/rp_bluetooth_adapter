FILESEXTRAPATHS_append := "${THISDIR}/files:"

SRC_URI += "\
    file://default.pa \
    file://system.pa \
		file://daemon.conf \
		file://client.conf \
		file://pulseaudio.service"

RDEPENDS:pulseaudio-server += "\
    pulseaudio-module-bluetooth-discover \
    pulseaudio-module-bluetooth-policy \
		pulseaudio-module-bluez5-device \
		pulseaudio-module-bluez5-discover \
		pulseaudio-module-loopback"
		
inherit systemd useradd

SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE_${PN} = "pulseaudio.service"

FILES_${PN} = "${systemd_unitdir}/system/pulseaudio.service"

# USERADD_PACKAGES = "pulseaudio-service"
# GROUPMEMS_PARAM_pulseaudio-service = " --add root --group audio"

USERADD_PACKAGES = "${PN}"

GROUPADD_PARAM_${PN} = "pulse"
USERADD_PARAM_${PN} = "-g pulse -G audio pulse"

do_install_append() {
    install -d ${D}${sysconfdir}/pulse/
    install -m 0644 ${WORKDIR}/*.pa ${D}${sysconfdir}/pulse/

		install -m 0644 ${WORKDIR}/*.conf ${D}${sysconfdir}/pulse/

    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/pulseaudio.service ${D}/${systemd_unitdir}/system/
}