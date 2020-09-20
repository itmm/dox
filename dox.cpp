
#line 5 "index.md"

	
#line 19 "index.md"

	#include <iostream>
	#include <string>

#line 814 "index.md"

	#include "lazy-write.h"

#line 6 "index.md"
;
	
#line 31 "index.md"

	static std::string theme {};
	static std::string prefix {};
	bool with_multi_cols { true };

#line 40 "index.md"

	std::string after_prefix(const std::string &str, const std::string &prefix) {
		auto len { prefix.size() };
		if (str.size() > len && str.substr(0, len) == prefix) {
			return str.substr(len);
		}
		return std::string {};
	}

#line 81 "index.md"

	static std::string title;
	static std::string author;
	static std::string date { "\\today" };

#line 93 "index.md"

	static const
		std::string end_of_file {
			"\r\n"
		};

#line 105 "index.md"

	void nextline(std::string &line) {
		if (line != end_of_file) {
			if (! std::getline(std::cin, line)) {
				line = end_of_file;
			}
		}
	}

#line 134 "index.md"

	bool has_prefix(
		const std::string &line,
		const std::string &prefix
	) {
		const auto &l { line };
		const auto &p { prefix };
		return l.size() >= p.size() &&
			l.substr(0, p.size()) == p;
	}

#line 234 "index.md"

	bool in_two_columns { false };

#line 241 "index.md"

	void enter_two_columns() {
		if (with_multi_cols && ! in_two_columns) {
			std::cout <<
				"\\begin{multicols}{2}\n";
			in_two_columns = true;
		}
	}

#line 254 "index.md"

	void exit_two_columns() {
		if (in_two_columns) {
			std::cout <<
				"\\end{multicols}\n";
			in_two_columns = false;
		}
	}

#line 282 "index.md"

	void format_line(
		const std::string line
	) {
		
#line 360 "index.md"

	for (unsigned i { 0 };
		i < line.size(); ++i
	) {
		
#line 373 "index.md"

	if (
			line[i] == '*' || line[i] == '_'
	   ) {
		
#line 384 "index.md"

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

#line 405 "index.md"

	if (! cnt) {
		
#line 415 "index.md"

	bool bold {
		i + 3 < j &&
			line[i + 1] == mark &&
			line[j - 2] == mark
	};

#line 426 "index.md"

	if (bold) {
		std::cout << "\\textbf{";
	} else {
		std::cout << "\\emph{";
	}

#line 437 "index.md"

	unsigned begin {
		bold ? i + 2 : i + 1
	};
unsigned end { bold ? j - 2 : j - 1 };
for (auto t { begin }; t < end; ++t) {
	
#line 456 "index.md"

	if (line[t] == mark) {
		std::cout << ' ';
	} else {
		std::cout << line[t];
	}

#line 443 "index.md"
;
}
std::cout << "}";

#line 468 "index.md"

	if (line[j] == ' ') {
		std::cout << '\\';
	}

#line 446 "index.md"
;
i = j - 1;
continue;

#line 407 "index.md"
;
	}

#line 377 "index.md"
;
	}

#line 569 "index.md"

	if (line[i] == '$') {
		
#line 578 "index.md"

	unsigned j { i + 1 };
	while (j < line.size() &&
		line[j] != '$'
	) { ++j; }

#line 588 "index.md"

	if (j < line.size() && line[j] == '$') {
		for (auto t { i }; t <= j; ++t) {
			std::cout << line[t];
		}
		i = j;
		continue;
	}

#line 571 "index.md"
;
	}

#line 706 "index.md"

	if (line[i] == '`') {
		
#line 715 "index.md"

	unsigned j { i + 1 };
	for (;
		j < line.size() && line[j] != '`';
		++j
	) {}

#line 726 "index.md"

	if (j < line.size() &&
		line[j] == '`'
	) {
		
#line 739 "index.md"

	std::cout << "\\hlInline{";
	for (auto t { i + 1 }; t < j; ++t) {
		
#line 678 "index.md"

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

#line 742 "index.md"
;
	}
	std::cout << "}";

#line 751 "index.md"

	if (j + 1 < line.size() &&
		line[j + 1] == ' '
	) {
		std::cout << "\\";
	}

#line 730 "index.md"
;
		i = j;
		continue;
	}

#line 708 "index.md"
;
	}

#line 364 "index.md"
;
		std::cout << line[i];
	}

#line 286 "index.md"
;
	}

