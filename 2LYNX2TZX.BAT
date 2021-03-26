rem lynx2wav -s AIRRAID.TAP AIRRAID.WAV
rem sox AIRRAID.WAV AIRRAID.VOC
rem direct /t 483 AIRRAID.VOC AIRRAID_TAPE5_7KHz.tzx
rem direct /t 564 AIRRAID.VOC AIRRAID_TAPE5_6KHz.tzx
rem direct AIRRAID.VOC AIRRAID_TAPE5_9KHz.tzx

rem forfiles /s /m *.tap /C "cmd /c lynx2wav -t @file @fname.wav
forfiles /s /m *.tap /C "cmd /c 2lynx2wav -f11 -5 @file @fname.wav
forfiles /s /m *.wav /C "cmd /c sox @file @fname.voc
del *.wav
rem forfiles /s /m *.voc /C "cmd /c direct /t 483  @file @fname_TAPE5_7KHz.tzx
forfiles /s /m *.voc /C "cmd /c direct @file @fname_TAPE5_12KKHz.tzx
del *.voc
mkdir LYNXTZX
move *.tzx LYNXTZX
PAUSE