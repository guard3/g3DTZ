# g3DTZ
A **GAME.DTZ** extraction utility for **GTA:LCS** and **GTA:VCS**

Both **PSP** and **PS2** versions are supported!
## Getting Started
Follow these steps to get a g3DTZ project up and running.
### Prerequisites
**g3DTZ** utilizes [zlib](https://zlib.net/) for GAME.DTZ decompression and it's included in this repo as a git submodule. So, after cloning this repo, don't forget to also initialize submodules.
```
git clone https://github.com/guard3/g3DTZ.git
cd g3DTZ
git submodule init
git submodule update
```
### Generate a Solution
To generate a Visual Studio 2019 solution with [premake](https://premake.github.io/), simply double click **vs2019.bat**. The generated solution includes both a **g3DTZ** and a **zlib** project with all dependencies and configurations already set up.

If you don't have Visual Studio 2019, you can specify your version in premake. *Eg.*
```
premake5 --vs2017
```
### Configurations
The **g3DTZ** solution has 4 configurations for each GAME.DTZ version, plus **Debug** and **Release**.
## Release
The current release is **g3DTZ v2.0**, with extraction support for:
- IDE files
- IPL files
- SFX.SDT sets *(PSP only)*
- Zones *(info.zon / map.zon / navig.zon)*
- Path data *(flight.dat / ferry1.dat / tracks.dat / tracks2.dat)*
- Colour data *(carcols.dat / pedcols.dat)*
- Weapon data *(weapon.dat / weapon_multi.dat)*
- Animations
- CULL.IPL
- OBJECT.DAT
- PED.DAT
- PEDGRP.DAT
- PEDSTATS.DAT
- FISTFITE.DAT *(LCS)*
- PARTICLE.CFG
- SURFACE.DAT
- HANDLING.CFG
- TIMECYC.DAT
- WATERPRO.DAT
- cdimage DIR
- cutscene DIR
- GAME.DAT *(aka decompressed GAME.DTZ)*
## TODO
- [ ] Add link to compiled binaries
## Notes
- The last 5 values of object.dat from VCS are unknown, probably different way of assigning damage effects
- There are no actual handling names in VCS, so the tool extracts with modelnames instead
- In LCS, the handling flags are the same as in VC, for VCS they are the same as SA.
- VCS has some extra special handling for hovercar and jetski, but I haven't looked into it
- VCS has some modelnames missing because not all of them have been cracked, and most likely won't ever be!
- VCS PS2 timecyc.dat has 4 extra values for radiosity and blur, so its format isn't very standard
- VCS most likely ditched FISTFITE.DAT for some other data format for its special fighting system
## Licence
**g3DTZ** is licenced under the **MIT License** - see [LICENSE](LICENSE.md) file for details.
