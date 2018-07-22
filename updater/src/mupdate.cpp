// ========================
// (C)2018 Hassan DRAGA
// mUpdate
// www.aliflang.org
// License : wxWindows Library Licence, Version 3.1
// ========================

#if  __APPLE__
	#define _WCHAR_H_CPLUSPLUS_98_CONFORMANCE_	// Fix (macOS) : /include/wx/wxcrt.h:576:14: error: call to 'wcsstr' is ambiguous
#endif

#include <string>
#include <stdlib.h>
#include <sstream>		// std::istringstream
#include <fstream>		// read file line by line
#include <memory>

#include <wx/wx.h>
#include <wx/sstream.h>
#include <wx/protocol/http.h> // HTTP
#include <wx/wfstream.h>
#include <wx/filesys.h>
#include <wx/zipstrm.h>			// Zip
#include <wx/utils.h>				// Kill Process
#include <wx/stdpaths.h>			// Get Path
#include <wx/filename.h>			// Path tools
//#include <wx/mimetype.h>	// To run .deb files..

using namespace std;

// ============================

int ID_FRAME_1 = 5000;
int ID_TXT_TITLE = 5001;
int ID_TXT_COMPILER = 5002;
int ID_TXT_LIBRARY = 5003;
int ID_TXT_ALIF_STUDIO = 5004;
int ID_BOUTON_UPDATE = 5005;
int ID_BOUTON_EXIT = 5006;

wxStaticText* OBJ_TXT_TITLE;
wxStaticText* OBJ_TXT_COMPILER;
wxStaticText* OBJ_TXT_LIBRARY;
wxStaticText* OBJ_TXT_ALIF_STUDIO;
wxButton* OBJ_BUTTON_UPDATE;
wxButton* OBJ_BUTTON_EXIT;

int VERSION_INSTALLED_COMPILER = 0;
int VERSION_INSTALLED_LIBRARY = 0;
int VERSION_INSTALLED_ALIFSTUDIO = 0;

string VERSION_S_INSTALLED_COMPILER = "0.0";
string VERSION_S_INSTALLED_LIBRARY = "0.0";
string VERSION_S_INSTALLED_ALIFSTUDIO = "0.0";

int VERSION_LAST_COMPILER = 0;
int VERSION_LAST_LIBRARY = 0;
int VERSION_LAST_ALIFSTUDIO = 0;

string VERSION_S_LAST_COMPILER = "0.0";
string VERSION_S_LAST_LIBRARY = "0.0";
string VERSION_S_LAST_ALIFSTUDIO = "0.0";

string URL_LAST_COMPILER = "";
string URL_LAST_LIBRARY = "";
string URL_LAST_ALIFSTUDIO = "";

bool SEARCH = true;

string TXT_COMPILER_NAME;
string TXT_LIBWX_NAME;
string TXT_IDE_NAME;

string TXT_URL_COMPILER_NAME;
string TXT_URL_LIBWX_NAME;
string TXT_URL_IDE_NAME;

string TMP_PKG_PATH_COMPILER;
string TMP_PKG_PATH_IDE;
string TMP_PKG_PATH_LIBWX;

string ABSOLUTE_PATH;

class FRAME_1 : public wxFrame
{
    public:
        FRAME_1 ();
        virtual ~FRAME_1();

        void BOUTON_UPDATE_CLICK(wxCommandEvent &event);
		void BOUTON_EXIT_CLICK(wxCommandEvent &event);

    private:
		DECLARE_NO_COPY_CLASS(FRAME_1)
        DECLARE_EVENT_TABLE()
};

FRAME_1 *OBJ_FRAME_1;

BEGIN_EVENT_TABLE(FRAME_1, wxFrame)
	EVT_BUTTON(ID_BOUTON_UPDATE, FRAME_1::BOUTON_UPDATE_CLICK)
	EVT_BUTTON(ID_BOUTON_EXIT, FRAME_1::BOUTON_EXIT_CLICK)
END_EVENT_TABLE()

