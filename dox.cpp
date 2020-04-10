
#line 5 "index.md"

	
#line 19 "index.md"

	#include <iostream>
	#include <string>

#line 6 "index.md"
;
	
#line 31 "index.md"

	static std::string theme { "none" };

#line 59 "index.md"

	static std::string title;
	static std::string author;
	static std::string date { "\\today" };

#line 71 "index.md"

	static const
		std::string end_of_file {
			"\r\n"
		};

#line 83 "index.md"

	void nextline(std::string &line) {
		if (line != end_of_file) {
			if (! std::getline(std::cin, line)) {
				line = end_of_file;
			}
		}
	}

#line 112 "index.md"

	bool has_prefix(
		const std::string &line,
		const std::string &prefix
	) {
		const auto &l { line };
		const auto &p { prefix };
		return l.size() >= p.size() &&
			l.substr(0, p.size()) == p;
	}

#line 212 "index.md"

	bool in_two_columns { false };

#line 219 "index.md"

	void enter_two_columns() {
		if (! in_two_columns) {
			std::cout <<
				"\\begin{multicols}{2}\n";
			in_two_columns = true;
		}
	}

#line 232 "index.md"

	void exit_two_columns() {
		if (in_two_columns) {
			std::cout <<
				"\\end{multicols}\n";
			in_two_columns = false;
		}
	}

#line 260 "index.md"

	void format_line(
		const std::string line
	) {
		
#line 333 "index.md"

	for (unsigned i { 0 };
		i < line.length(); ++i
	) {
		
#line 346 "index.md"

	if (
		line[i] == '*' || line[i] == '_'
	) {
		
#line 357 "index.md"

	unsigned j { i + 1 };
	char mark { line[i] };
	while (j < line.length() &&
		line[j] >= ' ' && (
			isalnum(line[j]) ||
			line[j] == '*' ||
			line[j] == '_' ||
			line[j] == '-'
		)
	) { ++j; }

#line 373 "index.md"

	if (i + 1 < j &&
		line[j - 1] == mark
	) {
		
#line 385 "index.md"

	bool bold {
		i + 3 < j &&
		line[i + 1] == mark &&
		line[j - 2] == mark
	};

#line 396 "index.md"

	if (bold) {
		std::cout << "\\textbf{";
	} else {
		std::cout << "\\emph{";
	}

#line 407 "index.md"

	unsigned begin {
		bold ? i + 2 : i + 1
	};
	unsigned end { bold ? j - 2 : j - 1 };
	for (auto t { begin }; t < end; ++t) {
		
#line 426 "index.md"

	if (line[t] == mark) {
		std::cout << ' ';
	} else {
		std::cout << line[t];
	}

#line 413 "index.md"
;
	}
	std::cout << "}";
	
#line 438 "index.md"

	if (line[j] == ' ') {
		std::cout << '\\';
	}

#line 416 "index.md"
;
	i = j - 1;
	continue;

#line 377 "index.md"
;
	}

#line 350 "index.md"
;
	}

#line 337 "index.md"
;
		std::cout << line[i];
	}

#line 264 "index.md"
;
	}

