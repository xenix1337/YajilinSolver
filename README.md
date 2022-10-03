# Yajilin Solver

### Features

- Solves practically any possible [Yajilin](https://en.wikipedia.org/wiki/Yajilin "Yajilin") puzzle
- Parses input from an own format, or [puzz.link](http://puzz.link "puzz.link") links
- Outputs an ASCII graphical representation of the board

### TODO:
- Optimize a lot
- Remove redundant code, restructurize some classes
- Enhance strategies to let them do more before using slow recursion
- Add more input/output types
- Unit testing

### Example output
```
YajilinSolver.exe -input=puzzlink -output=ascii "https://puzz.link/p?yajilin/10/10/l42i41m32f11a22b21a21m32b12i31l11121140f"

+---+---+---+---+---+---+---+---+---+---+
|   |   |   |   |   |XXX|   |   |   |   |
| **|************** |XXX| **|***|***|** |
| * |   |   |   | * |XXX| * |   |   | * |
+---+---+---+---+-*-+---+---+---+---+---+
| * |XXX|   |XXX| * |   | * |XXX|   | * |
| * |XXX| 2>|XXX| **|***|** |XXX| **|** |
| * |XXX|   |XXX|   |   |   |XXX| * |   |
+---+---+---+---+---+---+---+---+---+---+
| * |   |   |   |   |   |   |   | * |XXX|
| **|** | 1>| **|***|***|***|** | * |XXX|
|   | * |   | * |   |   |   | * | * |XXX|
+---+---+---+---+---+---+---+---+---+---+
|   | * |XXX| * |   |XXX|   | * | * |   |
| **|** |XXX| **|** |XXX|<2 | * | **|** |
| * |   |XXX|   | * |XXX|   | * |   | * |
+---+---+---+---+---+---+---+---+---+---+
| * |   |   | ^ | * |   |   | * |   | * |
| **|***|** | 1 | * | 2 | **|** | 1 | * |
|   |   | * |   | * | v | * |   | v | * |
+---+---+---+---+---+---+---+---+---+---+
|   |XXX| * |   | * |XXX| * |XXX|   | * |
| 1 |XXX| **|***|** |XXX| * |XXX| **|** |
| v |XXX|   |   |   |XXX| * |XXX| * |   |
+---+---+---+---+---+---+---+---+---+---+
|XXX|   |   |XXX|   |   | * | ^ | * |XXX|
|XXX| **|** |XXX|<2 | **|** | 2 | * |XXX|
|XXX| * | * |XXX|   | * |   |   | * |XXX|
+---+---+---+---+---+---+---+---+---+---+
|   | * | * |   |   | * |XXX|   | * |   |
| **|** | **|***|***|** |XXX|<1 | **|** |
| * |   |   |   |   |   |XXX|   |   | * |
+---+---+---+---+---+---+---+---+---+---+
| * |   |   |   |   |XXX|   |   |XXX| * |
| **|***|***|***|** |XXX| **|** |XXX| * |
|   |   |   |   | * |XXX| * | * |XXX| * |
+---+---+---+---+---+---+---+---+---+---+
| ^ | ^ | ^ |   | * |   | * | * |   | * |
| 1 | 2 | 1 | 0>| **|***|** | **|***|** |
|   |   |   |   |   |   |   |   |   |   |
+---+---+---+---+---+---+---+---+---+---+
```
