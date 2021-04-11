rem 2lynx2wav -f11 -5 -q AIRRAID.TAP AIRRAID.WAV
rem sox AIRRAID.WAV AIRRAID.VOC
rem direct AIRRAID.VOC AIRRAID_TAPE5.tzx
2lynx2wav -5 -q AIRRAID.TAP AIRRAID_tape5_id11.WAV
wav2tzx AIRRAID_tape5_id11.WAV

rem forfiles /m *.tap /C "cmd /c 2lynx2wav -f11 -5 -q @file @fname.wav
rem forfiles /m *.wav /C "cmd /c sox @file @fname.voc
forfiles /m *.tap /C "cmd /c 2lynx2wav -5 -q @file @fname_tape5_id11.wav
forfiles /m *.wav /C "cmd /c wav2tzx @file
del *.wav
rem forfiles /m *.voc /C "cmd /c direct @file @fname_sq_TAPE5.tzx
rem del *.voc
mkdir LYNXTZX
move *.tzx LYNXTZX
PAUSE