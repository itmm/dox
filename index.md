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
	static std::string date;
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

