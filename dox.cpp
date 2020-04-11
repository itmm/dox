
#line 5 "index.md"

	
#line 19 "index.md"

	#include <iostream>
	#include <string>

#line 6 "index.md"
;
	
#line 31 "index.md"

	static std::string theme {};

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
		
#line 338 "index.md"

	for (unsigned i { 0 };
		i < line.size(); ++i
	) {
		
#line 351 "index.md"

	if (
		line[i] == '*' || line[i] == '_'
	) {
		
#line 362 "index.md"

	unsigned j { i + 1 };
	char mark { line[i] };
	while (j < line.size() &&
		line[j] >= ' ' && (
			isalnum(line[j]) ||
			line[j] == '*' ||
			line[j] == '_' ||
			line[j] == '-'
		)
	) { ++j; }

#line 378 "index.md"

	if (i + 1 < j &&
		line[j - 1] == mark
	) {
		
#line 390 "index.md"

	bool bold {
		i + 3 < j &&
		line[i + 1] == mark &&
		line[j - 2] == mark
	};

#line 401 "index.md"

	if (bold) {
		std::cout << "\\textbf{";
	} else {
		std::cout << "\\emph{";
	}

#line 412 "index.md"

	unsigned begin {
		bold ? i + 2 : i + 1
	};
	unsigned end { bold ? j - 2 : j - 1 };
	for (auto t { begin }; t < end; ++t) {
		
#line 431 "index.md"

	if (line[t] == mark) {
		std::cout << ' ';
	} else {
		std::cout << line[t];
	}

#line 418 "index.md"
;
	}
	std::cout << "}";
	
#line 443 "index.md"

	if (line[j] == ' ') {
		std::cout << '\\';
	}

#line 421 "index.md"
;
	i = j - 1;
	continue;

#line 382 "index.md"
;
	}

#line 355 "index.md"
;
	}

#line 544 "index.md"

	if (line[i] == '$') {
		
#line 553 "index.md"

	unsigned j { i + 1 };
	while (j < line.size() &&
		line[j] != '$'
	) { ++j; }

#line 563 "index.md"

	if (j < line.size() && line[j] == '$') {
		for (auto t { i }; t <= j; ++t) {
			std::cout << line[t];
		}
		i = j;
		continue;
	}

#line 546 "index.md"
;
	}

#line 681 "index.md"

	if (line[i] == '`') {
		
#line 690 "index.md"

	unsigned j { i + 1 };
	for (;
		j < line.size() && line[j] != '`';
		++j
	) {}

#line 701 "index.md"

	if (j < line.size() &&
		line[j] == '`'
	) {
		
#line 714 "index.md"

	std::cout << "\\hlInline{";
	for (auto t { i + 1 }; t < j; ++t) {
		
#line 653 "index.md"

	if (line[t] == ' ') {
		std::cout << "\\";
	}
	if (line[t] == '-' && t > 0 &&
		isalpha(line[t - 1])
	) {
		std::cout << "{\\text -}";
	} else {
		std::cout << line[t];
	}

#line 717 "index.md"
;
	}
	std::cout << "}";

#line 726 "index.md"

	if (j + 1 < line.size() &&
		line[j + 1] == ' '
	) {
		std::cout << "\\";
	}

#line 705 "index.md"
;
		i = j;
		continue;
	}

#line 683 "index.md"
;
	}

#line 342 "index.md"
;
		std::cout << line[i];
	}

#line 264 "index.md"
;
	}

#line 457 "index.md"

	enum class List_Type {
		no_list, enum_list, item_list
	} list_type { List_Type::no_list };

#line 466 "index.md"

	void open_list(bool enumerate) {
		if (list_type == List_Type::no_list) {
			if (enumerate) {
				std::cout << "\\begin{enumerate}\n";
				list_type = List_Type::enum_list;
			} else {
				std::cout << "\\begin{itemize}\n";
				list_type = List_Type::item_list;
			}
		}
		std::cout << "\\item ";
	}