#line 482 "index.md"

	enum class List_Type {
		no_list, enum_list, item_list
	} list_type { List_Type::no_list };

#line 491 "index.md"

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

#line 508 "index.md"

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
		
#line 52 "index.md"
 {
	static const std::string theme_pre {
		"--theme="
	};
	static const std::string prefix_pre {
		"--prefix="
	};
	for (int i { 1 }; i < argc; ++i) {
		std::string arg { argv[i] };
		{
			auto val { after_prefix(arg, theme_pre) };
			if (! val.empty()) { theme = val; }
		}
		{
			auto val { after_prefix(arg, prefix_pre) };
			if (! val.empty()) { prefix = val; }
		}
		if (arg == "--single-col") {
			with_multi_cols = false;
		}
	}
} 
#line 124 "index.md"

	std::string line;
	nextline(line);
	
#line 150 "index.md"
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
#line 168 "index.md"
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
#line 185 "index.md"
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
#line 201 "index.md"

	while (
		line != end_of_file && line.size()
	) {
		std::cerr <<
			"ignoring meta line: " <<
			line << "\n";
		nextline(line);
	}

#line 127 "index.md"
;

#line 218 "index.md"

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
	) << "{" << prefix << "solarized}\n"

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

	"\\usepackage{" << prefix << "lisp}\n"

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


#line 220 "index.md"
;

#line 270 "index.md"

	while (line != end_of_file) {
		
#line 294 "index.md"

	do {
		
#line 313 "index.md"
 {
	static const std::string prefix {
		"## "
	};
	if (has_prefix(line, prefix)) {
		
#line 327 "index.md"

	exit_two_columns();
	std::cout << "\\section{";
	format_line(line.substr(
		prefix.size()
	));
	std::cout << "}\n";

#line 318 "index.md"
;
		nextline(line);
		break;
	}
} 
#line 339 "index.md"
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
#line 526 "index.md"

	if (line == "") {
		close_list();
	}

#line 534 "index.md"
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
#line 549 "index.md"

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

#line 604 "index.md"

	if (line == "```lisp") {
		std::cout << "\\begin{lisp}\n";
		nextline(line);
		
#line 617 "index.md"

	int nr { 1 };
	while (line != end_of_file &&
		line != "```"
	) {
		
#line 633 "index.md"

	if (nr > 1) {
		std::cout << "\\\\*\n";
	}

#line 642 "index.md"

	std::cout << "$\\hlLine{" <<
		nr++ << "}";

#line 650 "index.md"

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

#line 667 "index.md"

	for (auto t { i };
		t < line.size(); ++t
	) {
		
#line 678 "index.md"

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

#line 671 "index.md"
;
	}

#line 696 "index.md"

	std::cout << "$";

#line 622 "index.md"
;
		nextline(line);
	}
	std::cout << "\n";
	nextline(line);

#line 608 "index.md"
;
		std::cout << "\\end{lisp}\n";
		break;
	}

#line 765 "index.md"
 {
	static const std::string prefix {
		"!("
	};
	if (has_prefix(line, prefix)) {
		exit_two_columns();
		
#line 780 "index.md"

	std::cout <<
		"\\centerline{\\includegraphics[scale=.5]{";
	
#line 791 "index.md"

	auto i { prefix.size() };
	while (i < line.size() &&
		line[i] != '}' && line[i] != '.'
	) {
		std::cout << line[i];
		++i;
	}
	if (theme.size()) {
		std::cout << "-" << theme;
	}

#line 783 "index.md"
;
	std::cout << ".pdf}}\n";

#line 771 "index.md"
;
		nextline(line);
		break;
	}
} 
#line 820 "index.md"

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

#line 850 "index.md"

	if (line == "```lily") {
		exit_two_columns();
		static int count { 1 };
		std::string name {
			"imgs/lily-" + std::to_string(count++)
		};
		std::string themed_name { name };
		if (theme.size()) {
			themed_name += "-" + theme;
		}
		Lazy_Write wr { themed_name + ".ly" };
		nextline(line);
		wr << "\\include \"" << prefix << "preamble";
		if (theme.size()) {
			wr << "-" << theme;
		}
		wr << ".ly\"\n";
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

#line 296 "index.md"
;
		enter_two_columns();
		format_line(line);
		std::cout << "\n";
		nextline(line);
	} while (false);

#line 272 "index.md"
;
	}
	exit_two_columns();
	std::cout << "\\end{document}\n";

#line 12 "index.md"
;
	}