FRAME_1 :: FRAME_1() : 
	wxFrame(NULL, ID_FRAME_1, 
	wxT("تحديث ألف ستوديو"),
	wxPoint(50, 50),
	wxSize(600, 450), 
	wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN) 
{
    wxPanel *P = new wxPanel(this, wxID_ANY);

	OBJ_TXT_TITLE = new wxStaticText (P, ID_TXT_TITLE, wxT("تحديث ألف ستوديو عبر الأنترنت"), 
										wxPoint(2,5), wxSize(565, 32), 
										wxALIGN_CENTRE_HORIZONTAL | wxST_NO_AUTORESIZE);

	OBJ_TXT_COMPILER = new wxStaticText (P, ID_TXT_COMPILER, wxT(" "), 
															  wxPoint(2,50), wxSize(565, 90),
															  wxST_NO_AUTORESIZE | wxALIGN_CENTRE_HORIZONTAL);

	OBJ_TXT_ALIF_STUDIO = new wxStaticText (P, ID_TXT_LIBRARY, wxT("من فظلكم،\n"
															  "تأكدو من اتصالكم بالشبكة، ثم اظغط على زر بحث"), 
															 wxPoint(2,140), wxSize(565, 90),
															 wxST_NO_AUTORESIZE | wxALIGN_CENTRE_HORIZONTAL);

	OBJ_TXT_LIBRARY = new wxStaticText (P, ID_TXT_ALIF_STUDIO, wxT(" "), 
																wxPoint(2,230), wxSize(565, 90),
																wxST_NO_AUTORESIZE | wxALIGN_CENTRE_HORIZONTAL);
	
	OBJ_BUTTON_UPDATE = new wxButton (P, ID_BOUTON_UPDATE, wxT(" بحث عبر الأنترنت "), wxPoint(413,370), wxSize(160, 32));
	OBJ_BUTTON_EXIT = new wxButton (P, ID_BOUTON_EXIT, wxT(" خروج "), wxPoint(12,370), wxSize(160, 32));
	
	#ifdef _WIN32
		OBJ_TXT_TITLE->SetLayoutDirection(wxLayout_RightToLeft);
		OBJ_TXT_COMPILER->SetLayoutDirection(wxLayout_RightToLeft);
		OBJ_TXT_LIBRARY->SetLayoutDirection(wxLayout_RightToLeft);
		OBJ_TXT_ALIF_STUDIO->SetLayoutDirection(wxLayout_RightToLeft);
		OBJ_BUTTON_UPDATE->SetLayoutDirection(wxLayout_RightToLeft);
		OBJ_BUTTON_EXIT->SetLayoutDirection(wxLayout_RightToLeft);
	#endif

	wxFont* FONT_TITLE = new wxFont(12,
	wxFONTFAMILY_MODERN, // wxFONTFAMILY_SWISS
	wxFONTSTYLE_NORMAL, // wxFONTSTYLE_ITALIC
	wxFONTWEIGHT_BOLD, // wxFONTWEIGHT_NORMAL / wxFONTWEIGHT_BOLD
	false, // 
	"Courier New");

	OBJ_TXT_TITLE->SetFont(*FONT_TITLE);

	wxFont* FONT = new wxFont(12,
	wxFONTFAMILY_MODERN, // wxFONTFAMILY_SWISS
	wxFONTSTYLE_NORMAL, // wxFONTSTYLE_ITALIC
	wxFONTWEIGHT_NORMAL, // wxFONTWEIGHT_NORMAL / wxFONTWEIGHT_BOLD
	false, // 
	"Courier New");
	
	OBJ_TXT_COMPILER->SetFont(*FONT);
	OBJ_TXT_LIBRARY->SetFont(*FONT);
	OBJ_TXT_ALIF_STUDIO->SetFont(*FONT);
	
	Centre();

	// -------------------
	// Path
	// -------------------

	#ifdef _WIN32
	
		// Windows

		// C:\Program Files (x86)\Alif Studio
		//									 -->\alif.exe
		//									 -->\bin\gcc.exe
		//									 -->\include\wx\wx.h
		//									 -->\lib\libwxmsw31u_alif_lib_core
		//									 -->\aliflib\msg.aliflib

		wxFileName fname( ::wxStandardPaths::Get().GetExecutablePath() );

		wxString Buffer;
		Buffer = fname.GetPathWithSep();
		ABSOLUTE_PATH = std::string(Buffer.mb_str());	

		TXT_COMPILER_NAME = ABSOLUTE_PATH + "win32_alif_version.inf";
		TXT_LIBWX_NAME = ABSOLUTE_PATH + "win32_aliflibwx_version.inf";
		TXT_IDE_NAME = ABSOLUTE_PATH + "win32_alifstudio_version.inf";

		TXT_URL_COMPILER_NAME = "http://www.aliflang.org/update/win32_alif_version.inf";
		TXT_URL_LIBWX_NAME = "http://www.aliflang.org/update/win32_aliflibwx_version.inf";
		TXT_URL_IDE_NAME = "http://www.aliflang.org/update/win32_alifstudio_version.inf";

		TMP_PKG_PATH_COMPILER = ABSOLUTE_PATH + "alif.zip";
		TMP_PKG_PATH_IDE = ABSOLUTE_PATH + "alifstudio.zip";
		TMP_PKG_PATH_LIBWX = ABSOLUTE_PATH + "aliflibwx.zip";

	#elif  __APPLE__

		// Mac OS X
		
		// alif_1.0-1.pkg
		//		/usr/local/bin/alif
		//		/Library/Application Support/Aliflang/Alif_Compiler/aliflib/aliflib.inf
		//		/Library/Application Support/Aliflang/Alif_Compiler/mac_alif_version.inf
		//		/Library/Application Support/Aliflang/Alif_Compiler/Alif_Arabic_Programming_Language
		//		/Library/Application Support/Aliflang/Alif_Compiler/alif.icns
		//		/Library/Application Support/Aliflang/Alif_Compiler/Info.plist

		// aliflibwx_3.1-1.pkg
		//		/Library/Application Support/Aliflang/Alif_Lib_WX/include/[wx][boost][utf8]
		//		/Library/Application Support/Aliflang/Alif_Lib_WX/lib/[.a]
		//		/Library/Application Support/Aliflang/Alif_Lib_WX/mac_aliflibwx_version.inf
		
		// alifstudio_1.0-1.pkg
		//		/Applications/Alif Studio.app
		//		/Library/Application Support/Aliflang/Alif_Studio/mac_alifstudio_version.inf
		//		/Library/Application Support/Aliflang/Alif_Studio/alifstudio.png
		//		/Library/Application Support/Aliflang/Alif_Studio/mupdate

		wxFileName fname( ::wxStandardPaths::Get().GetExecutablePath() );

		wxString Buffer;
		Buffer = fname.GetPathWithSep();
		ABSOLUTE_PATH = std::string(Buffer.mb_str());

		TXT_COMPILER_NAME = "/Library/Application Support/Aliflang/Alif_Compiler/mac_alif_version.inf";
		TXT_LIBWX_NAME = "/Library/Application Support/Aliflang/Alif_Lib_WX/mac_aliflibwx_version.inf";
		TXT_IDE_NAME = "/Library/Application Support/Aliflang/Alif_Studio/mac_alifstudio_version.inf";

		TXT_URL_COMPILER_NAME = "http://www.aliflang.org/update/mac_alif_version.inf";
		TXT_URL_LIBWX_NAME = "http://www.aliflang.org/update/mac_aliflibwx_version.inf";
		TXT_URL_IDE_NAME = "http://www.aliflang.org/update/mac_alifstudio_version.inf";

		wxFileName tfname(wxFileName::GetTempDir()); // wxStandardPaths::Get().GetTempDir()
		wxString PATH_TEMP = tfname.GetPathWithSep();

		if (PATH_TEMP.length() < 4)
			PATH_TEMP = "/tmp/";
		
		TMP_PKG_PATH_COMPILER = PATH_TEMP + "aliflang.pkg";
		TMP_PKG_PATH_IDE = PATH_TEMP + "alifstudio.pkg";
		TMP_PKG_PATH_LIBWX = PATH_TEMP + "aliflibwx.pkg";

	#else

		// Linux

		// aliflang_1.0-1.deb
		//		/usr/local/bin/alif.bin
		//		/usr/local/lib/aliflib/risalah.aliflib
		//		/usr/local/share/aliflang/copyright
		//		/usr/local/share/aliflang/linux_alif_version.inf
		//		/usr/local/share/aliflang/Alif_Arabic_Programming_Language

		// aliflibwx_3.1-1.deb
		//		/usr/local/include/aliflibwx/[wx][boost][utf8]
		//		/usr/local/lib/aliflibwx/[.a]
		//		/usr/local/share/aliflibwx/linux_aliflibwx_version.inf
		//		/usr/share/doc/aliflibwx/copyright (txt)

		// alifstudio_1.0-1.deb
		//		/usr/local/bin/alifstudio.bin
		//		/usr/local/bin/mupdate.bin
		//		/usr/local/share/alifstudio/copyright
		//		/usr/local/share/alifstudio/linux_alifstudio_version.inf
		//		/usr/share/alifstudio/alifstudio.ico
		//		/usr/share/alifstudio/alifstudio.png
		//		/usr/share/applications/'Alif Studio'

		wxFileName fname( ::wxStandardPaths::Get().GetExecutablePath() );

		wxString Buffer;
		Buffer = fname.GetPathWithSep();
		ABSOLUTE_PATH = std::string(Buffer.mb_str());

		TXT_COMPILER_NAME = "/usr/local/share/aliflang/linux_alif_version.inf";
		TXT_LIBWX_NAME = "/usr/local/share/aliflibwx/linux_aliflibwx_version.inf";
		TXT_IDE_NAME = "/usr/local/share/alifstudio/linux_alifstudio_version.inf";

		TXT_URL_COMPILER_NAME = "http://www.aliflang.org/update/linux_alif_version.inf";
		TXT_URL_LIBWX_NAME = "http://www.aliflang.org/update/linux_aliflibwx_version.inf";
		TXT_URL_IDE_NAME = "http://www.aliflang.org/update/linux_alifstudio_version.inf";

		wxFileName tfname(wxFileName::GetTempDir()); // wxStandardPaths::Get().GetTempDir()
		wxString PATH_TEMP = tfname.GetPathWithSep();

		if (PATH_TEMP.length() < 4)
			PATH_TEMP = "/tmp/";
		
		TMP_PKG_PATH_COMPILER = PATH_TEMP + "aliflang.deb";
		TMP_PKG_PATH_IDE = PATH_TEMP + "alifstudio.deb";
		TMP_PKG_PATH_LIBWX = PATH_TEMP + "aliflibwx.deb";

	#endif
}

