SUMMARY = "A script to ping an IP and control LEDs based on the result"
DESCRIPTION = "This recipe installs a Python script that pings a specified IP and controls LEDs on a Raspberry Pi."


LICENSE = "CLOSED"


SRC_URI = "file://ping_led.py"

# Set the destination directory for the script
do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${WORKDIR}/ping_led.py ${D}${bindir}/ping_led.py
}


