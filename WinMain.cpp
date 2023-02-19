#include "Resources/Headers/Onyx.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
try {
	Window wnd(800, 300, "Onyx");
	Window wnd2(800, 300, "Best");
	MSG msg;
	BOOL gResult;

	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (gResult == -1) {
		return -1;
	}
	
	return msg.wParam;
}
catch (const CustomException& e) {
	MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
}
catch (const std::exception& e) {
	MessageBox(nullptr, e.what(), "Standart Exception", MB_OK | MB_ICONEXCLAMATION);
}
catch (...) {
	MessageBox(nullptr,"No details","Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
}

return -1;
}
