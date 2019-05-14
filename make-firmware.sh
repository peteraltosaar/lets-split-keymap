#!/bin/bash

cp keymap.c ../qmk_firmware/keyboards/lets_split/keymaps/peteraltosaar/
cd ../qmk_firmware
make lets_split/rev2:peteraltosaar
cd -
