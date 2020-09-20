# Define LaTeX preamble
* preamble of the LaTeX document

```
@Def(preamble)
	@put(preamble)
@End(preamble)
```
* use local fragment instead of global one

```
@def(preamble)
	"\\documentclass["
		"a5paper,ngerman"
	"]{article}\n"
@end(preamble)
```
* document is generated on a DIN A5 page format
* with german spelling
* and a small font

```
@add(preamble)
	"\\usepackage[T1]{fontenc}\n"
	"\\usepackage[utf8]{inputenc}\n"
@end(preamble)
```
* use modern font encoding
* and UTF-8 input format

```
@add(preamble)
	"\\usepackage["
		"margin=0.5in,includefoot"
	"]{geometry}\n"
@end(preamble)
```
* use smaller margins

```
@add(preamble)
	"\\usepackage{microtype}\n"
	"\\usepackage{babel}\n"
	"\\usepackage{siunitx}\n"
@end(preamble)
```
* better position characters
* use german titles
* and standard units

```
@add(preamble)
	"\\usepackage" << (theme.size() ?
		"[" + theme + "]" : ""
	) << "{" << prefix << "solarized}\n"
@end(preamble)
```
* the local solarized package is used with the current theme

```
@add(preamble)
	"\\usepackage{sectsty}\n"
	"\\usepackage{ccfonts}\n"
	"\\usepackage{euler}\n"
@end(preamble)
```
* better section titles
* use concrete and euler font to mimic look of "Concrete Mathematics"

```
@add(preamble)
	"\\usepackage{fancyhdr}\n"
	"\\usepackage{fancyvrb}\n"
@end(preamble)
```
* better headers
* and better verbose listings

```
@add(preamble)
	"\\usepackage{graphicx}\n"
@end(preamble)
```
* include graphics

```
@add(preamble)
	"\\usepackage{multicol}\n"
@end(preamble)
```
* for fancy two-column output

```
@add(preamble)
	"\\usepackage{mdframed}\n"
@end(preamble)
```
* to frame boxes

```
@add(preamble)
	"\\usepackage{" << prefix << "lisp}\n"
@end(preamble)
```
* highlight LISP source code

```
@add(preamble)
	"\\pagestyle{fancy}\n"
	"\\fancypagestyle{plain}{\n"
	"\\fancyhf{}\n"
@end(preamble)
```
* define own pagestyle

```
@add(preamble)
	"\\fancyfoot[C]{{"
		"\\color{deemph}\\small"
		"$\\thepage$"
	"}}\n"
@end(preamble)
```
* page footer contains a small page number

```
@add(preamble)
	"\\renewcommand{\\headrulewidth}"
		"{0pt}\n"
	"\\renewcommand{\\footrulewidth}"
		"{0pt}}\n"
@end(preamble)
```
* hide header and footer rulers

```
@add(preamble)
	"\\title{"
		"\\color{emph}" << title <<
	"}\n"
	"\\author{" << author << "}\n"
	"\\date{" << date << "}\n"
@end(preamble)
```
* define meta-data

```
@add(preamble)
	"\\columnseprule.2pt\n"
	"\\renewcommand{\\columnseprulecolor}"
		"{\\color{deemph}}\n"
@end(preamble)
```
* define column separator

```
@add(preamble)
	"\\begin{document}\n"
@end(preamble)
```
* start the main document

```
@add(preamble)
	"\\pagecolor{background}\n"
	"\\color{normal}\n"
	"\\allsectionsfont{"
		"\\color{emph}\\mdseries"
	"}\n"
@end(preamble)
```
* set the default colors

```
@add(preamble)
	"\\pagestyle{plain}\n"
	"\\maketitle\n"
	"\\thispagestyle{fancy}\n"
@end(preamble)
```
* render title
* and set default page style

```
@add(preamble)
	"\\surroundwithmdframed["
		"backgroundcolor=codebackground,"
		"fontcolor=normal,"
		"hidealllines=true"
	"]{Verbatim}\n";
@end(preamble)
```
* put verbose text in a box
