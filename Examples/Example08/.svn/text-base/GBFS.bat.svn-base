@echo off

SET devkitdir=C:\devkitPro\devkitARM\bin
SET progname=Example08

%devkitdir%\gbfs gbfs.gbfs gbfs_data\*.*

%devkitdir%\padbin 256 %progname%.nds
copy /b %progname%.nds+gbfs.gbfs %progname%_final.nds

%devkitdir%\padbin 256 %progname%.ds.gba
copy /b %progname%.ds.gba+gbfs.gbfs %progname%_final.ds.gba

%devkitdir%\padbin 256 %progname%.sc.nds
copy /b %progname%.sc.nds+gbfs.gbfs %progname%_final.sc.nds

del gbfs.gbfs
