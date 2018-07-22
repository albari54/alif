#!/bin/sh

# ========================
# (C)2018 Hassan DRAGA
# mUpdate
# Linux 64
# www.aliflang.org
# License : wxWindows Library Licence, Version 3.1
# ========================

rm -f "bin/linux_mupdate"
rm -f "linux_mupdate.o"

# Root
	rm -f "/usr/local/bin/mupdate"

file="/usr/local/bin/mupdate"
if [ -e "$file" ]; then
	echo "Can't remove '/usr/local/bin/mupdate', need Root... "
	echo 
	exit
fi

echo 
echo "----------------------------"
echo " mUpdate - Linux 64 " 
echo "----------------------------"
echo 

cmd=" -O2 "
arg=$1
if [ "$arg" = "debug" ]; then
	echo "*** Debuging Mode ***"
	echo 
	cmd=" -Og -g "
fi

echo "Compiling... "
echo 

g++ -c -o "linux_mupdate.o" -Wno-undef -Wno-unused-parameter -D__WXGTK__ -Wno-ctor-dtor-privacy -Woverloaded-virtual  -D_FILE_OFFSET_BITS=64 -DwxDEBUG_LEVEL=0 -I"/usr/local/lib/aliflibwx/wx/include/gtk2-unicode-static-3.1-alif" -I"/usr/local/include/aliflibwx" -pthread -m64 -DG_DISABLE_CAST_CHECKS $cmd -m64 -std=c++11 "src/mupdate.cpp"

file="linux_mupdate.o"
if [ ! -e "$file" ]; then
	echo 
	echo "Error. "
	echo 
	exit
fi

echo 
echo "Linking... "
echo 

g++ -o "bin/linux_mupdate" "linux_mupdate.o" -L"/usr/local/lib/aliflibwx" -lwx_baseu_alif_net-3.1 -lwx_gtk2u_alif_propgrid-3.1 -lwx_gtk2u_alif_aui-3.1  -lwx_gtk2u_alif_html-3.1 -lwx_gtk2u_alif_adv-3.1 -lwx_gtk2u_alif_stc-3.1 -lwx_gtk2u_alif_core-3.1 -lwx_baseu_alif_xml-3.1 -lwx_baseu_alif-3.1  -lwxscintilla_alif-3.1   -lwxtiff_alif-3.1 -lwxjpeg_alif-3.1 -lwxpng_alif-3.1  -lgtk-x11-2.0 -lgdk-x11-2.0 -lpangocairo-1.0 -latk-1.0 -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lpangoft2-1.0 -lpango-1.0 -lgobject-2.0 -lfontconfig -lfreetype -lgthread-2.0 -lglib-2.0 -lX11 -lXxf86vm -lSM -lgtk-x11-2.0 -lgdk-x11-2.0 -lpangocairo-1.0 -latk-1.0 -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lpangoft2-1.0 -lpango-1.0 -lgobject-2.0 -lglib-2.0 -lfontconfig -lfreetype -lwxzlib_alif-3.1 -lwxregexu_alif-3.1 -lwxexpat_alif-3.1 -pthread -m64 -static-libgcc -static-libstdc++ -ldl -lm -ldl -lm $cmd

file="bin/linux_mupdate"
if [ ! -e "$file" ]; then
	echo 
	echo "Error. "
	echo 
	exit
fi

if [ "$arg" = "debug" ]; then

	# Root
		cp "bin/linux_mupdate" "/usr/local/bin/mupdate"
		chmod +x "/usr/local/bin/mupdate"
	chmod +x "bin/linux_mupdate"
	exit

else

	# Root
		cp "bin/linux_mupdate" "/usr/local/bin/mupdate"
		chmod +x "/usr/local/bin/mupdate"
		
	chmod +x "bin/linux_mupdate"
	
	echo 
	echo "Striping... "
	echo 

	# Root
		strip --strip-all --strip-unneeded "/usr/local/bin/mupdate"
	strip --strip-all --strip-unneeded "bin/linux_mupdate"

	echo 
	echo "Done."
	echo 

fi
