# Trackpad: try enabling with upstream I2C pins (GP2 SDA, GP3 SCL).
# Motion pin is undef'd in config.h so the digitizer polls instead of
# using an interrupt. If touch produces cursor movement, the I2C wiring
# matches upstream; if not, we will need an I2C probe.
POINTING_DEVICE_ENABLE = yes

MAXTOUCH_DEBUG = no