FRAME_1::~FRAME_1(){}
class MyApp : public wxApp
{
    public:
        MyApp();
		~MyApp();
		virtual bool OnInit();
        virtual int OnExit();
	private:
		DECLARE_NO_COPY_CLASS(MyApp)
};

DECLARE_APP(MyApp);
IMPLEMENT_APP(MyApp);
MyApp::MyApp(){}
MyApp::~MyApp(){}

int MyApp::OnExit()
{
	// Clean
	if (wxFileName::FileExists(TMP_PKG_PATH_COMPILER))
		wxRemoveFile(TMP_PKG_PATH_COMPILER);
	if (wxFileName::FileExists(TMP_PKG_PATH_IDE))
		wxRemoveFile(TMP_PKG_PATH_IDE);
	if (wxFileName::FileExists(TMP_PKG_PATH_LIBWX))
		wxRemoveFile(TMP_PKG_PATH_LIBWX);
	
	return 0;
}

int ALIF_STUDIO_PID = 0;

bool MyApp::OnInit()
{
	// to read ARG
	//if (!wxApp::OnInit())
		//return false;

	if ((wxApp::argc - 1) == 1)
	{
		ALIF_STUDIO_PID = wxAtoi(wxApp::argv[1]);
	}

	OBJ_FRAME_1 = new FRAME_1();
	OBJ_FRAME_1->SetLayoutDirection(wxLayout_RightToLeft);
	SetTopWindow(OBJ_FRAME_1);
	OBJ_FRAME_1->Center(true);
	OBJ_FRAME_1->Refresh();
	OBJ_FRAME_1->Show();
	
    return true;
}

