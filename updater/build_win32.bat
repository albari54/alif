REM # ========================
REM # (C)2018 Hassan DRAGA
REM # mUpdate
REM # Win32
REM # www.aliflang.org
REM # License : wxWindows Library Licence, Version 3.1
REM # ========================

Set PATH=C:\Alif\bin
Set FOLDER=C:\Alif\

del mupdate.exe
del "C:\Alif\mupdate.exe"

del *.o
del *.res
del *.d

echo off
cls
echo.

	echo ----------------------------
	echo mUpdate
	echo ----------------------------
	echo.

if exist "C:\Alif\mupdate.exe" (
 echo.
 echo Can't remove mUpdate..
) else (

	echo Compiling...
	echo.

	"%FOLDER%\bin\g++" -finput-charset=utf-8 -c -o "mupdate.o" -O2 -mthreads -DHAVE_W32API_H -D__WXMSW__ -DwxDEBUG_LEVEL=0 -DNDEBUG -I. -I "%FOLDER%\include" -W -Wno-deprecated-declarations -DNOPCH -Wno-ctor-dtor-privacy -Os -s -fno-keep-inline-dllexport -std=gnu++11 -m32 -MT"mupdate.o" -MF"mupdate.o.d" -MD -MP "src\mupdate.cpp"

	if not exist "mupdate.o" (
		echo.
		echo Error.
	) else (
	
		echo Resource...
		echo.
	
		"%FOLDER%\bin\windres.exe" -I "%FOLDER%\include" -J rc -O coff -i "wx.rc" -o "wx.res" --define __WXMSW__ --define wxDEBUG_LEVEL=0 --define NDEBUG --define _UNICODE --define NOPCH

		echo Linking...
		echo.
		
		"%FOLDER%\bin\g++" -I "%FOLDER%\include" -Os -static-libgcc -static-libstdc++ -m32 -finput-charset=utf-8 -o "bin\mupdate.exe" "wx.res" "mupdate.o" -mthreads -L"%FOLDER%\lib" -Wl,--subsystem,windows -mwindows -lwxbase31u_alif_lib_net -lwxmsw31u_alif_lib_gl -lopengl32 -lglu32 -lwxmsw31u_alif_lib_aui -lwxmsw31u_alif_lib_propgrid -lwxmsw31u_alif_lib_adv -lwxmsw31u_alif_lib_stc -lwxmsw31u_alif_lib_core  -lwxbase31u_alif_lib -lwxscintilla -lwxtiff -lwxjpeg -lwxpng -lwxzlib -lwxregexu -lwxexpat -lkernel32 -luser32 -lgdi32 -lcomdlg32 -lwinspool -lwinmm -lshell32 -lshlwapi -lcomctl32 -lole32 -loleaut32 -luuid -lrpcrt4 -ladvapi32 -lversion -lwsock32 -lwininet -loleacc -luxtheme

		if not exist "bin\mupdate.exe" (
				echo.
				echo Error.
		) else (
		
			echo Copy...
			echo.

			copy "bin\mupdate.exe" "C:\Alif\mupdate.exe"

			del *.o
			del *.res
			del *.d
		)
	)
)
