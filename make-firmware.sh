#!/bin/bash

echo "Password:"
read -s password

cp keymap.c ../qmk_firmware/keyboards/lets_split/keymaps/peteraltosaar/
cd ../qmk_firmware
sed -i '' 's/PW_PLACEHOLDER/'$password'/g' keyboards/lets_split/keymaps/peteraltosaar/keymap.c
make lets_split/rev2:peteraltosaar:avrdude
rm keyboards/lets_split/keymaps/peteraltosaar/keymap.c
cd -
