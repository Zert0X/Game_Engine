#include <App.h>
App::App()
	:
	wnd(800, 600, "Onyx")
{}

int App::Go() {
	while (true) {
		
		if (const auto ecode = Window::ProcessMessage()) {
			return *ecode;
		}

		DoFrame();
	}

}

void App::DoFrame() {
}