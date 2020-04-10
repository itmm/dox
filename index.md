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
	static std::string theme { "none" };
@end(main prereqs)
```
* current theme defaults to `"none"`

```
@def(main) {
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
			"ignoring meta line: " <<
			line << "\n";
		nextline(line);
	}
@end(read metadata)
```
* all other lines until the first empty line are ignored

## Writing the preamble
* after `dox` read the meta-data it writes the LaTeX preamble

```
@add(main)
	std::cout <<
		@put(preamble);
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
		if (! in_two_columns) {
			std::cout <<
				"\\begin{multicols}{2}\n";
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
			std::cout <<
				"\\end{multicols}\n";
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
	std::cout << "\\end{document}\n";
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
	std::cout << "\\section{";
	format_line(line.substr(
		prefix.size()
	));
	std::cout << "}\n";
@end(write section)
```
* section headers are in one-column style

```
@add(process special) {
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
@end(emphasise)
```
* find end of chars to highlight

```
@add(emphasise)
	if (i + 1 < j &&
		line[j - 1] == mark
	) {
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
		std::cout << "\\textbf{";
	} else {
		std::cout << "\\emph{";
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
	std::cout << "}";
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
		std::cout << '\\';
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
@end(main prereqs)
```

```
@add(main prereqs)
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
		for (auto t { i }; t <= j; ++t) {
			std::cout << line[t];
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
		int nr { 1 };
		while (line != end_of_file && line != "```") {
			std::cout << "$\\hlLine{" << nr++ << "}";
			unsigned indent { 0 };
			unsigned i { 0 };
			while (i < line.size() && line[i] == '\t') { ++i; ++indent; }
			if (indent) {
				std::cout << "\\hlIndent{" << indent << "}";
			}
			for (; i < line.size(); ++i) {
				if (line[i] == ' ') {
					std::cout << "\\";
				}
				std::cout << line[i];
			}
			std::cout << "$";
			nextline(line);
			if (line == end_of_file || line == "```") {
				std::cout << "\n";
				break;
			}
			std::cout << "\\\\*\n";
		}
		nextline(line);
		std::cout << "\\end{lisp}\n";
		break;
	}
@end(process special)
```

## Handle inline code

```
@add(handle format)
	if (line[i] == '`') {
		unsigned j { i + 1 };
		while (j < line.size() &&
			line[j] != '`'
		) { ++j; }
		if (j < line.size() && line[j] == '`') {
			std::cout << "\\hlInline{";
			for (auto t { i + 1 }; t < j; ++t) {
				if (line[t] == ' ') {
					std::cout << "\\";
				}
				std::cout << line[t];
			}
			std::cout << "}";
			if (j + 1 < line.size() && line[j + 1] == ' ') {
				std::cout << "\\";
			}
			i = j;
			continue;
		}
	}
@end(handle format)
```
