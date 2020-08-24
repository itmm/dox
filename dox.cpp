
#line 5 "index.md"

	
#line 19 "index.md"

	#include <iostream>
	#include <string>

#line 792 "index.md"

	#include "lazy-write.h"

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

	unsigned j { i };
	char mark { line[j] };
	int cnt { 0 };
	while (j < line.size() && line[j] == mark) {
		++cnt; ++j;
	}
	while (j < line.size() && cnt &&
			line[j] >= ' ' && (
				isalnum(line[j]) ||
				line[j] == '*' ||
				line[j] == '_' ||
				line[j] == '-' ||
				line[j] == ' '
				)
		  ) { if (line[j] == mark) { --cnt; }; ++j; }

#line 383 "index.md"

	if (! cnt) {
		
#line 393 "index.md"

	bool bold {
		i + 3 < j &&
			line[i + 1] == mark &&
			line[j - 2] == mark
	};

#line 404 "index.md"

	if (bold) {
		std::cout << "\\textbf{";
	} else {
		std::cout << "\\emph{";
	}

#line 415 "index.md"

	unsigned begin {
		bold ? i + 2 : i + 1
	};
unsigned end { bold ? j - 2 : j - 1 };
for (auto t { begin }; t < end; ++t) {
	
#line 434 "index.md"

	if (line[t] == mark) {
		std::cout << ' ';
	} else {
		std::cout << line[t];
	}

#line 421 "index.md"
;
}
std::cout << "}";

#line 446 "index.md"

	if (line[j] == ' ') {
		std::cout << '\\';
	}

#line 424 "index.md"
;
i = j - 1;
continue;

#line 385 "index.md"
;
	}

#line 355 "index.md"
;
	}

#line 547 "index.md"

	if (line[i] == '$') {
		
#line 556 "index.md"

	unsigned j { i + 1 };
	while (j < line.size() &&
		line[j] != '$'
	) { ++j; }

#line 566 "index.md"

	if (j < line.size() && line[j] == '$') {
		for (auto t { i }; t <= j; ++t) {
			std::cout << line[t];
		}
		i = j;
		continue;
	}

#line 549 "index.md"
;
	}

#line 684 "index.md"

	if (line[i] == '`') {
		
#line 693 "index.md"

	unsigned j { i + 1 };
	for (;
		j < line.size() && line[j] != '`';
		++j
	) {}

#line 704 "index.md"

	if (j < line.size() &&
		line[j] == '`'
	) {
		
#line 717 "index.md"

	std::cout << "\\hlInline{";
	for (auto t { i + 1 }; t < j; ++t) {
		
#line 656 "index.md"

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

#line 720 "index.md"
;
	}
	std::cout << "}";

#line 729 "index.md"

	if (j + 1 < line.size() &&
		line[j + 1] == ' '
	) {
		std::cout << "\\";
	}

#line 708 "index.md"
;
		i = j;
		continue;
	}

#line 686 "index.md"
;
	}

#line 342 "index.md"
;
		std::cout << line[i];
	}

#line 264 "index.md"
;
	}

#line 460 "index.md"

	enum class List_Type {
		no_list, enum_list, item_list
	} list_type { List_Type::no_list };

#line 469 "index.md"

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

#line 486 "index.md"

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

	"\\usepackage{fancyhdr}\n"
	"\\usepackage{fancyvrb}\n"

#line 80 "preamble.md"

	"\\usepackage{graphicx}\n"

#line 87 "preamble.md"

	"\\usepackage{multicol}\n"

#line 94 "preamble.md"

	"\\usepackage{mdframed}\n"

#line 101 "preamble.md"

	"\\usepackage{lisp}\n"

#line 108 "preamble.md"

	"\\pagestyle{fancy}\n"
	"\\fancypagestyle{plain}{\n"
	"\\fancyhf{}\n"

#line 117 "preamble.md"

	"\\fancyfoot[C]{{"
		"\\color{deemph}\\small"
		"$\\thepage$"
	"}}\n"

