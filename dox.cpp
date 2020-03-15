
#line 5 "index.md"

	
#line 17 "index.md"

	#include <iostream>
	#include <string>

#line 6 "index.md"
;
	
#line 24 "index.md"

	static std::string title;
	static std::string author;
	static std::string date { "\\today" };

#line 32 "index.md"

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

#line 66 "index.md"

	bool has_prefix(const std::string &line, const std::string &prefix) {
		return line.size() >= prefix.size() &&
			line.substr(0, prefix.size()) == prefix;
	}

#line 145 "index.md"

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

#line 7 "index.md"
;
	int main(
		int argc, const char *const argv[]
	) {
		
#line 47 "index.md"

	std::string line;
	nextline(line);
	
#line 55 "index.md"

	if (line.size() >= 2 && line[0] == '#' && line[1] == ' ') {
		title = line.substr(2);
		nextline(line);
	} else {
		std::cerr << "no title\n";
	}

#line 75 "index.md"

	if (has_prefix(line, "* author: ")) {
		author = line.substr(10);
		nextline(line);
	} else {
		std::cerr << "no author\n";
	}

#line 86 "index.md"

	if (has_prefix(line, "* date: ")) {
		date = line.substr(8);
		nextline(line);
	}

#line 95 "index.md"

	while (line.size()) {
		std::cerr << "ignoring meta line: " << line << "\n";
		nextline(line);
	}

#line 104 "index.md"

	std::cout <<
		"\\documentclass[a5paper,ngerman,9pt]{article}\n"
		"\\usepackage[T1]{fontenc}\n"
		"\\usepackage[utf8]{inputenc}\n"
		"\\usepackage[margin=0.5in,includefoot]{geometry}\n"
		"\\usepackage{microtype}\n"
		"\\usepackage{babel}\n"
		"\\usepackage[none]{solarized}\n"
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

#line 50 "index.md"
;

#line 163 "index.md"

	while (line != end_of_file) {
		
#line 173 "index.md"

	do {
		
#line 183 "index.md"

	if (has_prefix(line, "## ")) {
		exit_two_columns();
		std::cout << "\\section{" << line.substr(3) << "}\n";
		enter_two_columns();
		nextline(line);
		break;
	}
	if (has_prefix(line, "### ")) {
		std::cout << "\\subsection{" << line.substr(4) << "}\n";
		nextline(line);
		break;
	}

#line 175 "index.md"
;
		std::cout << line << "\n";
		nextline(line);
	} while (false);

#line 165 "index.md"
;
	}
	exit_two_columns();
	std::cout << "\\end{document}\n";

#line 11 "index.md"
;
	}
