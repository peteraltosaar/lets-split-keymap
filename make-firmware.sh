#!/bin/bash

echo "Password:"
read -s password

cp keymap.c ../qmk_firmware/keyboards/lets_split/keymaps/peteraltosaar/
cd ../qmk_firmware
sed -i '' 's/PW_PLACEHOLDER/'$password'/g' keyboards/lets_split/keyamps/peteraltosaar/keymap.c
make lets_split/rev2:peteraltosaar
rm keymap.c
cd -