// ----------------------------------------

#ifdef _WIN32

	bool ExtractZipFiles(const wxString& aZipFile, const wxString& aTargetDir)
	{
		bool ret = true;
		
		std::auto_ptr<wxZipEntry> entry(new wxZipEntry());
		
		do {
		
			wxFileInputStream in(aZipFile);
		
			if (!in)
			{
				wxMessageBox(wxT("لم تنجح عملية فتح الملف \n\n" + aZipFile), wxT("خطأ"), wxICON_WARNING);
				ret = false;
				break;
			}

			wxZipInputStream zip(in);
		
			while (entry.reset(zip.GetNextEntry()), entry.get() != NULL) {
			// access meta-data
			wxString name = entry->GetName();
			name = aTargetDir + wxFileName::GetPathSeparator() + name;
		
			// read 'zip' to access the entry's data
			if (entry->IsDir()) {
				int perm = entry->GetMode();
				wxFileName::Mkdir(name, perm, wxPATH_MKDIR_FULL);
			} else {
				zip.OpenEntry(*entry.get());
				if (!zip.CanRead()) {

				wxMessageBox(wxT("لم تنجح عملية فتح الملف \n\n" + entry->GetName()), wxT("خطأ"), wxICON_WARNING);
				ret = false;
				break;
				}
		
				wxFileOutputStream file(name);
		
				if (!file) {

					wxMessageBox(wxT("لم تنجح عملية فتح الملف \n\n" + name), wxT("خطأ"), wxICON_WARNING);
				ret = false;
				break;
				}
				zip.Read(file);
		
			}
		
			}
		
		} while(false);
		
		return ret;
	}

