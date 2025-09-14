# L-SIM LAUNCHER
## Purpose
The purpose of the L-Sim launcher is to provide an easy way to create and manage projects for the [L-SIM ENGINE](https://github.com/Haletas033/LSIMENGINE). the L-SIM launcher allows you to:
* Create Projects
* Load Projects
* Manage Projects
* Delete Projects
* Manage L-SIM ENGINE installs (not currently implemented)
* Adjust L-SIM config files (not currently implemented)
##### All in one clean and intuitive interface

## Current features
Current features of the L-SIM launcher include:
* Creating projects with default config and shaders
* Opening projects instatntly in the [L-SIM ENGINE](https://github.com/Haletas033/LSIMENGINE)
* Delete projects cleanly
* Setting the working directory for all projects

## Upcoming features
* Adding and deleting [L-SIM ENGINE](https://github.com/Haletas033/LSIMENGINE) installs
* Editing [L-SIM ENGINE](https://github.com/Haletas033/LSIMENGINE) configs
* Easy access to documentation

## Prerequisites (Windows)
This project requires Git, Cmake, Ninja(or another build system), A install of the [L-SIM ENGINE](https://github.com/Haletas033/LSIMENGINE)
## How to run
1. Clone the repository
```bash
git clone https://github.com/Haletas033/LSIMLAUNCHER.git
cd LSIMLAUNCHER
```
2. create build directory
```bash
mkdir build
```
3. Run cmake to configure the project
```bash
cmake -S . -B build -G Ninja
```
4. Build the project using ninja (or another build system)
```bash
cd build
ninja
```
5. Run the project
```bash
./LSIMLAUNCHER
```
## Contributing
Contributions are welcome! Whether it's a bug fix, new feature, or documentation improvement, feel free to open an issue or submit a pull request.

## License
This project is licensed under the [MIT License](https://opensource.org/licenses/MIT).  See the [LICENSE](LICENSE) file for details.
