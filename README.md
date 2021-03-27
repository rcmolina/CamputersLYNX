# CamputersLYNX

Patched conversion utility for better loading with TAPE5.

Follow this procedure:

* 2lynx2wav -f11 -5 "Centipede (19xx)(Play It!)_MLOAD.tap" "Centipede (19xx)(Play It!)_MLOAD5_12KHz.wav"
* sox "Centipede (19xx)(Play It!)_MLOAD5_12KHz.wav" "Centipede (19xx)(Play It!)_MLOAD5_12KHz.voc"
* direct "Centipede (19xx)(Play It!)_MLOAD5_12KHz.voc" "Centipede (19xx)(Play It!)_MLOAD5_12KHz.tzx"
* direct /t 554 "Centipede (19xx)(Play It!)_MLOAD5_12KHz.voc" "Centipede (19xx)(Play It!)_MLOAD5_6KHz.tzx"


