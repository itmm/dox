
#line 5 "index.md"

	
#line 17 "index.md"

	#include <iostream>
	#include <string>

#line 6 "index.md"
;
	
#line 24 "index.md"

	static std::string title;
	static std::string author;
	static std::string date;

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

#line 50 "index.md"
;

#line 11 "index.md"
;
	}
