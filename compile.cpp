#include<fstream>
#include<stack>
#include <iostream>

void compile() {
	std::ifstream in("program.bf");
	std::ofstream out("compiled.asm");

	if (!out) {
		std::cerr << "Error: Unable to write to compiled.asm" << std::endl;
	}

	if (!in) {
		std::cerr << "Error: Unable to read from program.bf" << std::endl;
	}

	auto prolog = R"(
global  _start
extern getchar
extern putchar
extern exit
section .text
_start:
  sub rsp, 4000
  mov eax, 0
  mov ecx, 4000
  mov rid, rsp
  rep stosb
  mov r12, rsp
  sub rsp, 64
)";

	out << prolog;

	std::stack<int> labels;
	int current_label = 0;

	char c;
	while (in >> c) {
		switch (c) {
		case '>':
			out << "  add r12, 1\n";
			break;
		case '<':
			out << "  sub r12, 1\n";
			break;
		case '+':
			out << "  add byte [r12], 1\n";
			break;
		case '-':
			out << "  sub byte [r12], 1\n";
			break;
		case ',':
			out << "  call getchar\n"
				<< "  mov byte [r12], al\n";
			break;
		case '.':
			out << "  move cl, [r12]\n"
				   "  call putchar\n";
			break;
		case '[':
			out << "label" << current_label << "start:\n"
				<< "  cmp byte [r12], 0\n"
				<< "  jz label" << current_label << "end\n";
			labels.push(current_label);
			current_label++;
			break;
		case ']':
			out << "  jmp label" << labels.top() << "start\n"
				<< "label" << labels.top() << "end:\n";
			labels.pop();
			break;
		default:
			break;
		}
	}

	auto epilog = R"(
  add rsp, 4064
  mov eax, 0
  call exit
)";

	out << epilog;

	std::cout << "Compiled" << std::endl;
}