#endif

// ----------------------------------------

void DOWNLOAD(string URL_FILE, string FILE_PATH)
{
	// لا تستعملو HTTPS !
	
	wxHTTP HTTP;
	HTTP.SetHeader(_T("Content-type"), _T("application/zip"));
	HTTP.SetTimeout(10);

	while (!HTTP.Connect(_T("www.aliflang.org"), 80))
		wxSleep(6);
	
	wxApp::IsMainLoopRunning();

	wxInputStream *HTTP_INPUT_STREAM = HTTP.GetInputStream(URL_FILE); 

	if (HTTP.GetError() == wxPROTO_NOERR)
	{
		wxFileOutputStream FILE(FILE_PATH);
    		HTTP_INPUT_STREAM->Read(FILE);
		FILE.Close();
	}
	else
	{
		wxMessageBox(wxT("تعدر الاتصال بالخادم !\n\n"
						"من فظلكم، تأكدو من اتصالكم بشبكة الأنترنت ثم حاولو من جديد\n"
						"يمكنكم أيضا تحميل النسخة الجديدة عبر الموقع الرسمي للغة البرمجة ألف\n\n"
						"w w w . a l i f l a n g . o r g"), wxT("تعدر الاتصال بالخادم"), wxICON_WARNING);
	}
	
	wxDELETE(HTTP_INPUT_STREAM);
	HTTP.Close();
}

// ----------------------------------------

void GET_VERSION_HTTP(string URL_FILE, int *pVersion, string *pVersion_S, string *pURL)
{
	wxHTTP HTTP;
	HTTP.SetHeader(_T("Content-type"), _T("text/html; charset=utf-8"));
	HTTP.SetTimeout(10);

	while (!HTTP.Connect(_T("www.aliflang.org"), 80))
		wxSleep(6);
	
	wxApp::IsMainLoopRunning();

	wxInputStream *HTTP_INPUT_STREAM = HTTP.GetInputStream(URL_FILE);

	if (HTTP.GetError() == wxPROTO_NOERR)
	{
			wxString HTTP_RES;
			wxStringOutputStream HTTP_OUTPUT_STREAM(&HTTP_RES);
			HTTP_INPUT_STREAM->Read(HTTP_OUTPUT_STREAM);

			std::istringstream BUFFER_STREAM(std::string(HTTP_RES.mb_str()));

			std::string LINE;

			int CURRENT_LINE = 1;

			while (std::getline(BUFFER_STREAM, LINE))
			{
				if (CURRENT_LINE == 1)
				{
					CURRENT_LINE++;
					*pVersion = std::stoi(LINE.c_str());
				}
				else if (CURRENT_LINE == 2)
				{
					CURRENT_LINE++;
					*pVersion_S = LINE;
				}
				else
				{
					*pURL = LINE;
					break;
				}
			}
	}
	else
	{
		wxMessageBox(wxT("تعدر الاتصال بالخادم !\n\n"
					"من فظلكم، تأكدو من اتصالكم بشبكة الأنترنت ثم حاولو من جديد\n"
					"يمكنكم أيضا تحميل النسخة الجديدة عبر الموقع الرسمي للغة البرمجة ألف\n\n"
					"w w w . a l i f l a n g . o r g"), wxT("تعدر الاتصال بالخادم"), wxICON_WARNING);
			
		OBJ_BUTTON_UPDATE->Enable(true);
		OBJ_TXT_LIBRARY->SetLabel(wxT(" بحث عبر الأنترنت "));
	}
	
	wxDELETE(HTTP_INPUT_STREAM);
	HTTP.Close();
}

