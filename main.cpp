
#line 59 "lazy-write/index.md"

	#include "lazy-write.h"
	#include <cassert>
	
#line 80 "lazy-write/index.md"

	
#line 99 "lazy-write/index.md"

	void lazy_write(
		fs::path path,
		const std::string &content
	) {
		std::string p { path.string() };
		{
			Lazy_Write lw { p };
			lw << content;
		}
		assert(fs::file_size(path) ==
			content.size());
		std::ifstream in { p };
		using it = std::istreambuf_iterator<char>;
		std::string got {
			it { in }, it { }
		};
		assert(got == content);
	}

#line 81 "lazy-write/index.md"
;

#line 62 "lazy-write/index.md"
;
	int main() {
		
#line 122 "lazy-write/index.md"
 {
	fs::path p { "a.tmp" };
	lazy_write(p, "");
	fs::remove(p);
} 
#line 240 "lazy-write/index.md"
 {
	fs::path p { "a.tmp" };
	lazy_write(p, "abc");
	fs::remove(p);
} 
#line 248 "lazy-write/index.md"
 {
	fs::path p { "a.tmp" };
	lazy_write(p, "abc");
	lazy_write(p, "");
	fs::remove(p);
} 
#line 257 "lazy-write/index.md"
 {
	fs::path p { "a.tmp" };
	lazy_write(p, "");
	lazy_write(p, "abc");
	fs::remove(p);
} 
#line 266 "lazy-write/index.md"
 {
	fs::path p { "a.tmp" };
	lazy_write(p, "abc");
	lazy_write(p, "ab");
	fs::remove(p);
} 
#line 275 "lazy-write/index.md"
 {
	fs::path p { "a.tmp" };
	lazy_write(p, "abc");
	lazy_write(p, "ad");
	fs::remove(p);
} 
#line 284 "lazy-write/index.md"
 {
	fs::path p { "a.tmp" };
	lazy_write(p, "abc");
	lazy_write(p, "adef");
	fs::remove(p);
} 
#line 64 "lazy-write/index.md"
;
	}
