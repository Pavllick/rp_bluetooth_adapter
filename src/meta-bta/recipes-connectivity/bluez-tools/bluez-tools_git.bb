DESCRIPTION = "Bluez Tools"
HOMEPAGE = "http://code.google.com/p/bluez-tools/"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=12f884d2ae1ff87c09e5b7ccc2c4ca7e"

RDEPENDS_${PN} = "bluez5"
DEPENDS = "glib-2.0 dbus-glib readline"

PR = "r0+gitr${SRCPV}"

SRCREV = "f65321736475429316f07ee94ec0deac8e46ec4a"

S = "${WORKDIR}/git"

SRC_URI = "git://github.com/khvzak/bluez-tools.git;protocol=git;branch=master"

inherit systemd autotools pkgconfig

EXTRA_AUTORECONF_append = " -I ${STAGING_DATADIR}/aclocal"