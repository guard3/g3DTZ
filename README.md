# g3DTZ
a GAME.DTZ extraction utility (LCS/VCS)

Current version v1.1
## GTAForums
[g3DTZ topic on GTAForums](https://gtaforums.com/topic/908702-g3dtz-a-gamedtz-extraction-utility/)

Includes download link to compiled binaries

## How to compile
This repo includes a full VS2017 solution, to which you will have to include the zlib library.

For successful compilation, you also have to do the appropriate `#define`s
```cpp
#define lcs
or
#define vcs
```
and
```cpp
#define psp
or
#define ps2
```
main.cpp already has `#define`s for convenience
## How to use
The default utility accepts a single argument: the path to GAME.DTZ

To view help, run without arguments
## Notes
- There are no actual handling names in VCS, so modelnames are used instead
- The last 5 values of object.dat from VCS are unknown, probably different way of assigning damage effects
- Handling.cfg has unknowns. Specifically, bABS and SuspensionHighSpdComDamp. Also, MaxVelocity is unknown in LCS version
- The IDE files from vcs aren't original. They are split up in a way that makes sense (also helps when bruteforcing names).
- Speaking of bruteforcing names, all names are known for LCS, but ~700 remain uncracked for VCS. Some more were added in this version
- VCS PS2 timecyc.dat has 4 extra values for radiosity and blur, so its format isn't very standard

## Documentation
Although this repo serves as a very good documentation source, here are some alternative links

[gtamodding.com](http://www.gtamodding.com/wiki/Game.dtz) (yeah, that won't come online... rip)

[Vice City Stories GAME.DTZ on GTAForums](https://gtaforums.com/topic/892041-vice-city-stories-gamedtz/)
## Credits
Big thanks to aap for his [librwgta](https://github.com/aap/librwgta) repo!
