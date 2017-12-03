:: windowsXP script to create backup of tracker+ data, and archive it
:: last edit may 15, 2013 at 15:17.
:: output is good and modifies nothing on remote machines
:: if rerun in the same day, the backup will be updated with the newest copies

:: creates script variables
SET MM=%DATE:~4,2%
SET DD=%DATE:~7,2%
SET YYYY=%DATE:~10,4%
:: %FIND% IS STATIC, sEd LOOKS IN A FILE THAT IS READ-ONLY, SAVES CHANGES TO NEW FILE EACH TIME
SET FIND=12/15/2012
SET REPLACE=%MM%/%DD%/%YYYY%
SET BKDIR=C:\BackupWork
SET BKDIRCO=%BKDIR%\CO0002
SET BKCOFILE=%BKDIR%\COMPANY.INI[BACKUP]
SET REMOTE=\\Rzpc\trk\CO0002
SET DAY=%DATE:~0,3%
SET SERVER=192.168.15.245

:: clearly wrong
SET PASSWORD=%7

:: simple and readable method of making the proper folder name for archives
:: GOTO needs to die in a fire, but it's fast and doesn't change flow control in this case
GOTO CASE_%MM%
:CASE_01
	SET MONTH=January
	GOTO END_MM
:CASE_02
	SET MONTH=February
	GOTO END_MM
:CASE_03
	SET MONTH=March
	GOTO END_MM
:CASE_04
	SET MONTH=April
	GOTO END_MM
:CASE_05
	SET MONTH=May
	GOTO END_MM
:CASE_06
	SET MONTH=June
	GOTO END_MM
:CASE_07
	SET MONTH=July
	GOTO END_MM
:CASE_08
	SET MONTH=August
	GOTO END_MM
:CASE_09
	SET MONTH=September
	GOTO END_MM
:CASE_10
	SET MONTH=October
	GOTO END_MM
:CASE_11
	SET MONTH=November
	GOTO END_MM
:CASE_12
	SET MONTH=December
	GOTO END_MM
:END_MM

GOTO CASE_%DAY%
:CASE_Sun
	SET DAY=Sunday
	GOTO END_DAY
:CASE_Mon
	SET DAY=Monday
	GOTO END_DAY
:CASE_Tue
	SET DAY=Tuesday
	GOTO END_DAY
:CASE_Wed
	SET DAY=Wednesday
	GOTO END_DAY
:CASE_Thu
	SET DAY=Thursday
	GOTO END_DAY
:CASE_Fri
	SET DAY=Friday
	GOTO END_DAY
:CASE_Sat
	SET DAY=Saturday
	GOTO END_DAY
:END_DAY

:: clean, but not remove, directory on local machine
:: so backup isn't susceptible to old data being stored
del /Q %BKDIRCO%

:: sets archival and failure directories, sets backup storage locations
SET ARCHDIR="%USERPROFILE%\Desktop\TRKBackups\%YYYY%\%MONTH%\%DD%_%DAY%"
SET FAILDIR="%USERPROFILE%\Desktop\TRKBackups\%YYYY%\%MONTH%\%DD%_%DAY%_DidNotRun"
SET COFILE=%ARCHDIR%\COMPANY.INI
SET BKZIP=%ARCHDIR%\BACKUP.ZIP

:: copies data over for backing up
xcopy %REMOTE% %BKDIRCO%

:: checks if xcopy completed cleanly, else it stops right here
:: leaves a directory named %DD%_DidNotRun inside of %MONTH% to signifiy that something went wrong
:: cleans directory in the event data wasn't copied properly
:: copies faildir to raspi
:: then finally halts execution
IF NOT %ERRORLEVEL%==0 (
	mkdir %FAILDIR%
	del /Q %BKDIRCO%
	pscp -l backups -pw %PASSWORD% -r -batch %FAILDIR% @%SERVER%:/mnt/TRKBackups/%YYYY%/%MONTH%
	exit
)

:: makes archival directory tree for storage
mkdir %ARCHDIR%

:: stream edit and save COMPANY.INI into ARCHDIR
sed -e "s_%FIND%_%REPLACE%_" < %BKCOFILE% > %COFILE%

:: creates backup ZIP in ARCHDIR
7z a -mx9 -tzip %BKZIP% %BKDIRCO%\*

:: cleans directory before for next backup, copies to raspi, then exits
del /Q %BKDIRCO%
pscp -l backups -pw %PASSWORD% -r -batch %ARCHDIR% @%SERVER%:/mnt/TRKBackups/%YYYY%/%MONTH%
exit
