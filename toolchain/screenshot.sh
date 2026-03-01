#!/usr/bin/env bash

# Source - https://stackoverflow.com/a/5608081
# Posted by Nick Russler, modified by community. See post 'Timeline' for change history
# Retrieved 2026-01-24, License - CC BY-SA 3.0

expect << EOF
spawn telnet 127.0.0.1 1234
expect -re ".*(qemu)"
send "screendump screendump.png -f png\r"
expect -re ".*(qemu)"
send "^]quit\r"
EOF
