# Dox
* generate LaTeX sources from a markdown file

```
@Def(file: dox.cpp)
	@put(includes);
	@put(main prereqs);
	int main(
		int argc,
		const char *const argv[]
	) {
		@put(main);
	}
@End(file: dox.cpp)
```
* simple main program

```
@def(includes)
	#include @s(<iostream>)
	#include @s(<string>)
@end(includes)
```
* needs libraries for string processing

## Theme selection
* `dox` can generate output with different themes
* specify theme with a command line argument

```
@def(main prereqs)
	static std::string theme {};
	static std::string prefix {};
	bool with_multi_cols { true };
	bool generate_latex { true };
	bool generate_html { false };
	bool generate_markdown { false };
@end(main prereqs)
```
* no default theme is used

```
@add(main prereqs)
	std::string after_prefix(const std::string &str, const std::string &prefix) {
		auto len { prefix.size() };
		if (str.size() > len && str.substr(0, len) == prefix) {
			return str.substr(len);
		}
		return std::string {};
	}
@end(main prereqs)
```

```
@def(main) {
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
} @end(main)
```
* may select other theme based on command line arguments

## Meta-Data
* collect information about the document

```
@add(main prereqs)
	static std::string title;
	static std::string author;
	static std::string date { "\\today" };
@end(main prereqs)
```
* `date` defaults to the LaTeX command for the current day

## Read the next line
* reading one line from standard input

```
@add(main prereqs)
	static const
		std::string end_of_file {
			"\r\n"
		};
@end(main prereqs)
```
* a special string value marks the end of file
* as the newline is stripped by the reading routine the provided string
  should never occur during normal reading

```
@add(main prereqs)
	void nextline(std::string &line) {
		if (line != end_of_file) {
			if (! std::getline(std::cin, line)) {
				line = end_of_file;
			}
		}
	}
@end(main prereqs)
```
* reads the next line into the argument
* if the end is already reached, nothing will be read

## Reading Meta-Data
* the start of the read document may contain meta-data
* every line until the first empty line is considered meta-data
* but nonetheless the meta-data is formatted as regular markdown code

```
@add(main)
	std::string line;
	nextline(line);
	@put(read metadata);
@end(main)
```
* read the first line
* and process meta-data

```
@add(main prereqs)
	bool has_prefix(
		const std::string &line,
		const std::string &prefix
	) {
		const auto &l { line };
		const auto &p { prefix };
		return l.size() >= p.size() &&
			l.substr(0, p.size()) == p;
	}
@end(main prereqs)
```
* check if a string starts with the specified prefix
* this is used a couple of times in the program

```
@def(read metadata) {
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
} @end(read metadata)
```
* the first meta-data must be the title that is provided with a lever 1
  heading

```
@add(read metadata) {
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
} @end(read metadata)
```
* the next line specifies the author

```
@add(read metadata) {
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
} @end(read metadata)
```
* the next line may specify the generation date
* if no date is provided, the program uses the current date

```
@add(read metadata)
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
@end(read metadata)
```
* all other lines until the first empty line are ignored

## Writing the preamble
* after `dox` read the meta-data it writes the LaTeX preamble

```
@add(main)
	if (generate_latex) {
		std::cout <<
			@put(preamble);
	}
	if (generate_html) {
		std::cout << "<!doctype html>\n"
			"<html><head>"
				"<meta charset=\"utf-8\"/>"
				"<title>" << title << "</title>"
			"</head><body>"
				"<h1>" << title << "</h1>";
	}
@end(main)
```
* write the preamble

```
@inc(preamble.md)
```
* preamble is defined in another document

## Handle Two-Column Style
* output can switch between one-column and two-column style

```
@add(main prereqs)
	bool in_two_columns { false };
@end(main prereqs)
```
* is the output currently in two-column style?

```
@add(main prereqs)
	void enter_two_columns() {
		if (with_multi_cols && ! in_two_columns) {
			if (generate_latex) {
				std::cout <<
					"\\begin{multicols}{2}\n";
			}
			in_two_columns = true;
		}
	}
@end(main prereqs)
```
* switch into two-column style