#line 7 "index.md"
;
	int main(
		int argc,
		const char *const argv[]
	) {
		
#line 38 "index.md"
 {
	static const std::string light {
		"--theme=light"
	};
	static const std::string dark {
		"--theme=dark"
	};
	if (argc == 2 && argv[1] == light) {
		theme = "light";
	}
	if (argc == 2 && argv[1] == dark) {
		theme = "dark";
	}
} 
#line 102 "index.md"

	std::string line;
	nextline(line);
	
#line 128 "index.md"
 {
	static const std::string prefix {
		"# "
	};
	if (has_prefix(line, prefix)) {
		title = line.substr(
			prefix.size()
		);
		nextline(line);
	} else {
		std::cerr << "no title\n";
	}
} 
#line 146 "index.md"
 {
	static const std::string prefix {
		"* author: "
	};
	if (has_prefix(line, prefix)) {
		author = line.substr(
			prefix.size()
		);
		nextline(line);
	} else {
		std::cerr << "no author\n";
	}
} 
#line 163 "index.md"
 {
	static const std::string prefix {
		"* date: "
	};
	if (has_prefix(line, prefix)) {
		date = line.substr(
			prefix.size()
		);
		nextline(line);
	}
} 
#line 179 "index.md"

	while (
		line != end_of_file && line.size()
	) {
		std::cerr <<
			"ignoring meta line: " <<
			line << "\n";
		nextline(line);
	}

#line 105 "index.md"
;

#line 196 "index.md"

	std::cout <<
		
#line 5 "preamble.md"

	
#line 12 "preamble.md"

	"\\documentclass["
		"a5paper,ngerman,9pt"
	"]{article}\n"

#line 23 "preamble.md"

	"\\usepackage[T1]{fontenc}\n"
	"\\usepackage[utf8]{inputenc}\n"

#line 32 "preamble.md"

	"\\usepackage["
		"margin=0.5in,includefoot"
	"]{geometry}\n"

#line 41 "preamble.md"

	"\\usepackage{microtype}\n"
	"\\usepackage{babel}\n"

#line 50 "preamble.md"

	"\\usepackage[" <<
		theme <<
	"]{solarized}\n"

#line 59 "preamble.md"

	"\\usepackage{sectsty}\n"
	"\\usepackage{ccfonts}\n"
	"\\usepackage{euler}\n"

#line 69 "preamble.md"

	"\\usepackage{todone}\n"

#line 76 "preamble.md"

	"\\usepackage{fancyhdr}\n"
	"\\usepackage{fancyvrb}\n"

#line 85 "preamble.md"

	"\\usepackage{graphicx}\n"

#line 92 "preamble.md"

	"\\usepackage{multicol}\n"

#line 99 "preamble.md"

	"\\usepackage{mdframed}\n"

#line 106 "preamble.md"

	"\\pagestyle{fancy}\n"
	"\\fancypagestyle{plain}{\n"
	"\\fancyhf{}\n"

#line 115 "preamble.md"

	"\\fancyfoot[C]{{"
		"\\color{deemph}\\small"
		"$\\thepage$"
	"}}\n"

#line 125 "preamble.md"

	"\\renewcommand{\\headrulewidth}"
		"{0pt}\n"
	"\\renewcommand{\\footrulewidth}"
		"{0pt}}\n"

#line 135 "preamble.md"

	"\\title{"
		"\\color{emph}" << title <<
	"}\n"
	"\\author{" << author << "}\n"
	"\\date{" << date << "}\n"

#line 146 "preamble.md"

	"\\columnseprule.2pt\n"
	"\\renewcommand{\\columnseprulecolor}"
		"{\\color{deemph}}\n"

#line 155 "preamble.md"

	"\\begin{document}\n"

#line 162 "preamble.md"

	"\\pagecolor{background}\n"
	"\\color{normal}\n"
	"\\allsectionsfont{"
		"\\color{emph}\\mdseries"
	"}\n"

#line 173 "preamble.md"

	"\\pagestyle{plain}\n"
	"\\maketitle\n"
	"\\thispagestyle{fancy}\n"

#line 183 "preamble.md"

	"\\surroundwithmdframed["
		"backgroundcolor=codebackground,"
		"fontcolor=normal,"
		"hidealllines=true"
	"]{Verbatim}\n";

#line 6 "preamble.md"


#line 198 "index.md"
;

#line 248 "index.md"

	while (line != end_of_file) {
		
#line 272 "index.md"

	do {
		
#line 291 "index.md"
 {
	static const std::string prefix {
		"## "
	};
	if (has_prefix(line, prefix)) {
		
#line 305 "index.md"

	exit_two_columns();
	std::cout << "\\section{";
	format_line(line.substr(
		prefix.size()
	));
	std::cout << "}\n";

#line 296 "index.md"
;
		nextline(line);
		break;
	}
} 
#line 317 "index.md"

	if (has_prefix(line, "### ")) {
		std::cout << "\\subsection{";
		format_line(line.substr(4));
		std::cout << "}\n";
		nextline(line);
		break;
	}

#line 274 "index.md"
;
		enter_two_columns();
		format_line(line);
		std::cout << "\n";
		nextline(line);
	} while (false);

#line 250 "index.md"
;
	}
	exit_two_columns();
	std::cout << "\\end{document}\n";

#line 12 "index.md"
;
	}
