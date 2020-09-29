
#line 5 "index.md"

	
#line 19 "index.md"

	#include <iostream>
	#include <string>

#line 1035 "index.md"

	#include "lazy-write.h"

#line 6 "index.md"
;
	
#line 31 "index.md"

	static std::string theme {};
	static std::string prefix {};
	bool with_multi_cols { true };
	bool generate_latex { true };
	bool generate_html { false };
	bool generate_markdown { false };

#line 43 "index.md"

	std::string after_prefix(const std::string &str, const std::string &prefix) {
		auto len { prefix.size() };
		if (str.size() > len && str.substr(0, len) == prefix) {
			return str.substr(len);
		}
		return std::string {};
	}

#line 103 "index.md"

	static std::string title;
	static std::string author;
	static std::string date { "\\today" };

#line 115 "index.md"

	static const
		std::string end_of_file {
			"\r\n"
		};

#line 127 "index.md"

	void nextline(std::string &line) {
		if (line != end_of_file) {
			if (! std::getline(std::cin, line)) {
				line = end_of_file;
			}
		}
	}

#line 156 "index.md"

	bool has_prefix(
		const std::string &line,
		const std::string &prefix
	) {
		const auto &l { line };
		const auto &p { prefix };
		return l.size() >= p.size() &&
			l.substr(0, p.size()) == p;
	}

#line 278 "index.md"

	bool in_two_columns { false };

#line 285 "index.md"

	void enter_two_columns() {
		if (with_multi_cols && ! in_two_columns) {
			if (generate_latex) {
				std::cout <<
					"\\begin{multicols}{2}\n";
			}
			in_two_columns = true;
		}
	}

#line 300 "index.md"

	void exit_two_columns() {
		if (in_two_columns) {
			if (generate_latex) {
				std::cout <<
					"\\end{multicols}\n";
			}
			in_two_columns = false;
		}
	}

#line 332 "index.md"

	void format_line(
		const std::string line
	) {
		
#line 434 "index.md"

	for (unsigned i { 0 };
		i < line.size(); ++i
	) {
		
#line 447 "index.md"

	if (
			line[i] == '*' || line[i] == '_'
	   ) {
		
#line 458 "index.md"

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

#line 479 "index.md"

	if (! cnt) {
		
#line 489 "index.md"

	bool bold {
		i + 3 < j &&
			line[i + 1] == mark &&
			line[j - 2] == mark
	};

#line 500 "index.md"

	if (bold) {
		if (generate_latex) {
			std::cout << "\\textbf{";
		}
		if (generate_markdown) {
			std::cout << mark << mark;
		}
		if (generate_html) {
			std::cout << "<b>";
		}
	} else {
		if (generate_latex) {
			std::cout << "\\emph{";
		}
		if (generate_markdown) {
			std::cout << mark;
		}
		if (generate_html) {
			std::cout << "<i>";
		}
	}

#line 527 "index.md"

	unsigned begin {
		bold ? i + 2 : i + 1
	};
unsigned end { bold ? j - 2 : j - 1 };
for (auto t { begin }; t < end; ++t) {
	
#line 558 "index.md"

	if (line[t] == mark) {
		std::cout << ' ';
	} else {
		std::cout << line[t];
	}

#line 533 "index.md"
;
}
if (generate_latex) {
	std::cout << "}";
}
if (generate_markdown) {
	if (bold) {
		std::cout << mark << mark;
	} else {
		std::cout << mark;
	}
}
if (generate_html) {
	std::cout << (bold ? "</b>" : "</i>");
}

#line 570 "index.md"

	if (line[j] == ' ') {
		if (generate_latex) {
			std::cout << '\\';
		}
	}

#line 548 "index.md"
;
i = j - 1;
continue;

#line 481 "index.md"
;
	}

#line 451 "index.md"
;
	}

#line 714 "index.md"

	if (line[i] == '$') {
		
#line 723 "index.md"

	unsigned j { i + 1 };
	while (j < line.size() &&
		line[j] != '$'
	) { ++j; }

#line 733 "index.md"

	if (j < line.size() && line[j] == '$') {
		if (generate_latex) {
			for (auto t { i }; t <= j; ++t) {
				std::cout << line[t];
			}
		}
		if (generate_markdown) {
			for (auto t { i + 1 }; t < j; ++t) {
				std::cout << line[t];
			}
		}
		if (generate_html) {
			for (auto t { i + 1 }; t < j; ++t) {
				std::cout << line[t];
			}
		}
		i = j;
		continue;
	}

#line 716 "index.md"
;
	}

#line 899 "index.md"

	if (line[i] == '`') {
		
#line 908 "index.md"

	unsigned j { i + 1 };
	for (;
		j < line.size() && line[j] != '`';
		++j
	) {}

#line 919 "index.md"

	if (j < line.size() &&
		line[j] == '`'
	) {
		
#line 932 "index.md"

	if (generate_latex) {
		std::cout << "\\hlInline{";
	}
	if (generate_markdown) {
		std::cout << '`';
	}
	if (generate_html) {
		std::cout << "<code>";
	}
	for (auto t { i + 1 }; t < j; ++t) {
		
#line 859 "index.md"

	if (line[t] == ' ') {
		if (generate_latex) {
			std::cout << "\\";
		}
	}
	if (line[t] == '-' && t > 0 &&
		isalpha(line[t - 1])
	) {
		if (generate_latex) {
			std::cout << "{\\text -}";
		}
		if (generate_markdown) {
			std::cout << line[t];
		}
		if (generate_html) {
			std::cout << line[t];
		}
	} else {
		std::cout << line[t];
	}

#line 943 "index.md"
;
	}
	if (generate_latex) {
		std::cout << "}";
	}
	if (generate_markdown) {
		std::cout << '`';
	}
	if (generate_html) {
		std::cout << "</code>";
	}

#line 960 "index.md"

	if (j + 1 < line.size() &&
		line[j + 1] == ' '
	) {
		if (generate_latex) {
			std::cout << "\\";
		}
	}

#line 923 "index.md"
;
		i = j;
		continue;
	}

#line 901 "index.md"
;
	}

#line 438 "index.md"
;
		std::cout << line[i];
	}

#line 336 "index.md"
;
	}