```
@add(main prereqs)
	void exit_two_columns() {
		if (in_two_columns) {
			if (generate_latex) {
				std::cout <<
					"\\end{multicols}\n";
			}
			in_two_columns = false;
		}
	}
@end(main prereqs)
```
* switch back into one-column style

## Process main body
* process the main body of text

```
@add(main)
	while (line != end_of_file) {
		@put(process line);
	}
	exit_two_columns();
	if (generate_latex) {
		std::cout << "\\end{document}\n";
	}
@end(main)
```
* read and process all lines
* and close the document

```
@add(main prereqs)
	void format_line(
		const std::string line
	) {
		@put(format line);
	}
@end(main prereqs)
```
* do special formatting of all the special sequences in one line of
  normal text

```
@def(process line)
	do {
		@put(process special);
		enter_two_columns();
		format_line(line);
		std::cout << "\n";
		nextline(line);
	} while (false);
@end(process line)
```
* first process some special lines
* if no special line is found do the normal processing
* in two-column style
* and read the next line

## Process section headers
* process the section and subsection headers

```
@def(process special) {
	static const std::string prefix {
		"## "
	};
	if (has_prefix(line, prefix)) {
		@put(write section);
		nextline(line);
		break;
	}
} @end(process special)
```
* process section header

```
@def(write section)
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
@end(write section)
```
* section headers are in one-column style

```
@add(process special) {
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
} @end(process special)
```
* subsections stay in the current columns style

## Handle emphasis
* text in a line can be emphasised

```
@def(format line)
	for (unsigned i { 0 };
		i < line.size(); ++i
	) {
		@put(handle format);
		std::cout << line[i];
	}
@end(format line)
```
* iterate over each char
* and process special format sequences

```
@def(handle format)
	if (
			line[i] == '*' || line[i] == '_'
	   ) {
		@put(emphasise);
	}
@end(handle format)
	```
	* emphasise following words

	```
@def(emphasise)
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
@end(emphasise)
	```
	* find end of chars to highlight

	```
@add(emphasise)
	if (! cnt) {
		@put(do emphasis);
	}
@end(emphasise)
	```
	* if start and end differ and have the same mark, it is a legal
	highlight sequence

	```
@def(do emphasis)
	bool bold {
		i + 3 < j &&
			line[i + 1] == mark &&
			line[j - 2] == mark
	};
@end(do emphasis)
	```
	* if two marks are at the beginning and ending use bold highlight

	```
@add(do emphasis)
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
@end(do emphasis)
	```
	* write bold or italics tag

	```
@add(do emphasis)
	unsigned begin {
		bold ? i + 2 : i + 1
	};
unsigned end { bold ? j - 2 : j - 1 };
for (auto t { begin }; t < end; ++t) {
	@put(emphasis loop);
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
@put(add padding);
i = j - 1;
continue;
@end(do emphasis)
	```
	* write the emphasised characters
	* close tag
	* and skip over the processed characters

	```
@def(emphasis loop)
	if (line[t] == mark) {
		std::cout << ' ';
	} else {
		std::cout << line[t];
	}
@end(emphasis loop)
```
* replace the marking char with spaces
* and copy all other chars

```
@def(add padding)
	if (line[j] == ' ') {
		if (generate_latex) {
			std::cout << '\\';
		}
	}
@end(add padding)
```
* if a space follows the emphasise sequence
* it must be padded
* otherwise it is swallowed by TeX

## Handle lists
* format lists

```
@add(main prereqs)
	enum class List_Type {
		no_list, enum_list, item_list
	} list_type { List_Type::no_list };
@end(main prereqs)
```
* is the output currently in a list item

```
@add(main prereqs)
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
@end(main prereqs)
```

```
@add(main prereqs)
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
@end(main prereqs)
```

```
@add(process special)
	if (line == "") {
		close_list();
	}
@end(process special)
```

```
@add(process special) {
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
} @end(process special)
```

```
@add(process special)
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
@end(process special)
```
* subsections stay in the current columns style

## Handle math
* verbose copy math blocks

```
@add(handle format)
	if (line[i] == '$') {
		@put(math);
	}
@end(handle format)
```
* start of math mode

