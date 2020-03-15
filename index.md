# Dox
* generate LaTeX sources from a markdown file

```
@Def(file: dox.cpp)
	@put(includes);
	@put(main prereqs);
	int main(
		int argc, const char *const argv[]
	) {
		@put(main);
	}
@End(file: dox.cpp)
```

```
@def(includes)
	#include <iostream>
	#include <string>
@end(includes)
```

```
@def(main prereqs)
	static std::string title;
	static std::string author;
	static std::string date { "\\today" };
@end(main prereqs)
```

```
@add(main prereqs)
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
@end(main prereqs)
```

```
@def(main)
	std::string line;
	nextline(line);
	@put(read metadata);
@end(main)
```

```
@def(read metadata)
	if (line.size() >= 2 && line[0] == '#' && line[1] == ' ') {
		title = line.substr(2);
		nextline(line);
	} else {
		std::cerr << "no title\n";
	}
@end(read metadata)
```

```
@add(main prereqs)
	bool has_prefix(const std::string &line, const std::string &prefix) {
		return line.size() >= prefix.size() &&
			line.substr(0, prefix.size()) == prefix;
	}
@end(main prereqs)
```

```
@add(read metadata)
	if (has_prefix(line, "* author: ")) {
		author = line.substr(10);
		nextline(line);
	} else {
		std::cerr << "no author\n";
	}
@end(read metadata)
```

```
@add(read metadata)
	if (has_prefix(line, "* date: ")) {
		date = line.substr(8);
		nextline(line);
	}
@end(read metadata)
```

```
@add(read metadata)
	while (line.size()) {
		std::cerr << "ignoring meta line: " << line << "\n";
		nextline(line);
	}
@end(read metadata)
```

```
@add(read metadata)
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
@end(read metadata)
```

```
@add(main prereqs)
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
@end(main prereqs)
```

```
@add(main)
	while (line != end_of_file) {
		@put(process line);
	}
	exit_two_columns();
	std::cout << "\\end{document}\n";
@end(main)
```

```
@def(process line)
	do {
		@put(process special);
		std::cout << line << "\n";
		nextline(line);
	} while (false);
@end(process line)
```

```
@def(process special)
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
@end(process special)
```