#line 586 "index.md"

	enum class List_Type {
		no_list, enum_list, item_list
	} list_type { List_Type::no_list };

#line 595 "index.md"

	int item_counter { 0 };

	void open_list(bool enumerate) {
		bool already_open { true };
		if (list_type == List_Type::no_list) {
			if (enumerate) {
				if (generate_latex) {
					std::cout << "\\begin{enumerate}\n";
				}
				if (generate_html) {
					std::cout << "<ol>\n";
				}
				list_type = List_Type::enum_list;
				item_counter = 0;
			} else {
				if (generate_latex) {
					std::cout << "\\begin{itemize}\n";
				}
				if (generate_html) {
					std::cout << "<ul>\n";
				}
				list_type = List_Type::item_list;
			}
			already_open = false;
		}
		if (generate_latex) {
			std::cout << "\\item ";
		}
		if (generate_markdown) {
			if (list_type == List_Type::enum_list) {
				std::cout << ++item_counter << ". ";
			}
			if (list_type == List_Type::item_list) {
				std::cout << "* ";
			}
		}
		if (generate_html) {
			if (already_open) {
				std::cout << "</li>";
			}
			std::cout << "<li>";
		}
	}

#line 643 "index.md"

	void close_list() {
		switch (list_type) {
			case List_Type::no_list:
				break;
			case List_Type::enum_list:
				if (generate_latex) {
					std::cout << "\\end{enumerate}\n";
				}
				if (generate_html) {
					std::cout << "</li></ol>";
				}
				break;
			case List_Type::item_list:
				if (generate_latex) {
					std::cout << "\\end{itemize}\n";
				}
				if (generate_html) {
					std::cout << "</li></ol>";
				}
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
		
#line 55 "index.md"
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
			generate_latex = true;
			generate_html = false;
			generate_markdown = false;
		}
		if (arg == "--two-cols") {
			with_multi_cols = true;
			generate_latex = true;
			generate_html = false;
			generate_markdown = false;
		}
		if (arg == "--markdown") {
			generate_latex = false;
			generate_html = false;
			generate_markdown = true;
		}
		if (arg == "--html") {
			generate_latex = false;
			generate_html = true;
			generate_markdown = false;
		}
	}
} 
#line 146 "index.md"

	std::string line;
	nextline(line);
	
