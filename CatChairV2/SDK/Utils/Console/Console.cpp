#include "Console.hpp"
#include <Windows.h>
#include <iostream>

void Console::AttachConsole() {
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout); /* Open the Output Handle */

	printf("Attached Console\n");
}

void Console::DetachConsole() {
	FreeConsole(); /* Free the Console from the Game */
	fclose(stdout); /* Close the Handle we opened */
}