// ----------------------------------------

void GET_VERSION_LOCAL(string URL_FILE, int *pVersion, string *pVersion_S)
{
	string LINE;
	bool LINE_ONE = true;

	ifstream FILE_STREAM(URL_FILE);

	if (!FILE_STREAM.is_open())
	{
		//wxMessageBox("Can't read file : '" + URL_FILE + "' ");
		wxMessageBox(wxT("لم تنجح عملية فتح الملف \n\n" + URL_FILE), wxT("خطأ"), wxICON_WARNING);
		*pVersion = 0;
		*pVersion_S = "0.0 Beta";

		return;
	}
	
	while (getline(FILE_STREAM, LINE))
	{
		if (LINE_ONE)
		{
			LINE_ONE = false;

			*pVersion = std::stoi(LINE.c_str());
		}
		else
		{
			*pVersion_S = LINE;
			break;
		}
	}
}

// ----------------------------------------

bool INSTALL_PKG(wxString PKG_FULL_PATH)
{
	#ifdef _WIN32
		// extract (zip) into absolute path

		if (ExtractZipFiles(PKG_FULL_PATH, ABSOLUTE_PATH))
		{
			return true;
		}
		else
		{
			return false;
		}

	#elif __APPLE__
		// install pkg by running (open alif.pkg)

		wxString CMD;
		CMD = wxT("open ") + PKG_FULL_PATH;

		if (wxExecute(CMD, wxEXEC_ASYNC))
		{
			return true;
		}
		else
		{
			return false;
		}

	#else
		// install pkg by running (deb / rpg / pkg) installer command

		wxString CMD;
		
		CMD = wxT("xdg-open ") + PKG_FULL_PATH;

		// wxEXEC_ASYNC imidiat return
		// wxEXEC_SYNC wait prog to exit

		if (wxExecute(CMD, wxEXEC_ASYNC))
		{
			return true;
		}
		else
		{
			return false;
		}

	#endif
}

// ----------------------------------------

