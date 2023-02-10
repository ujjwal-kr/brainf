#include<fstream>
#include<stack>

void compile() {
	std::ifstream in("program.bf");
	std::ofstream out("compiled.asm");

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
}