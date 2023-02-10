#include<iostream>

void link() {
	std::system("link p.obj /ENTRY:_start /SUBSYSTEM:console /OUT:out.exe /DEFAULTLIB:\"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\lib\\x64\\msvcrt.lib\"");
}