void FRAME_1::BOUTON_UPDATE_CLICK(wxCommandEvent &event)
{
	event.Skip();

	if (SEARCH)
	{
		// Clean
		if (wxFileName::FileExists(TMP_PKG_PATH_COMPILER))
			wxRemoveFile(TMP_PKG_PATH_COMPILER);
		if (wxFileName::FileExists(TMP_PKG_PATH_IDE))
			wxRemoveFile(TMP_PKG_PATH_IDE);
		if (wxFileName::FileExists(TMP_PKG_PATH_LIBWX))
			wxRemoveFile(TMP_PKG_PATH_LIBWX);

		OBJ_BUTTON_UPDATE->Enable(false);
		OBJ_TXT_ALIF_STUDIO->SetLabel(wxT("جاري البحث عن نسخة جديدة عبر الأنترنت.."));

		GET_VERSION_HTTP(TXT_URL_COMPILER_NAME,	&VERSION_LAST_COMPILER, 
												&VERSION_S_LAST_COMPILER, 
												&URL_LAST_COMPILER);
		
		GET_VERSION_HTTP(TXT_URL_LIBWX_NAME, &VERSION_LAST_LIBRARY, 
											 &VERSION_S_LAST_LIBRARY, 
											 &URL_LAST_LIBRARY);

		GET_VERSION_HTTP(TXT_URL_IDE_NAME,	&VERSION_LAST_ALIFSTUDIO, 
											&VERSION_S_LAST_ALIFSTUDIO, 
											&URL_LAST_ALIFSTUDIO);

		// Check Setup

		// TODO: Check files existe before update !

		// Get Installed Alif Version
		GET_VERSION_LOCAL(TXT_COMPILER_NAME, &VERSION_INSTALLED_COMPILER, &VERSION_S_INSTALLED_COMPILER);

		// Get Installed Library WX Version
		GET_VERSION_LOCAL(TXT_LIBWX_NAME, &VERSION_INSTALLED_LIBRARY, &VERSION_S_INSTALLED_LIBRARY);

		// Get Installed Alif Studio
		GET_VERSION_LOCAL(TXT_IDE_NAME, &VERSION_INSTALLED_ALIFSTUDIO, &VERSION_S_INSTALLED_ALIFSTUDIO);

		// Show Informations
		
		OBJ_TXT_COMPILER->SetLabel(	wxT("[برنامج مترجم ألف]\n"
										"الإصدار الحالي : ") + VERSION_S_INSTALLED_COMPILER +
										wxT("\nأخر إصدار : ") + VERSION_S_LAST_COMPILER);

		OBJ_TXT_LIBRARY->SetLabel(	wxT("[مكتبات الواجهة]\n"
										"الإصدار الحالي : ") + VERSION_S_INSTALLED_LIBRARY +
										wxT("\nأخر إصدار : ") + VERSION_S_LAST_LIBRARY);

		OBJ_TXT_ALIF_STUDIO->SetLabel(	wxT("[برنامج ألف ستوديو]\n"
										"الإصدار الحالي : ") + VERSION_S_INSTALLED_ALIFSTUDIO +
										wxT("\nأخر إصدار : ") + VERSION_S_LAST_ALIFSTUDIO);
		
		// Check if there aplicable Update

		if (VERSION_LAST_COMPILER > VERSION_INSTALLED_COMPILER ||
			VERSION_LAST_LIBRARY > VERSION_INSTALLED_LIBRARY ||
			VERSION_LAST_ALIFSTUDIO > VERSION_INSTALLED_ALIFSTUDIO)
		{
			SEARCH = false;
			OBJ_BUTTON_UPDATE->Enable(true);
			OBJ_BUTTON_UPDATE->SetLabel(wxT(" موافق "));

			wxMessageBox(wxT("ثم العتور على نسخ جديدة ! \nرجاء، اظغط على زر موافق لتحميلها و تتبيتها بشكل آلي"),
						wxT("نسخ جديدة !"), wxICON_INFORMATION);		
		}
		else
		{
			wxMessageBox(wxT("لم يتم العتور على نسخ جديدة، رجاءً، حاولو مرة أخرى لاحقا"),
						wxT("لا توجد نسخ جديدة"), wxICON_EXCLAMATION);
		}
	}
	else
	{
		OBJ_BUTTON_UPDATE->Enable(false);

		// Search again for installed version
		// to avoid re-installed when
		// one faild.

		// Get Installed Alif Version
		GET_VERSION_LOCAL(TXT_COMPILER_NAME, &VERSION_INSTALLED_COMPILER, &VERSION_S_INSTALLED_COMPILER);

		// Get Installed Library WX Version
		GET_VERSION_LOCAL(TXT_LIBWX_NAME, &VERSION_INSTALLED_LIBRARY, &VERSION_S_INSTALLED_LIBRARY);

		// Get Installed Alif Studio
		GET_VERSION_LOCAL(TXT_IDE_NAME, &VERSION_INSTALLED_ALIFSTUDIO, &VERSION_S_INSTALLED_ALIFSTUDIO);

		if (VERSION_LAST_COMPILER > VERSION_INSTALLED_COMPILER)
		{
			if (!wxFileName::FileExists(TMP_PKG_PATH_COMPILER))
			{
				OBJ_TXT_COMPILER->SetLabel(wxT("جاري تحميل برنامج مترجم ألف..."));

				DOWNLOAD(URL_LAST_COMPILER, TMP_PKG_PATH_COMPILER);
			}
			
			if (!wxFileName::FileExists(TMP_PKG_PATH_COMPILER))
			{
				OBJ_TXT_COMPILER->SetLabel(wxT(" خطأ في التحميل "));

				OBJ_BUTTON_UPDATE->Enable(true);
				goto GOTO_IDE;
			}

			OBJ_TXT_COMPILER->SetLabel(wxT(" جاري تتبيث البرنامج... "));

			if (INSTALL_PKG(TMP_PKG_PATH_COMPILER))
			{
				OBJ_TXT_COMPILER->SetLabel(wxT(" تمت عملية التتبيت بنجاح "));
			}
			else
			{
				OBJ_TXT_COMPILER->SetLabel(wxT(" خطأ في التتبيث "));

				OBJ_BUTTON_UPDATE->Enable(true);
			}
		}

		GOTO_IDE:

		if (VERSION_LAST_ALIFSTUDIO > VERSION_INSTALLED_ALIFSTUDIO)
		{
			if (!wxFileName::FileExists(TMP_PKG_PATH_IDE))
			{
				OBJ_TXT_ALIF_STUDIO->SetLabel(wxT("جاري تحميل برنامج ألف ستوديو... "));

				DOWNLOAD(URL_LAST_ALIFSTUDIO, TMP_PKG_PATH_IDE);
			}
			
			if (!wxFileName::FileExists(TMP_PKG_PATH_IDE))
			{
				OBJ_TXT_ALIF_STUDIO->SetLabel(wxT(" خطأ في التحميل "));

				OBJ_BUTTON_UPDATE->Enable(true);
				goto GOTO_LIB;
			}

			OBJ_TXT_ALIF_STUDIO->SetLabel(wxT(" جاري تتبيث البرنامج... "));

			// Close Alif Studio Process
			if (ALIF_STUDIO_PID > 0)
				wxKill(ALIF_STUDIO_PID);

			//if (ExtractZipFiles("ide.zip", ZIP_EXTRACT_PATH_IDE))
			if (INSTALL_PKG(TMP_PKG_PATH_IDE))
			{
				OBJ_TXT_ALIF_STUDIO->SetLabel(wxT(" تمت عملية التتبيت بنجاح "));

				// Run Alif Studio Again

				// TODO: Wait installer to finish, before run new IDE.

				//#ifdef __APPLE__
					//wxExecute("open \"/Applications/Alif Studio.app\"");
				//#elif
					//wxExecute("alifstudio");
				//#endif
			}
			else
			{
				OBJ_TXT_ALIF_STUDIO->SetLabel(wxT(" خطأ في التتبيث "));

				OBJ_BUTTON_UPDATE->Enable(true);
			}
		}

		GOTO_LIB:

		if (VERSION_LAST_LIBRARY > VERSION_INSTALLED_LIBRARY)
		{
			if (!wxFileName::FileExists(TMP_PKG_PATH_LIBWX))
			{
				OBJ_TXT_LIBRARY->SetLabel(wxT("جاري تحميل مكتبات الواجهة..."));

				DOWNLOAD(URL_LAST_LIBRARY, TMP_PKG_PATH_LIBWX);
			}
			
			if (!wxFileName::FileExists(TMP_PKG_PATH_LIBWX))
			{
				OBJ_TXT_LIBRARY->SetLabel(wxT(" خطأ في التحميل "));

				OBJ_BUTTON_UPDATE->Enable(true);
				goto GOTO_FINISH;
			}

			OBJ_TXT_LIBRARY->SetLabel(wxT(" جاري تتبيث البرنامج... "));

			//if (ExtractZipFiles("libwx.zip", ZIP_EXTRACT_PATH_LIBWX))
			if (INSTALL_PKG(TMP_PKG_PATH_IDE))
			{
				OBJ_TXT_LIBRARY->SetLabel(wxT(" تمت عملية التتبيت بنجاح "));
			}
			else
			{
				OBJ_TXT_LIBRARY->SetLabel(wxT(" خطأ في التتبيث "));

				OBJ_BUTTON_UPDATE->Enable(true);
			}
		}

		GOTO_FINISH:
		; // null statement
	}
}

void FRAME_1::BOUTON_EXIT_CLICK(wxCommandEvent &event)
{
	event.Skip();

	OBJ_BUTTON_EXIT->Enable(false);

	// Clean
	if (wxFileName::FileExists(TMP_PKG_PATH_COMPILER))
		wxRemoveFile(TMP_PKG_PATH_COMPILER);
	if (wxFileName::FileExists(TMP_PKG_PATH_IDE))
		wxRemoveFile(TMP_PKG_PATH_IDE);
	if (wxFileName::FileExists(TMP_PKG_PATH_LIBWX))
		wxRemoveFile(TMP_PKG_PATH_LIBWX);

	OBJ_FRAME_1->Destroy();
}
