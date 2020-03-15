
#line 5 "index.md"

	
#line 17 "index.md"

	#include <iostream>
	#include <string>

#line 6 "index.md"
;
	
#line 24 "index.md"

	static std::string theme { "none" };

#line 41 "index.md"

	static std::string title;
	static std::string author;
	static std::string date { "\\today" };

#line 49 "index.md"

	static std::string end_of_file {
		"**End_of_filE**"
	};
	void nextline(std::string &line) {
		if (line != end_of_file) {
			if (! std::getline(std::cin, line)) {
				line = end_of_file;
			}
		}
	}

#line 83 "index.md"

	bool has_prefix(const std::string &line, const std::string &prefix) {
		return line.size() >= prefix.size() &&
			line.substr(0, prefix.size()) == prefix;
	}

#line 162 "index.md"

	bool in_two_columns { false };
	void enter_two_columns() {
		if (! in_two_columns) {
			std::cout << "\\begin{multicols}{2}\n";
			in_two_columns = true;
		}
	}
	void exit_two_columns() {
		if (in_two_columns) {
			std::cout << "\\end{multicols}\n";
			in_two_columns = false;
		}
	}

#line 180 "index.md"

	void format_line(const std::string line) {
		
#line 230 "index.md"

	for (unsigned i { 0 }; i < line.length(); ++i) {
		if (line[i] == '*') {
			unsigned j { i + 1 };
			while (j < line.length() && line[j] >= ' ' && (isalnum(line[j]) || line[j] == '*')) { ++j; }
			if (line[j - 1] == '*') {
				std::cout << "\\emph{";
				for (unsigned t { i + 1 }; t + 1< j; ++t) {
					if (line[t] == '*') {
						std::cout << ' ';
					} else {
						std::cout << line[t];
					}
				}
				std::cout << "}";
				if (line[j] == ' ') {
					std::cout << '\\';
				}
				i = j - 1; continue;
			}
		}
		std::cout << line[i];
	}

#line 182 "index.md"
;
	}

#line 7 "index.md"
;
	int main(
		int argc, const char *const argv[]
	) {
		
#line 30 "index.md"

	if (argc == 2 && argv[1] == std::string { "--theme=light" }) {
		theme = "light";
	}
	if (argc == 2 && argv[1] == std::string { "--theme=dark" }) {
		theme = "dark";
	}

#line 64 "index.md"

	std::string line;
	nextline(line);
	
#line 72 "index.md"

	if (line.size() >= 2 && line[0] == '#' && line[1] == ' ') {
		title = line.substr(2);
		nextline(line);
	} else {
		std::cerr << "no title\n";
	}

#line 92 "index.md"

	if (has_prefix(line, "* author: ")) {
		author = line.substr(10);
		nextline(line);
	} else {
		std::cerr << "no author\n";
	}

#line 103 "index.md"

	if (has_prefix(line, "* date: ")) {
		date = line.substr(8);
		nextline(line);
	}

#line 112 "index.md"

	while (line.size()) {
		std::cerr << "ignoring meta line: " << line << "\n";
		nextline(line);
	}

#line 121 "index.md"

	std::cout <<
		"\\documentclass[a5paper,ngerman,9pt]{article}\n"
		"\\usepackage[T1]{fontenc}\n"
		"\\usepackage[utf8]{inputenc}\n"
		"\\usepackage[margin=0.5in,includefoot]{geometry}\n"
		"\\usepackage{microtype}\n"
		"\\usepackage{babel}\n"
		"\\usepackage[" << theme << "]{solarized}\n"
		"\\usepackage{sectsty}\n"
		"\\usepackage{ccfonts}\n"
		"\\usepackage{euler}\n"
		"\\usepackage{todone}\n"
		"\\usepackage{fancyhdr}\n"
		"\\usepackage{fancyvrb}\n"
		"\\usepackage{graphicx}\n"
		"\\usepackage{multicol}\n"
		"\\usepackage{mdframed}\n"
		"\\pagestyle{fancy}\n"
		"\\fancypagestyle{plain}{\n"
		"\\fancyhf{}\n"
		"\\fancyfoot[C]{{\\color{deemph}\\small$\\thepage$}}\n"
		"\\renewcommand{\\headrulewidth}{0pt}\n"
		"\\renewcommand{\\footrulewidth}{0pt}}\n"
		"\\title{\\color{emph}" << title << "}\n"
		"\\author{" << author << "}\n"
		"\\date{" << date << "}\n"
		"\\columnseprule.2pt\n"
		"\\renewcommand{\\columnseprulecolor}{\\color{deemph}}\n"
		"\\begin{document}\n"
		"\\pagecolor{background}\n"
		"\\color{normal}\n"
		"\\allsectionsfont{\\color{emph}\\mdseries}\n"
		"\\pagestyle{plain}\n"
		"\\maketitle\n"
		"\\thispagestyle{fancy}\n"
		"\\surroundwithmdframed[backgroundcolor=codebackground,fontcolor=normal,hidealllines=true]{Verbatim}\n";

#line 67 "index.md"
;

#line 188 "index.md"

	while (line != end_of_file) {
		
#line 198 "index.md"

	do {
		
#line 209 "index.md"

	if (has_prefix(line, "## ")) {
		exit_two_columns();
		std::cout << "\\section{";
		format_line(line.substr(3));
		std::cout << "}\n";
		enter_two_columns();
		nextline(line);
		break;
	}
	if (has_prefix(line, "### ")) {
		std::cout << "\\subsection{";
		format_line(line.substr(4));
		std::cout << "}\n";
		nextline(line);
		break;
	}

#line 200 "index.md"
;
		format_line(line);
		std::cout << "\n";
		nextline(line);
	} while (false);

#line 190 "index.md"
;
	}
	exit_two_columns();
	std::cout << "\\end{document}\n";

#line 11 "index.md"
;
	}
