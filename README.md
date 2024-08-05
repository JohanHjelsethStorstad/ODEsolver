# ODEsolver
## Set up
You need to install matplotlib for c++ first install python requierments:
```bash
sudo apt-get install python3 python3-pip
pip3 install matplotlib
```
Then in the lib directory (make it) install:
```bash
git clone https://github.com/lava/matplotlib-cpp.git
```
You might need to change the path to your python interpriter in the Makefile: example:
```bash
-I /usr/include/python3.10
```
Also add a .vscode c_cpp_properties.json for intelliSense: example:
```json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "/usr/include/python3.10", //python interpriter path for Python.h
                "/home/johanstorstad/.local/lib/python3.10/site-packages/numpy/_core/include", // numpy path
                "/home/johanstorstad/ODEsolver/lib/json/single_include" //easy include of json
            ],
            "intelliSenseMode": "linux-gcc-x64",
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "c17",
            "cppStandard": "gnu++17"
        }
    ],
    "version": 4
}
```
You can get your numpy path using:
```bash
python3 -c "import numpy; print(numpy.get_include())
```

## Example of use
```cpp
std::shared_ptr<ODE::BucherTableau::ButcherTableau> butcherTableau = std::make_shared<ODE::BucherTableau::ExplicitButcherTableau<1>>(
    ODE::BucherTableau::ExplicitButcherTableau<1>::Euler()
);
std::shared_ptr<ODE::PrimeFieldInferation::PrimeFieldInferationScheme> inferationScheme = std::make_shared<ODE::PrimeFieldInferation::PrimeFieldInferationSchemeNearest>();
std::vector<Structures::Arrow<double>> primeField = {
    { {0, 0}, {1, 1} },
    { {1, 1}, {2, 2} },
    { {2, 2}, {3, 3} },
    { {3, 3}, {4, 4} },
    { {4, 4}, {5, 5} }
};
ODE::IterationScheme iterationScheme(primeField, butcherTableau, inferationScheme);

std::vector<Structures::Point<double>> points;
points.push_back({ 0.5, 0.5 });
static constexpr int N = 1000;
static constexpr double dt = 0.01;
for (int i = 0; i < N; i++) 
    points.push_back(iterationScheme.step(points.back(), dt));

```