#line 172 "index.md"
 {
	static const std::string prefix {
		"# "
	};
	if (has_prefix(line, prefix)) {
		title = line.substr(
			prefix.size()
		);
		if (generate_markdown) {
			std::cout << line << '\n';
		}
		nextline(line);
	} else {
		std::cerr << "no title\n";
	}
} 
#line 193 "index.md"
 {
	static const std::string prefix {
		"* author: "
	};
	if (has_prefix(line, prefix)) {
		author = line.substr(
			prefix.size()
		);
		if (generate_markdown) {
			std::cout << line << '\n';
		}
		nextline(line);
	} else {
		std::cerr << "no author\n";
	}
} 
#line 213 "index.md"
 {
	static const std::string prefix {
		"* date: "
	};
	if (has_prefix(line, prefix)) {
		date = line.substr(
			prefix.size()
		);
		if (generate_markdown) {
			std::cout << line << '\n';
		}
		nextline(line);
	}
} 
#line 232 "index.md"

	while (
		line != end_of_file && line.size()
	) {
		std::cerr <<
			"unknown meta line: " <<
			line << "\n";
		if (generate_markdown) {
			std::cout << line << '\n';
		}
		nextline(line);
	}

#line 149 "index.md"
;

#line 252 "index.md"

	if (generate_latex) {
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

	"\\fancyfoot[C]\x7b\x7b"
		"\\color{deemph}\\small"
		"$\\thepage$"
	"\x7d\x7d\n"

#line 129 "preamble.md"

	"\\renewcommand{\\headrulewidth}"
		"{0pt}\n"
	"\\renewcommand{\\footrulewidth}"
		"{0pt}}\n"

#line 139 "preamble.md"

	"\\title{"
		"\\color{emph}" << title <<
	"}\n"
	"\\author{" << author << "}\n"
	"\\date{" << date << "}\n"

#line 150 "preamble.md"

	"\\columnseprule.2pt\n"
	"\\renewcommand{\\columnseprulecolor}"
		"{\\color{deemph}}\n"

#line 159 "preamble.md"

	"\\begin{document}\n"

#line 166 "preamble.md"

	"\\pagecolor{background}\n"
	"\\color{normal}\n"
	"\\allsectionsfont{"
		"\\color{emph}\\mdseries"
	"}\n"

#line 177 "preamble.md"

	"\\pagestyle{plain}\n"
	"\\maketitle\n"
	"\\thispagestyle{fancy}\n"

#line 187 "preamble.md"

	"\\surroundwithmdframed["
		"backgroundcolor=codebackground,"
		"fontcolor=normal,"
		"hidealllines=true"
	"]{Verbatim}\n";

#line 6 "preamble.md"


#line 255 "index.md"
;
	}
	if (generate_html) {
		std::cout << "<!doctype html>\n"
			"<html><head>"
				"<meta charset=\"utf-8\"/>"
				"<title>" << title << "</title>"
			"</head><body>"
				"<h1>" << title << "</h1>";
	}