```
@def(math)
	unsigned j { i + 1 };
	while (j < line.size() &&
		line[j] != '$'
	) { ++j; }
@end(math)
```
* find end of math mode

```
@add(math)
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
@end(math)
```
* directly copy math

## Handle Source Code
* highlight source code

```
@add(process special)
	if (line == "```lisp") {
		std::cout << "\\begin{lisp}\n";
		nextline(line);
		@put(process lisp lines);
		std::cout << "\\end{lisp}\n";
		break;
	}
@end(process special)
```
* parse LISP block

```
@def(process lisp lines)
	int nr { 1 };
	while (line != end_of_file &&
		line != "```"
	) {
		@put(process lisp line);
		nextline(line);
	}
	std::cout << "\n";
	nextline(line);
@end(process lisp lines)
```
* process each line
* close last line with a newline

```
@def(process lisp line)
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
@end(process lisp line)
```
* terminate previous line correctly

```
@add(process lisp line)
	if (generate_latex) {
		std::cout << "$\\hlLine{" <<
			nr << "}";
	}
	if (generate_html) {
		std::cout << "<span class=\"line\">" << nr << "</span>";
	}
	++nr;
@end(process lisp line)
```
* enter math mode and write line number

```
@add(process lisp line)
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
@end(process lisp line)
```
* skip over tabs
* and add matching indent

```
@add(process lisp line)
	for (auto t { i };
		t < line.size(); ++t
	) {
		@mul(copy code);
	}
@end(process lisp line)
```
* copy code

```
@def(copy code)
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
@end(copy code)
```
* copy code
* but escape spaces
* special treatment to separate hyphens from minus signs

```
@add(process lisp line)
	if (generate_latex) {
		std::cout << "$";
	}
@end(process lisp line)
```
* leave math mode

## Handle inline code
* display an inline code fragment

```
@add(handle format)
	if (line[i] == '`') {
		@put(inline code);
	}
@end(handle format)
```
* parse inline code fragment

```
@def(inline code)
	unsigned j { i + 1 };
	for (;
		j < line.size() && line[j] != '`';
		++j
	) {}
@end(inline code)
```
* find end of fragment

```
@add(inline code)
	if (j < line.size() &&
		line[j] == '`'
	) {
		@put(do inline code);
		i = j;
		continue;
	}
@end(inline code)
```
* process valid fragment

```
@def(do inline code)
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
		@mul(copy code);
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
@end(do inline code)
```
* copy code fragment
* but escape spaces

```
@add(do inline code)
	if (j + 1 < line.size() &&
		line[j + 1] == ' '
	) {
		if (generate_latex) {
			std::cout << "\\";
		}
	}
@end(do inline code)
```
* pad trailing space

## Include Graphics
* include PDF graphics in the correct theme

```
@add(process special) {
	static const std::string prefix {
		"!("
	};
	if (has_prefix(line, prefix)) {
		exit_two_columns();
		@put(include graphics);
		nextline(line);
		break;
	}
} @end(process special)
```
* parse image

```
@def(include graphics)
	if (generate_latex) {
		std::cout <<
			"\\centerline{\\includegraphics[scale=.5]{";
		@mul(copy themed graphics name);
		std::cout << ".pdf}}\n";
	}
	if (generate_markdown) {
		std::cout << line << '\n';
	}
	if (generate_html) {
		std::cout << "<img src=\"";
		@mul(copy themed graphics name);
		std::cout << ".svg\"></img>\n";
	}
@end(include graphics)
```
* include LaTeX statements to load graphic
* only PDF graphics are supported

```
@def(copy themed graphics name)
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
@end(copy themed graphics name)
```
* copy name until the first extension
* add theme name if present

## Handle Graphviz Code

```
@inc(lazy-write/lazy.md)
```

```
@add(includes)
	#include "lazy-write.h"
@end(includes)
```

```
@add(process special)
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
@end(process special)
```

```
@add(process special)
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
@end(process special)
```

```
@add(main)
	if (generate_html) {
		std::cout << "</body></html>\n";
	}
@end(main)
```
