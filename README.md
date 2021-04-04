# CamputersLYNX

Patched conversion utility for better loading with TAPE5.

Follow this procedure:

* 2lynx2wav -f11 -5 -s "Centipede (19xx)(Play It!)_MLOAD.tap" "Centipede (19xx)(Play It!)_MLOAD5.wav"
* sox "Centipede (19xx)(Play It!)_MLOAD5.wav" "Centipede (19xx)(Play It!)_MLOAD5.voc"
* direct "Centipede (19xx)(Play It!)_MLOAD5.voc" "Centipede (19xx)(Play It!)_MLOAD5.tzx"
* direct /t 554 "Centipede (19xx)(Play It!)_MLOAD5.voc" "Centipede (19xx)(Play It!)_MLOAD5_slim.tzx"


