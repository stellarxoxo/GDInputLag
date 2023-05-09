#include <Windows.h>
#include <stdio.h>

#include "extensions2.h"
#include "the_big_bad_wolf.h"

void extension_menu(
	LPVOID instance
) {
	MegaHackExt::Window* window = MegaHackExt::Window::Create("Input Lag");

	MegaHackExt::CheckBox* checkbox = MegaHackExt::CheckBox::Create("-1 frame");
	window->add(checkbox);

	MegaHackExt::Client::commit(window);
}

void the_big_bad_wolf(
	LPVOID instance
) {
	while (true)
	{
		if (get_attempts() < 40)
		{
			Sleep(1000);
		}
		else
		{
			blow_the_house_down();
		}
	}
}

BOOL
APIENTRY
DllMain(
	LPVOID	instance,
	ULONG	reason_to_call,
	LPVOID	reserved
) {
	if (reason_to_call != DLL_PROCESS_ATTACH)
	{
		return TRUE;
	}

	CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(extension_menu), instance, 0, NULL);
	CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(the_big_bad_wolf), instance, 0, NULL);

	return TRUE;
}