#line 127 "preamble.md"

	"\\renewcommand{\\headrulewidth}"
		"{0pt}\n"
	"\\renewcommand{\\footrulewidth}"
		"{0pt}}\n"

#line 137 "preamble.md"

	"\\title{"
		"\\color{emph}" << title <<
	"}\n"
	"\\author{" << author << "}\n"
	"\\date{" << date << "}\n"

#line 148 "preamble.md"

	"\\columnseprule.2pt\n"
	"\\renewcommand{\\columnseprulecolor}"
		"{\\color{deemph}}\n"

#line 157 "preamble.md"

	"\\begin{document}\n"

#line 164 "preamble.md"

	"\\pagecolor{background}\n"
	"\\color{normal}\n"
	"\\allsectionsfont{"
		"\\color{emph}\\mdseries"
	"}\n"

#line 175 "preamble.md"

	"\\pagestyle{plain}\n"
	"\\maketitle\n"
	"\\thispagestyle{fancy}\n"

#line 185 "preamble.md"

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
#line 504 "index.md"

	if (line == "") {
		close_list();
	}

#line 512 "index.md"
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
#line 527 "index.md"

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

#line 582 "index.md"

	if (line == "```lisp") {
		std::cout << "\\begin{lisp}\n";
		nextline(line);
		
#line 595 "index.md"

	int nr { 1 };
	while (line != end_of_file &&
		line != "```"
	) {
		
#line 611 "index.md"

	if (nr > 1) {
		std::cout << "\\\\*\n";
	}

#line 620 "index.md"

	std::cout << "$\\hlLine{" <<
		nr++ << "}";

#line 628 "index.md"

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

#line 645 "index.md"

	for (auto t { i };
		t < line.size(); ++t
	) {
		
#line 656 "index.md"

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

#line 649 "index.md"
;
	}

#line 674 "index.md"

	std::cout << "$";

#line 600 "index.md"
;
		nextline(line);
	}
	std::cout << "\n";
	nextline(line);

#line 586 "index.md"
;
		std::cout << "\\end{lisp}\n";
		break;
	}

#line 743 "index.md"
 {
	static const std::string prefix {
		"!("
	};
	if (has_prefix(line, prefix)) {
		exit_two_columns();
		
#line 758 "index.md"

	std::cout <<
		"\\centerline{\\includegraphics[scale=.5]{";
	
#line 769 "index.md"

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

#line 761 "index.md"
;
	std::cout << ".pdf}}\n";

#line 749 "index.md"
;
		nextline(line);
		break;
	}
} 
#line 798 "index.md"

	if (line == "```gv" || line == "```GV") {
		bool big { line[3] == 'G' };
		if (big) {
			exit_two_columns();
		}
		static int count { 1 };
		std::string name {
			"imgs/dot-" + std::to_string(count++)
		};
		Lazy_Write wr { name + ".dot" };
		nextline(line);
		while (line != end_of_file && line != "```") {
			wr << line + "\n";
			nextline(line);
		}
		nextline(line);
		std::cout <<
			"\\centerline{\\includegraphics[trim={1in .9in 1in .9in},clip]{";
		std::cout << name;
		if (theme.size()) {
			std::cout << "-" << theme;
		}
		std::cout << ".pdf}}\n";
		break;
	}

#line 828 "index.md"

	if (line == "```lily") {
		exit_two_columns();
		static int count { 1 };
		std::string name {
			"imgs/lily-" + std::to_string(count++)
		};
		Lazy_Write wr { name + ".ly" };
		nextline(line);
		wr << "\\include \"preamble.ly\"\n";
		while (line != end_of_file && line != "```") {
			wr << line + "\n";
			nextline(line);
		}
		nextline(line);
		std::cout <<
			"\\centerline{\\includegraphics{";
		std::cout << name;
		if (theme.size()) {
			std::cout << "-" << theme;
		}
		std::cout << ".pdf}}\n";
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
