#!/bin/sh

# ========================
# (C)2018 Hassan DRAGA
# mUpdate
# Mac OS X
# www.aliflang.org
# License : wxWindows Library Licence, Version 3.1
# ========================

rm -f "/Library/Application Support/Aliflang/Alif_Studio/mupdate"
rm -f "mupdate.o"
rm -f "bin/mac_mupdate"

file="/Library/Application Support/Aliflang/Alif_Studio/mupdate"
if [ -e "$file" ]; then
	echo 
	echo "Warning: Cannot remove mUpdate, Need Mac OS Sudo."
	echo 
	exit
fi

echo 
echo "----------------------------"
echo " mUpdate "
echo " macOS - SDK 10.12 - "
echo " CLT 10.11 - Minimum 10.9 "
echo "----------------------------"
echo 

echo "- Compiling... "
echo 

# Note: Clang will set SDK path auto

clang++ -mmacosx-version-min=10.9 -m64 -O2 -std=c++11 -c -o "mupdate.o" -D__WXOSX_COCOA__ -Wall -Wundef -Wunused-parameter -Wno-ctor-dtor-privacy -Woverloaded-virtual -Wno-deprecated-declarations  -D_FILE_OFFSET_BITS=64 -DwxDEBUG_LEVEL=0 -I"/Library/Application Support/Aliflang/Alif_Lib_WX/lib/wx/include/osx_cocoa-unicode-static-3.1-alif" -I"/Library/Application Support/Aliflang/Alif_Lib_WX/include" -fno-common "src/mupdate.cpp"

file="mupdate.o"
if [ ! -e "$file" ]; then
	echo "Error. "
	exit
fi

echo 
echo "- Linking... "
echo 

clang++ -m64 -mmacosx-version-min=10.9 -o "bin/mac_mupdate" "mupdate.o" -L"/Library/Application Support/Aliflang/Alif_Lib_WX/lib" -framework IOKit -framework Carbon -framework Cocoa -framework AudioToolbox -framework System -framework OpenGL -lwx_baseu_alif_net-3.1 -lwx_osx_cocoau_alif_aui-3.1 -lwx_osx_cocoau_alif_propgrid-3.1 -lwx_osx_cocoau_alif_adv-3.1 -lwx_osx_cocoau_alif_stc-3.1  -lwx_osx_cocoau_alif_core-3.1  -lwx_baseu_alif-3.1  -lwxscintilla_alif-3.1   -lwxtiff_alif-3.1 -lwxjpeg_alif-3.1 -lwxpng_alif-3.1  -framework WebKit -lwxzlib_alif-3.1 -lwxregexu_alif-3.1 -lwxexpat_alif-3.1 -framework IOKit -framework Carbon -framework Cocoa -framework AudioToolbox -framework System -framework OpenGL  -framework Security -lpthread -liconv  -framework Security -lpthread -liconv

file="bin/mac_mupdate"
if [ ! -e "$file" ]; then
	echo "Error. "
	exit
fi

echo 
echo "- Strip... "
echo 

strip "bin/mac_mupdate"

echo 
echo "- Copy... "
echo 

cp "bin/mac_mupdate" "/Library/Application Support/Aliflang/Alif_Studio/mupdate"

rm -f "mupdate.o"