#line 483 "index.md"

	void close_list() {
		switch (list_type) {
			case List_Type::no_list:
				break;
			case List_Type::enum_list:
				std::cout << "\\end{enumerate}\n";
				break;
			case List_Type::item_list:
				std::cout << "\\end{itemize}\n";
				break;
		}
		list_type = List_Type::no_list;
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
		"a5paper,ngerman"
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
	"\\usepackage{siunitx}\n"

#line 52 "preamble.md"

	"\\usepackage" << (theme.size() ?
		"[" + theme + "]" : ""
	) << "{solarized}\n"

#line 61 "preamble.md"

	"\\usepackage{sectsty}\n"
	"\\usepackage{ccfonts}\n"
	"\\usepackage{euler}\n"

#line 71 "preamble.md"

	"\\usepackage{todone}\n"

#line 78 "preamble.md"

	"\\usepackage{fancyhdr}\n"
	"\\usepackage{fancyvrb}\n"

#line 87 "preamble.md"

	"\\usepackage{graphicx}\n"

#line 94 "preamble.md"

	"\\usepackage{multicol}\n"

#line 101 "preamble.md"

	"\\usepackage{mdframed}\n"

#line 108 "preamble.md"

	"\\usepackage{lisp}\n"

#line 115 "preamble.md"

	"\\pagestyle{fancy}\n"
	"\\fancypagestyle{plain}{\n"
	"\\fancyhf{}\n"

#line 124 "preamble.md"

	"\\fancyfoot[C]{{"
		"\\color{deemph}\\small"
		"$\\thepage$"
	"}}\n"

#line 134 "preamble.md"

	"\\renewcommand{\\headrulewidth}"
		"{0pt}\n"
	"\\renewcommand{\\footrulewidth}"
		"{0pt}}\n"

#line 144 "preamble.md"

	"\\title{"
		"\\color{emph}" << title <<
	"}\n"
	"\\author{" << author << "}\n"
	"\\date{" << date << "}\n"

#line 155 "preamble.md"

	"\\columnseprule.2pt\n"
	"\\renewcommand{\\columnseprulecolor}"
		"{\\color{deemph}}\n"

#line 164 "preamble.md"

	"\\begin{document}\n"

#line 171 "preamble.md"

	"\\pagecolor{background}\n"
	"\\color{normal}\n"
	"\\allsectionsfont{"
		"\\color{emph}\\mdseries"
	"}\n"

#line 182 "preamble.md"

	"\\pagestyle{plain}\n"
	"\\maketitle\n"
	"\\thispagestyle{fancy}\n"

#line 192 "preamble.md"

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
 {
	static const std::string prefix {
		"### "
	};
	if (has_prefix(line, prefix)) {
		std::cout << "\\subsection{";
		format_line(line.substr(
			prefix.size()
		));
		std::cout << "}\n";
		nextline(line);
		break;
	}
} 
#line 501 "index.md"

	if (line == "") {
		close_list();
	}

#line 509 "index.md"
 {
	static const std::string prefix {
		"* "
	};
	if (has_prefix(line, prefix)) {
		open_list(false);
		format_line(line.substr(prefix.size()));
		std::cout << "\n";
		nextline(line);
		break;
	}
} 
#line 524 "index.md"

	if (line.size() && isdigit(line[0])) {
		unsigned i { 1 };
		while (i < line.size() && isdigit(line[i])) { ++i; }
		if (i + 1 < line.size() && line[i] == '.' && line[i + 1] == ' ') {
			open_list(true);
			format_line(line.substr(i + 1));
			std::cout << "\n";
			nextline(line);
			break;
		}
	}

#line 579 "index.md"

	if (line == "```lisp") {
		std::cout << "\\begin{lisp}\n";
		nextline(line);
		
#line 592 "index.md"

	int nr { 1 };
	while (line != end_of_file &&
		line != "```"
	) {
		
#line 608 "index.md"

	if (nr > 1) {
		std::cout << "\\\\*\n";
	}

#line 617 "index.md"

	std::cout << "$\\hlLine{" <<
		nr++ << "}";

#line 625 "index.md"

	unsigned i { 0 };
	for (;
		i < line.size() &&
			line[i] == '\t';
		++i
	) {}
	if (i) {
		std::cout << "\\hlIndent{" <<
			i << "}";
	}

#line 642 "index.md"

	for (auto t { i };
		t < line.size(); ++t
	) {
		
#line 653 "index.md"

	if (line[t] == ' ') {
		std::cout << "\\";
	}
	if (line[t] == '-' && t > 0 &&
		isalpha(line[t - 1])
	) {
		std::cout << "{\\text -}";
	} else {
		std::cout << line[t];
	}

#line 646 "index.md"
;
	}

#line 671 "index.md"

	std::cout << "$";

#line 597 "index.md"
;
		nextline(line);
	}
	std::cout << "\n";
	nextline(line);

#line 583 "index.md"
;
		std::cout << "\\end{lisp}\n";
		break;
	}

#line 740 "index.md"
 {
	static const std::string prefix {
		"!("
	};
	if (has_prefix(line, prefix)) {
		exit_two_columns();
		
#line 755 "index.md"

	std::cout << "\\begin{center}\n";
	std::cout <<
		"\\includegraphics[scale=.5]{";
	
#line 768 "index.md"

	unsigned i { prefix.size() };
	while (i < line.size() &&
		line[i] != '}' && line[i] != '.'
	) {
		std::cout << line[i];
		++i;
	}
	if (theme.size()) {
		std::cout << "-" << theme;
	}

#line 759 "index.md"
;
	std::cout << ".pdf}\n";
	std::cout << "\\end{center}\n";

#line 746 "index.md"
;
		nextline(line);
		break;
	}
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