#line 318 "index.md"

	while (line != end_of_file) {
		
#line 344 "index.md"

	do {
		
#line 363 "index.md"
 {
	static const std::string prefix {
		"## "
	};
	if (has_prefix(line, prefix)) {
		
#line 377 "index.md"

	exit_two_columns();
	if (generate_latex) {
		std::cout << "\\section{";
		format_line(line.substr(
			prefix.size()
		));
		std::cout << "}\n";
	}
	if (generate_markdown) {
		std::cout << line << '\n';
	}
	if (generate_html) {
		std::cout << "<h2>";
		format_line(line.substr(
			prefix.size()
		));
		std::cout << "</h2>\n";
	}

#line 368 "index.md"
;
		nextline(line);
		break;
	}
} 
#line 401 "index.md"
 {
	static const std::string prefix {
		"### "
	};
	if (has_prefix(line, prefix)) {
		if (generate_latex) {
			std::cout << "\\subsection{";
			format_line(line.substr(
				prefix.size()
			));
			std::cout << "}\n";
		}
		if (generate_markdown) {
			std::cout << line << '\n';
		}
		if (generate_html) {
			std::cout << "<h3>";
			format_line(line.substr(
				prefix.size()
			));
			std::cout << "</h3>\n";
		}
		nextline(line);
		break;
	}
} 
#line 671 "index.md"

	if (line == "") {
		close_list();
	}

#line 679 "index.md"
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
#line 694 "index.md"

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

#line 761 "index.md"

	if (line == "```lisp") {
		std::cout << "\\begin{lisp}\n";
		nextline(line);
		
#line 774 "index.md"

	int nr { 1 };
	while (line != end_of_file &&
		line != "```"
	) {
		
#line 790 "index.md"

	if (nr > 1) {
		if (generate_latex) {
			std::cout << "\\\\*\n";
		}
		if (generate_markdown) {
			std::cout << '\n';
		}
		if (generate_html) {
			std::cout << "<br/>\n";
		}
	}

#line 807 "index.md"

	if (generate_latex) {
		std::cout << "$\\hlLine{" <<
			nr << "}";
	}
	if (generate_html) {
		std::cout << "<span class=\"line\">" << nr << "</span>";
	}
	++nr;

#line 821 "index.md"

	unsigned i { 0 };
	for (;
		i < line.size() &&
			line[i] == '\t';
		++i
	) {}
	if (i) {
		if (generate_latex) {
			std::cout << "\\hlIndent{" <<
				i << "}";
		}
		if (generate_markdown) {
			for (auto j { i }; j > 0; --j) {
				std::cout << '\t';
			}
		}
		if (generate_html) {
			std::cout << "<span class=\"indent_" << i << "\"></span>";
		}
	}

#line 848 "index.md"

	for (auto t { i };
		t < line.size(); ++t
	) {
		
#line 859 "index.md"

	if (line[t] == ' ') {
		if (generate_latex) {
			std::cout << "\\";
		}
	}
	if (line[t] == '-' && t > 0 &&
		isalpha(line[t - 1])
	) {
		if (generate_latex) {
			std::cout << "{\\text -}";
		}
		if (generate_markdown) {
			std::cout << line[t];
		}
		if (generate_html) {
			std::cout << line[t];
		}
	} else {
		std::cout << line[t];
	}

#line 852 "index.md"
;
	}

#line 887 "index.md"

	if (generate_latex) {
		std::cout << "$";
	}

#line 779 "index.md"
;
		nextline(line);
	}
	std::cout << "\n";
	nextline(line);

#line 765 "index.md"
;
		std::cout << "\\end{lisp}\n";
		break;
	}

#line 976 "index.md"
 {
	static const std::string prefix {
		"!("
	};
	if (has_prefix(line, prefix)) {
		exit_two_columns();
		
#line 991 "index.md"

	if (generate_latex) {
		std::cout <<
			"\\centerline{\\includegraphics[scale=.5]{";
		
#line 1012 "index.md"

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

#line 995 "index.md"
;
		std::cout << ".pdf}}\n";
	}
	if (generate_markdown) {
		std::cout << line << '\n';
	}
	if (generate_html) {
		std::cout << "<img src=\"";
		
#line 1012 "index.md"

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

#line 1003 "index.md"
;
		std::cout << ".svg\"></img>\n";
	}

#line 982 "index.md"
;
		nextline(line);
		break;
	}
} 
#line 1041 "index.md"

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
		if (generate_latex) {
			std::cout <<
				"\\centerline{\\includegraphics[trim={1in .9in 1in .9in},clip]{";
			std::cout << name;
			if (theme.size()) {
				std::cout << "-" << theme;
			}
			std::cout << ".pdf}}\n";
		}
		if (generate_markdown) {
			std::cout << "!(";
			std::cout << name;
			if (theme.size()) {
				std::cout << "-" << theme;
			}
			std::cout << ".svg)\n";
		}
		if (generate_html) {
			std::cout << "<img src=\"";
			std::cout << name;
			if (theme.size()) {
				std::cout << "-" << theme;
			}
			std::cout << ".svg\"></img>\n";
		}
		break;
	}

#line 1089 "index.md"

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
		if (generate_latex) {
			std::cout <<
				"\\centerline{\\includegraphics{";
			std::cout << themed_name;
			std::cout << ".pdf}}\n";
		}
		if (generate_markdown) {
			std::cout << "!(";
			std::cout << themed_name;
			std::cout << ".svg)\n";
		}
		if (generate_html) {
			std::cout << "<img src=\"";
			std::cout << themed_name;
			std::cout << ".svg\"></img>\n";
		}
		break;
	}

#line 346 "index.md"
;
		enter_two_columns();
		format_line(line);
		std::cout << "\n";
		nextline(line);
	} while (false);

#line 320 "index.md"
;
	}
	exit_two_columns();
	if (generate_latex) {
		std::cout << "\\end{document}\n";
	}

#line 1134 "index.md"

	if (generate_html) {
		std::cout << "</body></html>\n";
	}

#line 12 "index.md"
;
	}
