#include <windows.h>
#include <iostream>
#pragma comment(lib, "user32")

void remove_scrollbar()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
}

#include <vector>


void centerify_output(std::string str, int num_cols) {
	// Calculate left padding
	int padding_left = (num_cols / 2) - (str.size() / 2);

	// Put padding spaces
	for (int i = 0; i < padding_left; ++i) std::cout << ' ';

	// Print the message
	std::cout << str;
}

int main()
{
	remove_scrollbar();
	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

	std::cout << "Hello world from full screen app!" << std::endl;
	std::vector<std::string> lines = {
		"---------------------------------",
		"|                               |",
		"|                               |",
		"|         User : xyz            |",
		"|         Pass : ****           |",
		"|                               |",
		"|                               |",
		"---------------------------------",
	};

	int num_cols = 100;

	// VIRTUAL BORDER
	std::cout << std::endl;
	for (int i = 0; i < num_cols; ++i) std::cout << ' ';
	std::cout << '|' << std::endl;

	// OUTPUT
	for (int i = 0; i < lines.size(); ++i) {
		centerify_output(lines[i], num_cols);
		std::cout << std::endl;
	}

	// VIRTUAL BORDER
	std::cout << std::endl;
	for (int i = 0; i < num_cols; ++i) std::cout << ' ';
	std::cout << '|' << std::endl;
	std::cin.get();
}
	
