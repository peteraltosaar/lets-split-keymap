#/bin/bash

echo "String 1:"
read -s string1

echo "String 2:"
read -s string2

cp keymap.c ../qmk_firmware/keyboards/lets_split/keymaps/peteraltosaar/
cd ../qmk_firmware

sed -i '' 's/STRING1_PLACEHOLDER/'$string1'/g' keyboards/lets_split/keymaps/peteraltosaar/keymap.c
sed -i '' 's/STRING2_PLACEHOLDER/'$string2'/g' keyboards/lets_split/keymaps/peteraltosaar/keymap.c

make lets_split/rev2:peteraltosaar:avrdude
rm keyboards/lets_split/keymaps/peteraltosaar/keymap.c
cd -
