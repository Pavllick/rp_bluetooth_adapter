bt-device -r "$(bt-device -l | sed -n 's/.*(\(.*\))$/\1/p' | head -n 1)"
bluetoothctl discoverable on
