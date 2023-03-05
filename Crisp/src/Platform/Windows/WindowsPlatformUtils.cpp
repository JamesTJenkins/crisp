#include "CrispPCH.h"
#include "Crisp/Utils/PlatformUtils.h"

// Windows API dialog
#include <commdlg.h>
#include <SDL.h>
#include <SDL_syswm.h>

#include "Crisp/Core/Application.h"

namespace Crisp {
	static HWND GetWindowsWindow() {
		SDL_SysWMinfo wmInfo;
		SDL_VERSION(&wmInfo.version);
		SDL_GetWindowWMInfo((SDL_Window*)Application::Get().GetWindow().GetNativeWindow(), &wmInfo);
		return wmInfo.info.win.window;
	}

	std::string FileDialog::OpenFile(const char* filter) {
		OPENFILENAMEA ofn;	// Common dialog box structure
		CHAR szFile[260] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = GetWindowsWindow();
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetOpenFileNameA(&ofn) == TRUE) {
			return ofn.lpstrFile;
		}
		return std::string();
	}

	std::string FileDialog::SaveFile(const char* filter) {
		OPENFILENAMEA ofn;	// Common dialog box structure
		CHAR szFile[260] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = GetWindowsWindow();
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetSaveFileNameA(&ofn) == TRUE) {
			return ofn.lpstrFile;
		}
		return std::string();
	}
}